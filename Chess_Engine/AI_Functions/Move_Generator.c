#include "Move_Generator.h"


bool are_they_possible_moves(){

    // no need to have a great move generation algorithm, because it's not a function that is called during the AI search

    // going through all the from and to index to check if there is a possible move
    for (int from_index = 0; from_index < NUMBER_SQUARES; from_index++){

        // if there is not a piece of the color that is playing on from_index, we don't need to check the possible moves
        if (!(bitboards[WHITE_PIECES] & (1ULL << from_index)) && game_settings->color_of_player_that_is_playing == WHITE){
            continue;
        }
        if (!(bitboards[BLACK_PIECES] & (1ULL << from_index)) && game_settings->color_of_player_that_is_playing == BLACK){
            continue;
        }

        for (int to_index = 0; to_index < NUMBER_SQUARES; to_index++){

            // if there is a piece of the same color at the to_index, we don't need to check the possible moves
            if ((bitboards[WHITE_PIECES] & (1ULL << to_index)) && game_settings->color_of_player_that_is_playing == WHITE){
                continue;
            }
            if ((bitboards[BLACK_PIECES] & (1ULL << to_index)) && game_settings->color_of_player_that_is_playing == BLACK){
                continue;
            }
            
            // function to be able to get the flag, since those are different and doesn't interfere with one another, having one allows us to skip the others 
            // we look for the less time costly flag first
            int flag = No_Flag;
            int piece_taken_type = NOTHING;
            if (is_promotion_possible(game_settings->color_of_player_that_is_playing, bitboards, from_index, to_index)){
                // there is no need to handle the promotion flag here since having a queen instead of a pawn doens't change the check state of our king
            }
            else if (has_pawn_moved_two_squares(game_settings->color_of_player_that_is_playing, bitboards, from_index, to_index)){
                flag = Pawn_Two_Up_Flag;
            }
            else if (is_en_passant_possible(game_settings->color_of_player_that_is_playing, bitboards, from_index, to_index, chess_log)){
                flag = En_Passant_Flag;
                piece_taken_type = get_type_of_piece(bitboards, to_index);
            }
            else if (is_castle_possible(game_settings->color_of_player_that_is_playing, bitboards, from_index, to_index, chess_log)){
                flag = Castle_Flag;
            }
            // if the move is a capture, we need to know if it's a capture, to play the sound of the capture (not needed when we will consider the AI move as a useful part)
            if (will_capture(game_settings->color_of_player_that_is_playing, bitboards, to_index)){
                piece_taken_type = get_type_of_piece(bitboards, to_index);
            }

            // looking if the move is legal and getting the type of piece that will be moved
            int type_move_legal_attacking = is_legal_move(game_settings->color_of_player_that_is_playing, bitboards, from_index, to_index, flag);
            if (type_move_legal_attacking != NOTHING){
                
                // adding into a move value the information of the move                    
                int move_value = get_move_value(from_index, to_index, flag);

                // udpate the first part of the log
                update_log(move_value, piece_taken_type);

                // all put in a make move function 
                make_move(from_index, to_index, flag, type_move_legal_attacking);

                // updating the log with all the castle related information
                update_castle_state_in_log(from_index, to_index, flag, 1-game_settings->color_of_player_that_is_playing);

                // changing the player that is playing for the next turn if the move was done
                change_player_that_is_playing();

                // but also get the check state after the move for the previous player to see if the move was legal after all
                // because looking for a legal move don't assure us that we were not in check after the move
                // a checkmate is not looked for here, it's done every time a graphic need to be showed
                int check_state_after_move = is_check(1-game_settings->color_of_player_that_is_playing, bitboards, chess_log);
                // undo the last move made
                undo_last_move_AI();
                // if the player is not in check after the move, then there is a possible move
                if (check_state_after_move == NO_CHECK && get_king_index(bitboards, 1-game_settings->color_of_player_that_is_playing) != -1){
                    return true;
                }
                // otherwise, we need to continue the loop to check
            
            }

        }
    }
    
    // if there is no possible move, return false
    return false;

}


int get_check_state(int color){

    // getting if there is a possible move for the player that is playing
    bool is_there_a_possible_move = are_they_possible_moves();
    // getting if the player that is playing is in check
    int check_state = is_check(color, bitboards, chess_log);

    // if the king is not checked
    if (check_state == NO_CHECK){
        // if no move is possible on the board for the given color, then it's a stalemate (DRAW)
        if (is_there_a_possible_move == false){
            return STALEMATE;
        }
        // if there is a possible move for the player that is playing, then it's game on
        else if (is_there_a_possible_move == true){
            return NO_CHECK;
        }
    }
    // if the king is checked
    else if (check_state == CHECK){
       // if no move is possible on the board for the given color, then it's a checkmate (WIN)
        if (is_there_a_possible_move == false){
            return CHECK_MATE;
        }
        // if there is a possible move for the player that is playing, then it's a check and it's game on
        else if (is_there_a_possible_move == true){
            return CHECK;
        }
    }

    // default return
    return NO_CHECK;
    
}


move* generate_all_possible_moves(int* nb_moves){

    // putting back the number of moves to 0
    *nb_moves = 0;
    // creating the valid moves array
    move* valid_moves = (move*) malloc(sizeof(move) * max_size_valid_moves_array);
    // looking for malloc errors
    if (valid_moves == NULL){
        printf("Error: not enough memory to allocate the valid moves array\n");
        return NULL;
    }

    // going through all the from and to index to check if there is a possible move
    for (int from_index = 0; from_index < NUMBER_SQUARES; from_index++){

        // if there is not a piece of the color that is playing on from_index, we don't need to check the possible moves
        if (!(bitboards[WHITE_PIECES] & (1ULL << from_index)) && game_settings->color_of_player_that_is_playing == WHITE){
            continue;
        }
        if (!(bitboards[BLACK_PIECES] & (1ULL << from_index)) && game_settings->color_of_player_that_is_playing == BLACK){
            continue;
        }

        // getting the type of the piece that will be moved
        int type_of_piece = get_type_of_piece(bitboards, from_index);

        // faster to have an early exit if there is no piece on the square
        if (type_of_piece == NOTHING){
            continue;
        }

        // looking for en passant or castle moves
        if (game_settings->color_of_player_that_is_playing == WHITE){
            // if a left en passant is possible, we simulate the move and add it to the valid moves if the player is not in check after the move
            if (is_en_passant_possible(WHITE, bitboards, from_index, from_index+7, chess_log)){
                int to_index = from_index+7;
                int flag = No_Flag;
                int piece_taken_type = NOTHING;
                // adding into a move value the information of the move                    
                int move_value = get_move_value(from_index, to_index, flag);
                // udpate the first part of the log 
                update_log(move_value, piece_taken_type);
                // all put in a make move function 
                make_move(from_index, to_index, flag, PAWN_WHITE);
                // updating the log with all the castle related information
                update_castle_state_in_log(from_index, to_index, flag, BLACK);
                // changing the player that is playing for the next turn if the move was done
                change_player_that_is_playing();
                // getting the check state after the move
                int check_state_after_move = is_check(WHITE, bitboards, chess_log);
                // undo the last move made
                undo_last_move_AI();
                // if the player is not in check after the move, then there is a possible move
                if (check_state_after_move == NO_CHECK && get_king_index(bitboards, WHITE) != -1){
                    // reallocating the valid moves array if needed
                    if (*nb_moves >= max_size_valid_moves_array){
                        valid_moves = realloc(valid_moves, max_size_valid_moves_array_extended * sizeof(int*));
                        // looking for realloc errors
                        if (valid_moves == NULL){
                            printf("Error: not enough memory to reallocate the valid moves array\n");
                            return NULL;
                        }
                    }
                    // incrementing the number of moves
                    valid_moves[*nb_moves] = move_value;
                    (*nb_moves)++;
                }
            }
            // if a right en passant is possible, we simulate the move and add it to the valid moves if the player is not in check after the move
            if (is_en_passant_possible(WHITE, bitboards, from_index, from_index+9, chess_log)){
                int to_index = from_index+9;
                int flag = En_Passant_Flag;
                int piece_taken_type = PAWN_BLACK;
                // adding into a move value the information of the move
                int move_value = get_move_value(from_index, to_index, flag);
                // udpate the first part of the log
                update_log(move_value, piece_taken_type);
                // all put in a make move function
                make_move(from_index, to_index, flag, PAWN_WHITE);
                // updating the log with all the castle related information
                update_castle_state_in_log(from_index, to_index, flag, BLACK);
                // changing the player that is playing for the next turn if the move was done
                change_player_that_is_playing();
                // getting the check state after the move
                int check_state_after_move = is_check(WHITE, bitboards, chess_log);
                // undo the last move made
                undo_last_move_AI();
                // if the player is not in check after the move, then there is a possible move
                if (check_state_after_move == NO_CHECK && get_king_index(bitboards, WHITE) != -1){
                    // reallocating the valid moves array if needed
                    if (*nb_moves >= max_size_valid_moves_array){
                        valid_moves = realloc(valid_moves, max_size_valid_moves_array_extended * sizeof(int*));
                        // looking for realloc errors
                        if (valid_moves == NULL){
                            printf("Error: not enough memory to reallocate the valid moves array\n");
                            return NULL;
                        }
                    }
                    // incrementing the number of moves
                    valid_moves[*nb_moves] = move_value;
                    (*nb_moves)++;
                }
            }
            // looking for castle moves
            if (from_index == 4){
                // if a queen side castle is possible, we add it to the valid moves
                if (is_castle_possible(WHITE, bitboards, 4, 2, chess_log)){
                    int to_index = 4;
                    int flag = Castle_Flag;
                    // adding into a move value the information of the move
                    int move_value = get_move_value(from_index, to_index, flag);
                    // there is no need to simulate since we checked everything before in the is_castle_possible function
                    // reallocating the valid moves array if needed
                    if (*nb_moves >= max_size_valid_moves_array){
                        valid_moves = realloc(valid_moves, max_size_valid_moves_array_extended * sizeof(int*));
                        // looking for realloc errors
                        if (valid_moves == NULL){
                            printf("Error: not enough memory to reallocate the valid moves array\n");
                            return NULL;
                        }
                    }
                    // incrementing the number of moves
                    valid_moves[*nb_moves] = move_value;
                    (*nb_moves)++;
                }
                // if a king side castle is possible, we add it to the valid moves
                if (is_castle_possible(WHITE, bitboards, 4, 6, chess_log)){
                    int to_index = 6;
                    int flag = Castle_Flag;
                    // adding into a move value the information of the move
                    int move_value = get_move_value(from_index, to_index, flag);
                    // there is no need to simulate since we checked everything before in the is_castle_possible function
                    // reallocating the valid moves array if needed
                    if (*nb_moves >= max_size_valid_moves_array){
                        valid_moves = realloc(valid_moves, max_size_valid_moves_array_extended * sizeof(int*));
                        // looking for realloc errors
                        if (valid_moves == NULL){
                            printf("Error: not enough memory to reallocate the valid moves array\n");
                            return NULL;
                        }
                    }
                    // incrementing the number of moves
                    valid_moves[*nb_moves] = move_value;
                    (*nb_moves)++;
                }
            }
        }
        else if (game_settings->color_of_player_that_is_playing == BLACK){
            // if a left en passant is possible, we simulate the move and add it to the valid moves if the player is not in check after the move
            if (is_en_passant_possible(BLACK, bitboards, from_index, from_index-9, chess_log)){
                int to_index = from_index-9;
                int flag = En_Passant_Flag;
                int piece_taken_type = PAWN_WHITE;
                // adding into a move value the information of the move                    
                int move_value = get_move_value(from_index, to_index, flag);
                // udpate the first part of the log 
                update_log(move_value, piece_taken_type);
                // all put in a make move function 
                make_move(from_index, to_index, flag, PAWN_BLACK);
                // updating the log with all the castle related information
                update_castle_state_in_log(from_index, to_index, flag, WHITE);
                // changing the player that is playing for the next turn if the move was done
                change_player_that_is_playing();
                // getting the check state after the move
                int check_state_after_move = is_check(BLACK, bitboards, chess_log);
                // undo the last move made
                undo_last_move_AI();
                // if the player is not in check after the move, then there is a possible move
                if (check_state_after_move == NO_CHECK && get_king_index(bitboards, BLACK) != -1){
                    // reallocating the valid moves array if needed
                    if (*nb_moves >= max_size_valid_moves_array){
                        valid_moves = realloc(valid_moves, max_size_valid_moves_array_extended * sizeof(int*));
                        // looking for realloc errors
                        if (valid_moves == NULL){
                            printf("Error: not enough memory to reallocate the valid moves array\n");
                            return NULL;
                        }
                    }
                    // incrementing the number of moves
                    valid_moves[*nb_moves] = move_value;
                    (*nb_moves)++;
                }
            }
            // if a right en passant is possible, we simulate the move and add it to the valid moves if the player is not in check after the move
            if (is_en_passant_possible(BLACK, bitboards, from_index, from_index-7, chess_log)){
                int to_index = from_index-7;
                int flag = En_Passant_Flag;
                int piece_taken_type = PAWN_WHITE;
                // adding into a move value the information of the move
                int move_value = get_move_value(from_index, to_index, flag);
                // udpate the first part of the log
                update_log(move_value, piece_taken_type);
                // all put in a make move function
                make_move(from_index, to_index, flag, PAWN_BLACK);
                // updating the log with all the castle related information
                update_castle_state_in_log(from_index, to_index, flag, WHITE);
                // changing the player that is playing for the next turn if the move was done
                change_player_that_is_playing();
                // getting the check state after the move
                int check_state_after_move = is_check(BLACK, bitboards, chess_log);
                // undo the last move made
                undo_last_move_AI();
                // if the player is not in check after the move, then there is a possible move
                if (check_state_after_move == NO_CHECK && get_king_index(bitboards, BLACK) != -1){
                    // reallocating the valid moves array if needed
                    if (*nb_moves >= max_size_valid_moves_array){
                        valid_moves = realloc(valid_moves, max_size_valid_moves_array_extended * sizeof(int*));
                        // looking for realloc errors
                        if (valid_moves == NULL){
                            printf("Error: not enough memory to reallocate the valid moves array\n");
                            return NULL;
                        }
                    }
                    // incrementing the number of moves
                    valid_moves[*nb_moves] = move_value;
                    (*nb_moves)++;
                }
            }
            // looking for castle moves
            if (from_index == 60){
                // if a queen side castle is possible, we add it to the valid moves
                if (is_castle_possible(BLACK, bitboards, 60, 58, chess_log)){
                    int to_index = 58;
                    int flag = Castle_Flag;
                    // adding into a move value the information of the move
                    int move_value = get_move_value(from_index, to_index, flag);
                    // there is no need to simulate since we checked everything before in the is_castle_possible function
                    // reallocating the valid moves array if needed
                    if (*nb_moves >= max_size_valid_moves_array){
                        valid_moves = realloc(valid_moves, max_size_valid_moves_array_extended * sizeof(int*));
                        // looking for realloc errors
                        if (valid_moves == NULL){
                            printf("Error: not enough memory to reallocate the valid moves array\n");
                            return NULL;
                        }
                    }
                    // incrementing the number of moves
                    valid_moves[*nb_moves] = move_value;
                    (*nb_moves)++;
                }
                // if a king side castle is possible, we add it to the valid moves
                if (is_castle_possible(BLACK, bitboards, 60, 62, chess_log)){
                    int to_index = 62;
                    int flag = Castle_Flag;
                    // adding into a move value the information of the move
                    int move_value = get_move_value(from_index, to_index, flag);
                    // there is no need to simulate since we checked everything before in the is_castle_possible function
                    // reallocating the valid moves array if needed
                    if (*nb_moves >= max_size_valid_moves_array){
                        valid_moves = realloc(valid_moves, max_size_valid_moves_array_extended * sizeof(int*));
                        // looking for realloc errors
                        if (valid_moves == NULL){
                            printf("Error: not enough memory to reallocate the valid moves array\n");
                            return NULL;
                        }
                    }
                    // incrementing the number of moves
                    valid_moves[*nb_moves] = move_value;
                    (*nb_moves)++;
                }
            }
        }

        // if the piece is a white pawn 
        if (type_of_piece == PAWN_WHITE){
            bit_board white_pawn_moves = calculate_pawn_moves_with_blockers(from_index, WHITE, bitboards[WHITE_PIECES] | bitboards[BLACK_PIECES]);
            // getting all to indexes where the pawn can go
            while (white_pawn_moves) {
                // Get the index of the least significant bit that is set
                int to_index = __builtin_ctzll(white_pawn_moves);
                int flag = No_Flag;
                int piece_taken_type = NOTHING;      
                // Clear the least significant '1' bit
                white_pawn_moves &= white_pawn_moves - 1;
                // if there is a piece of the same color at the to_index, we don't need to check the possible moves
                if ((bitboards[WHITE_PIECES] & (1ULL << to_index))){
                    continue;
                }
                // we now can simulate each moves and check if the player is not in check after the move
                if (has_pawn_moved_two_squares(WHITE, bitboards, from_index, to_index)){
                    flag = Pawn_Two_Up_Flag;
                }
                else if (is_promotion_possible(WHITE, bitboards, from_index, to_index)){
                    flag = Promote_To_Queen_Flag;
                    printf("Promotion possible\n");
                }
                // if the move is a capture, we need to know if it's a capture, to play the sound of the capture (not needed when we will consider the AI move as a useful part)
                if (will_capture(WHITE, bitboards, to_index)){
                    piece_taken_type = get_type_of_piece(bitboards, to_index);
                }
                // adding into a move value the information of the move
                int move_value = get_move_value(from_index, to_index, flag);
                // udpate the first part of the log
                update_log(move_value, piece_taken_type);
                // all put in a make move function
                make_move(from_index, to_index, flag, PAWN_WHITE);
                if (flag == Promote_To_Queen_Flag){
                    // the AI will always promote to a queen
                    add_flag_to_move(&chess_log->moves[chess_log->actual_size-1]->move_value, Promote_To_Queen_Flag);
                    bitboards[QUEEN_WHITE] |= (1ULL << to_index);
                    bitboards[PAWN_WHITE] &= ~(1ULL << to_index);
                }
                // updating the log with all the castle related information
                update_castle_state_in_log(from_index, to_index, flag, BLACK);
                // changing the player that is playing for the next turn if the move was done
                change_player_that_is_playing();
                // getting the check state after the move
                int check_state_after_move = is_check(WHITE, bitboards, chess_log);
                // undo the last move made
                undo_last_move_AI();
                // if the player is not in check after the move, then there is a possible move
                if (check_state_after_move == NO_CHECK && get_king_index(bitboards, WHITE) != -1){
                    // reallocating the valid moves array if needed
                    if (*nb_moves >= max_size_valid_moves_array){
                        valid_moves = realloc(valid_moves, max_size_valid_moves_array_extended * sizeof(int*));
                        // looking for realloc errors
                        if (valid_moves == NULL){
                            printf("Error: not enough memory to reallocate the valid moves array\n");
                            return NULL;
                        }
                    }
                    // incrementing the number of moves
                    valid_moves[*nb_moves] = move_value;
                    (*nb_moves)++;
                }
            }
        }
        // if the piece is a black pawn
        else if (type_of_piece == PAWN_BLACK){
            bit_board black_pawn_moves = calculate_pawn_moves_with_blockers(from_index, BLACK, bitboards[WHITE_PIECES] | bitboards[BLACK_PIECES]);
            // getting all to indexes where the pawn can go
            while (black_pawn_moves) {
                // Get the index of the least significant bit that is set
                int to_index = __builtin_ctzll(black_pawn_moves);
                int flag = No_Flag;
                int piece_taken_type = NOTHING;
                // Clear the least significant '1' bit
                black_pawn_moves &= black_pawn_moves - 1;
                // if there is a piece of the same color at the to_index, we don't need to check the possible moves
                if ((bitboards[BLACK_PIECES] & (1ULL << to_index))){
                    continue;
                }
                // we now can simulate each moves and check if the player is not in check after the move
                if (has_pawn_moved_two_squares(BLACK, bitboards, from_index, to_index)){
                    flag = Pawn_Two_Up_Flag;
                }
                else if (is_promotion_possible(WHITE, bitboards, from_index, to_index)){
                    flag = Promote_To_Queen_Flag;
                }
                // if the move is a capture, we need to know if it's a capture, to play the sound of the capture (not needed when we will consider the AI move as a useful part)
                if (will_capture(BLACK, bitboards, to_index)){
                    piece_taken_type = get_type_of_piece(bitboards, to_index);
                }
                // adding into a move value the information of the move
                int move_value = get_move_value(from_index, to_index, flag);
                // udpate the first part of the log
                update_log(move_value, piece_taken_type);
                // all put in a make move function
                make_move(from_index, to_index, flag, PAWN_BLACK);
                if (flag == Promote_To_Queen_Flag){
                    // the AI will always promote to a queen
                    add_flag_to_move(&chess_log->moves[chess_log->actual_size-1]->move_value, Promote_To_Queen_Flag);
                    bitboards[QUEEN_BLACK] |= (1ULL << to_index);
                    bitboards[PAWN_BLACK] &= ~(1ULL << to_index);
                }
                // updating the log with all the castle related information
                update_castle_state_in_log(from_index, to_index, flag, WHITE);
                // changing the player that is playing for the next turn if the move was done
                change_player_that_is_playing();
                // getting the check state after the move
                int check_state_after_move = is_check(BLACK, bitboards, chess_log);
                // undo the last move made
                undo_last_move_AI();
                // if the player is not in check after the move, then there is a possible move
                if (check_state_after_move == NO_CHECK && get_king_index(bitboards, BLACK) != -1){
                    // reallocating the valid moves array if needed
                    if (*nb_moves >= max_size_valid_moves_array){
                        valid_moves = realloc(valid_moves, max_size_valid_moves_array_extended * sizeof(int*));
                        // looking for realloc errors
                        if (valid_moves == NULL){
                            printf("Error: not enough memory to reallocate the valid moves array\n");
                            return NULL;
                        }
                    }
                    // incrementing the number of moves
                    valid_moves[*nb_moves] = move_value;
                    (*nb_moves)++;
                }
            }
        }
        // if the piece is a white knight
        else if (type_of_piece == KNIGHT_WHITE){
            bit_board white_knight_moves = precomputed_knight_attacks[from_index];
            // getting all to indexes where the knight can go
            while (white_knight_moves) {
                // Get the index of the least significant bit that is set
                int to_index = __builtin_ctzll(white_knight_moves);
                int flag = No_Flag;
                int piece_taken_type = NOTHING;
                // Clear the least significant '1' bit
                white_knight_moves &= white_knight_moves - 1;
                // if there is a piece of the same color at the to_index, we don't need to check the possible moves
                if ((bitboards[WHITE_PIECES] & (1ULL << to_index))){
                    continue;
                }
                // we now can simulate each moves and check if the player is not in check after the move
                // if the move is a capture, we need to know if it's a capture, to play the sound of the capture (not needed when we will consider the AI move as a useful part)
                if (will_capture(WHITE, bitboards, to_index)){
                    piece_taken_type = get_type_of_piece(bitboards, to_index);
                }
                // adding into a move value the information of the move
                int move_value = get_move_value(from_index, to_index, flag);
                // udpate the first part of the log
                update_log(move_value, piece_taken_type);
                // all put in a make move function
                make_move(from_index, to_index, flag, KNIGHT_WHITE);
                // updating the log with all the castle related information
                update_castle_state_in_log(from_index, to_index, flag, BLACK);
                // changing the player that is playing for the next turn if the move was done
                change_player_that_is_playing();
                // getting the check state after the move
                int check_state_after_move = is_check(WHITE, bitboards, chess_log);
                // undo the last move made
                undo_last_move_AI();
                // if the player is not in check after the move, then there is a possible move
                if (check_state_after_move == NO_CHECK && get_king_index(bitboards, WHITE) != -1){
                    // reallocating the valid moves array if needed
                    if (*nb_moves >= max_size_valid_moves_array){
                        valid_moves = realloc(valid_moves, max_size_valid_moves_array_extended * sizeof(int*));
                        // looking for realloc errors
                        if (valid_moves == NULL){
                            printf("Error: not enough memory to reallocate the valid moves array\n");
                            return NULL;
                        }
                    }
                    // incrementing the number of moves
                    valid_moves[*nb_moves] = move_value;
                    (*nb_moves)++;
                }
            }
        }
        // if the piece is a black knight 
        else if (type_of_piece == KNIGHT_BLACK){
            bit_board black_knight_moves = precomputed_knight_attacks[from_index];
            // getting all to indexes where the knight can go
            while (black_knight_moves) {
                // Get the index of the least significant bit that is set
                int to_index = __builtin_ctzll(black_knight_moves);
                int flag = No_Flag;
                int piece_taken_type = NOTHING;
                // Clear the least significant '1' bit
                black_knight_moves &= black_knight_moves - 1;
                // if there is a piece of the same color at the to_index, we don't need to check the possible moves
                if ((bitboards[BLACK_PIECES] & (1ULL << to_index))){
                    continue;
                }
                // we now can simulate each moves and check if the player is not in check after the move
                // if the move is a capture, we need to know if it's a capture, to play the sound of the capture (not needed when we will consider the AI move as a useful part)
                if (will_capture(BLACK, bitboards, to_index)){
                    piece_taken_type = get_type_of_piece(bitboards, to_index);
                }
                // adding into a move value the information of the move
                int move_value = get_move_value(from_index, to_index, flag);
                // udpate the first part of the log
                update_log(move_value, piece_taken_type);
                // all put in a make move function
                make_move(from_index, to_index, flag, KNIGHT_BLACK);
                // updating the log with all the castle related information
                update_castle_state_in_log(from_index, to_index, flag, WHITE);
                // changing the player that is playing for the next turn if the move was done
                change_player_that_is_playing();
                // getting the check state after the move
                int check_state_after_move = is_check(BLACK, bitboards, chess_log);
                // undo the last move made
                undo_last_move_AI();
                // if the player is not in check after the move, then there is a possible move
                if (check_state_after_move == NO_CHECK && get_king_index(bitboards, BLACK) != -1){
                    // reallocating the valid moves array if needed
                    if (*nb_moves >= max_size_valid_moves_array){
                        valid_moves = realloc(valid_moves, max_size_valid_moves_array_extended * sizeof(int*));
                        // looking for realloc errors
                        if (valid_moves == NULL){
                            printf("Error: not enough memory to reallocate the valid moves array\n");
                            return NULL;
                        }
                    }
                    // incrementing the number of moves
                    valid_moves[*nb_moves] = move_value;
                    (*nb_moves)++;
                }
            }
        }
       // if the piece is a sliding piece
        else if (type_of_piece == ROOK_WHITE || type_of_piece == BISHOP_WHITE || type_of_piece == QUEEN_WHITE){
            // if the piece is a white rook or a white queen 
            if (type_of_piece == ROOK_WHITE || type_of_piece == QUEEN_WHITE){
                bit_board white_rook_moves = calculate_rook_attacks_with_blockers(from_index, bitboards[WHITE_PIECES] | bitboards[BLACK_PIECES]);
                // getting all to indexes where the rook can go
                while (white_rook_moves) {
                    // Get the index of the least significant bit that is set
                    int to_index = __builtin_ctzll(white_rook_moves);
                    int flag = No_Flag;
                    int piece_taken_type = NOTHING;
                    // Clear the least significant '1' bit
                    white_rook_moves &= white_rook_moves - 1;
                    // if there is a piece of the same color at the to_index, we don't need to check the possible moves
                    if ((bitboards[WHITE_PIECES] & (1ULL << to_index))){
                        continue;
                    }
                    // we now can simulate each moves and check if the player is not in check after the move
                    // if the move is a capture, we need to know if it's a capture, to play the sound of the capture (not needed when we will consider the AI move as a useful part)
                    if (will_capture(WHITE, bitboards, to_index)){
                        piece_taken_type = get_type_of_piece(bitboards, to_index);
                    }
                    // adding into a move value the information of the move
                    int move_value = get_move_value(from_index, to_index, flag);
                    // udpate the first part of the log
                    update_log(move_value, piece_taken_type);
                    // all put in a make move function
                    make_move(from_index, to_index, flag, (type_of_piece == ROOK_WHITE) ? ROOK_WHITE : QUEEN_WHITE);
                    // updating the log with all the castle related information
                    update_castle_state_in_log(from_index, to_index, flag, BLACK);
                    // changing the player that is playing for the next turn if the move was done
                    change_player_that_is_playing();
                    // getting the check state after the move
                    int check_state_after_move = is_check(WHITE, bitboards, chess_log);
                    // undo the last move made
                    undo_last_move_AI();
                    // if the player is not in check after the move, then there is a possible move
                    if (check_state_after_move == NO_CHECK && get_king_index(bitboards, WHITE) != -1){
                        // reallocating the valid moves array if needed
                        if (*nb_moves >= max_size_valid_moves_array){
                            valid_moves = realloc(valid_moves, max_size_valid_moves_array_extended * sizeof(int*));
                            // looking for realloc errors
                            if (valid_moves == NULL){
                                printf("Error: not enough memory to reallocate the valid moves array\n");
                                return NULL;
                            }
                        }
                        // incrementing the number of moves
                        valid_moves[*nb_moves] = move_value;
                        (*nb_moves)++;
                    }
                }
            }
              // if the piece is a white bishop or a white queen 
            if (type_of_piece == BISHOP_WHITE || type_of_piece == QUEEN_WHITE){
                bit_board white_bishop_moves = calculate_bishop_attacks_with_blockers(from_index, bitboards[WHITE_PIECES] | bitboards[BLACK_PIECES]);
                // getting all to indexes where the bishop can go
                while (white_bishop_moves) {
                    // Get the index of the least significant bit that is set
                    int to_index = __builtin_ctzll(white_bishop_moves);
                    int flag = No_Flag;
                    int piece_taken_type = NOTHING;
                    // Clear the least significant '1' bit
                    white_bishop_moves &= white_bishop_moves - 1;
                    // if there is a piece of the same color at the to_index, we don't need to check the possible moves
                    if ((bitboards[WHITE_PIECES] & (1ULL << to_index))){
                        continue;
                    }
                    // we now can simulate each moves and check if the player is not in check after the move
                    // if the move is a capture, we need to know if it's a capture, to play the sound of the capture (not needed when we will consider the AI move as a useful part)
                    if (will_capture(WHITE, bitboards, to_index)){
                        piece_taken_type = get_type_of_piece(bitboards, to_index);
                    }
                    // adding into a move value the information of the move
                    int move_value = get_move_value(from_index, to_index, flag);
                    // udpate the first part of the log
                    update_log(move_value, piece_taken_type);
                    // all put in a make move function
                    make_move(from_index, to_index, flag, (type_of_piece == BISHOP_WHITE) ? BISHOP_WHITE : QUEEN_WHITE);
                    // updating the log with all the castle related information
                    update_castle_state_in_log(from_index, to_index, flag, BLACK);
                    // changing the player that is playing for the next turn if the move was done
                    change_player_that_is_playing();
                    // getting the check state after the move
                    int check_state_after_move = is_check(WHITE, bitboards, chess_log);
                    // undo the last move made
                    undo_last_move_AI();
                    // if the player is not in check after the move, then there is a possible move
                    if (check_state_after_move == NO_CHECK && get_king_index(bitboards, WHITE) != -1){
                        // reallocating the valid moves array if needed
                        if (*nb_moves >= max_size_valid_moves_array){
                            valid_moves = realloc(valid_moves, max_size_valid_moves_array_extended * sizeof(int*));
                            // looking for realloc errors
                            if (valid_moves == NULL){
                                printf("Error: not enough memory to reallocate the valid moves array\n");
                                return NULL;
                            }
                        }
                        // incrementing the number of moves
                        valid_moves[*nb_moves] = move_value;
                        (*nb_moves)++;
                    }
                }
            }
        }
        else if (type_of_piece == ROOK_BLACK || type_of_piece == BISHOP_BLACK || type_of_piece == QUEEN_BLACK){
            // if the piece is a black rook or a black queen 
            if (type_of_piece == ROOK_BLACK || type_of_piece == QUEEN_BLACK){
                bit_board black_rook_moves = calculate_rook_attacks_with_blockers(from_index, bitboards[WHITE_PIECES] | bitboards[BLACK_PIECES]);
                // getting all to indexes where the rook can go
                while (black_rook_moves) {
                    // Get the index of the least significant bit that is set
                    int to_index = __builtin_ctzll(black_rook_moves);
                    int flag = No_Flag;
                    int piece_taken_type = NOTHING;
                    // Clear the least significant '1' bit
                    black_rook_moves &= black_rook_moves - 1;
                    // if there is a piece of the same color at the to_index, we don't need to check the possible moves
                    if ((bitboards[BLACK_PIECES] & (1ULL << to_index))){
                        continue;
                    }
                    // we now can simulate each moves and check if the player is not in check after the move
                    // if the move is a capture, we need to know if it's a capture, to play the sound of the capture (not needed when we will consider the AI move as a useful part)
                    if (will_capture(BLACK, bitboards, to_index)){
                        piece_taken_type = get_type_of_piece(bitboards, to_index);
                    }
                    // adding into a move value the information of the move
                    int move_value = get_move_value(from_index, to_index, flag);
                    // udpate the first part of the log
                    update_log(move_value, piece_taken_type);
                    // all put in a make move function
                    make_move(from_index, to_index, flag, (type_of_piece == ROOK_BLACK) ? ROOK_BLACK : QUEEN_BLACK);
                    // updating the log with all the castle related information
                    update_castle_state_in_log(from_index, to_index, flag, WHITE);
                    // changing the player that is playing for the next turn if the move was done
                    change_player_that_is_playing();
                    // getting the check state after the move
                    int check_state_after_move = is_check(BLACK, bitboards, chess_log);
                    // undo the last move made
                    undo_last_move_AI();
                    // if the player is not in check after the move, then there is a possible move
                    if (check_state_after_move == NO_CHECK && get_king_index(bitboards, BLACK) != -1){
                        // reallocating the valid moves array if needed
                        if (*nb_moves >= max_size_valid_moves_array){
                            valid_moves = realloc(valid_moves, max_size_valid_moves_array_extended * sizeof(int*));
                            // looking for realloc errors
                            if (valid_moves == NULL){
                                printf("Error: not enough memory to reallocate the valid moves array\n");
                                return NULL;
                            }
                        }
                        // incrementing the number of moves
                        valid_moves[*nb_moves] = move_value;
                        (*nb_moves)++;
                    }
                }
            }
            // if the piece is a black bishop or a black queen 
            if (type_of_piece == BISHOP_BLACK || type_of_piece == QUEEN_BLACK){
                bit_board black_bishop_moves = calculate_bishop_attacks_with_blockers(from_index, bitboards[WHITE_PIECES] | bitboards[BLACK_PIECES]);
                // getting all to indexes where the bishop can go
                while (black_bishop_moves) {
                    // Get the index of the least significant bit that is set
                    int to_index = __builtin_ctzll(black_bishop_moves);
                    int flag = No_Flag;
                    int piece_taken_type = NOTHING;
                    // Clear the least significant '1' bit
                    black_bishop_moves &= black_bishop_moves - 1;
                    // if there is a piece of the same color at the to_index, we don't need to check the possible moves
                    if ((bitboards[BLACK_PIECES] & (1ULL << to_index))){
                        continue;
                    }
                    // we now can simulate each moves and check if the player is not in check after the move
                    // if the move is a capture, we need to know if it's a capture, to play the sound of the capture (not needed when we will consider the AI move as a useful part)
                    if (will_capture(BLACK, bitboards, to_index)){
                        piece_taken_type = get_type_of_piece(bitboards, to_index);
                    }
                    // adding into a move value the information of the move
                    int move_value = get_move_value(from_index, to_index, flag);
                    // udpate the first part of the log
                    update_log(move_value, piece_taken_type);
                    // all put in a make move function
                    make_move(from_index, to_index, flag, (type_of_piece == BISHOP_BLACK) ? BISHOP_BLACK : QUEEN_BLACK);
                    // updating the log with all the castle related information
                    update_castle_state_in_log(from_index, to_index, flag, WHITE);
                    // changing the player that is playing for the next turn if the move was done
                    change_player_that_is_playing();
                    // getting the check state after the move
                    int check_state_after_move = is_check(BLACK, bitboards, chess_log);
                    // undo the last move made
                    undo_last_move_AI();
                    // if the player is not in check after the move, then there is a possible move
                    if (check_state_after_move == NO_CHECK && get_king_index(bitboards, BLACK) != -1){
                        // reallocating the valid moves array if needed
                        if (*nb_moves >= max_size_valid_moves_array){
                            valid_moves = realloc(valid_moves, max_size_valid_moves_array_extended * sizeof(int*));
                            // looking for realloc errors
                            if (valid_moves == NULL){
                                printf("Error: not enough memory to reallocate the valid moves array\n");
                                return NULL;
                            }
                        }
                        // incrementing the number of moves
                        valid_moves[*nb_moves] = move_value;
                        (*nb_moves)++;
                    }
                }
            }
        }
        // if the piece is a white king 
        else if (type_of_piece == KING_WHITE){
            bit_board white_king_moves = precomputed_king_attacks[from_index];
            // getting all to indexes where the king can go
            while (white_king_moves) {
                // Get the index of the least significant bit that is set
                int to_index = __builtin_ctzll(white_king_moves);
                int flag = No_Flag;
                int piece_taken_type = NOTHING;
                // Clear the least significant '1' bit
                white_king_moves &= white_king_moves - 1;
                // if there is a piece of the same color at the to_index, we don't need to check the possible moves
                if ((bitboards[WHITE_PIECES] & (1ULL << to_index))){
                    continue;
                }
                // we now can simulate each moves and check if the player is not in check after the move
                // if the move is a capture, we need to know if it's a capture, to play the sound of the capture (not needed when we will consider the AI move as a useful part)
                if (will_capture(WHITE, bitboards, to_index)){
                    piece_taken_type = get_type_of_piece(bitboards, to_index);
                }
                // adding into a move value the information of the move
                int move_value = get_move_value(from_index, to_index, flag);
                // udpate the first part of the log
                update_log(move_value, piece_taken_type);
                // all put in a make move function
                make_move(from_index, to_index, flag, KING_WHITE);
                // updating the log with all the castle related information
                update_castle_state_in_log(from_index, to_index, flag, BLACK);
                // changing the player that is playing for the next turn if the move was done
                change_player_that_is_playing();
                // getting the check state after the move
                int check_state_after_move = is_check(WHITE, bitboards, chess_log);
                // undo the last move made
                undo_last_move_AI();
                // if the player is not in check after the move, then there is a possible move
                if (check_state_after_move == NO_CHECK && get_king_index(bitboards, WHITE) != -1){
                    // reallocating the valid moves array if needed
                    if (*nb_moves >= max_size_valid_moves_array){
                        valid_moves = realloc(valid_moves, max_size_valid_moves_array_extended * sizeof(int*));
                        // looking for realloc errors
                        if (valid_moves == NULL){
                            printf("Error: not enough memory to reallocate the valid moves array\n");
                            return NULL;
                        }
                    }
                    // incrementing the number of moves
                    valid_moves[*nb_moves] = move_value;
                    (*nb_moves)++;
                }
            }
        }
        // if the piece is a black king 
        else if (type_of_piece == KING_BLACK){
            bit_board black_king_moves = precomputed_king_attacks[from_index];
            // getting all to indexes where the king can go
            while (black_king_moves) {
                // Get the index of the least significant bit that is set
                int to_index = __builtin_ctzll(black_king_moves);
                int flag = No_Flag;
                int piece_taken_type = NOTHING;
                // Clear the least significant '1' bit
                black_king_moves &= black_king_moves - 1;
                // if there is a piece of the same color at the to_index, we don't need to check the possible moves
                if ((bitboards[BLACK_PIECES] & (1ULL << to_index))){
                    continue;
                }
                // we now can simulate each moves and check if the player is not in check after the move
                // if the move is a capture, we need to know if it's a capture, to play the sound of the capture (not needed when we will consider the AI move as a useful part)
                if (will_capture(BLACK, bitboards, to_index)){
                    piece_taken_type = get_type_of_piece(bitboards, to_index);
                }
                // adding into a move value the information of the move
                int move_value = get_move_value(from_index, to_index, flag);
                // udpate the first part of the log
                update_log(move_value, piece_taken_type);
                // all put in a make move function
                make_move(from_index, to_index, flag, KING_BLACK);
                // updating the log with all the castle related information
                update_castle_state_in_log(from_index, to_index, flag, WHITE);
                // changing the player that is playing for the next turn if the move was done
                change_player_that_is_playing();
                // getting the check state after the move
                int check_state_after_move = is_check(BLACK, bitboards, chess_log);
                // undo the last move made
                undo_last_move_AI();
                // if the player is not in check after the move, then there is a possible move
                if (check_state_after_move == NO_CHECK && get_king_index(bitboards, BLACK) != -1){
                    // reallocating the valid moves array if needed
                    if (*nb_moves >= max_size_valid_moves_array){
                        valid_moves = realloc(valid_moves, max_size_valid_moves_array_extended * sizeof(int*));
                        // looking for realloc errors
                        if (valid_moves == NULL){
                            printf("Error: not enough memory to reallocate the valid moves array\n");
                            return NULL;
                        }
                    }
                    // incrementing the number of moves
                    valid_moves[*nb_moves] = move_value;
                    (*nb_moves)++;
                }
            }
        }
    }

    // returning the valid moves array
    return valid_moves;

}


move* generate_all_possible_moves_that_capture(int* nb_moves){

    // putting back the number of moves to 0
    *nb_moves = 0;
    // creating the valid moves array
    move* valid_moves = (move*) malloc(sizeof(move) * max_size_valid_moves_array);
    // looking for malloc errors
    if (valid_moves == NULL){
        printf("Error: not enough memory to allocate the valid moves array\n");
        return NULL;
    }

    // going through all the from and to index to check if there is a possible move
    for (int from_index = 0; from_index < NUMBER_SQUARES; from_index++){

        // if there is not a piece of the color that is playing on from_index, we don't need to check the possible moves
        if (!(bitboards[WHITE_PIECES] & (1ULL << from_index)) && game_settings->color_of_player_that_is_playing == WHITE){
            continue;
        }
        if (!(bitboards[BLACK_PIECES] & (1ULL << from_index)) && game_settings->color_of_player_that_is_playing == BLACK){
            continue;
        }

        // getting the type of the piece that will be moved
        int type_of_piece = get_type_of_piece(bitboards, from_index);

        // faster to have an early exit if there is no piece on the square
        if (type_of_piece == NOTHING){
            continue;
        }

        // looking for en passant or castle moves
        if (game_settings->color_of_player_that_is_playing == WHITE){
            // if a left en passant is possible, we simulate the move and add it to the valid moves if the player is not in check after the move
            if (is_en_passant_possible(WHITE, bitboards, from_index, from_index+7, chess_log)){
                int to_index = from_index+7;
                int flag = En_Passant_Flag;
                int piece_taken_type = PAWN_BLACK;
                // adding into a move value the information of the move                    
                int move_value = get_move_value(from_index, to_index, flag);
                // udpate the first part of the log 
                update_log(move_value, piece_taken_type);
                // all put in a make move function 
                make_move(from_index, to_index, flag, PAWN_WHITE);
                // updating the log with all the castle related information
                update_castle_state_in_log(from_index, to_index, flag, BLACK);
                // changing the player that is playing for the next turn if the move was done
                change_player_that_is_playing();
                // getting the check state after the move
                int check_state_after_move = is_check(WHITE, bitboards, chess_log);
                // undo the last move made
                undo_last_move_AI();
                // if the player is not in check after the move, then there is a possible move
                if (check_state_after_move == NO_CHECK && get_king_index(bitboards, WHITE) != -1){
                    // reallocating the valid moves array if needed
                    if (*nb_moves >= max_size_valid_moves_array){
                        valid_moves = realloc(valid_moves, max_size_valid_moves_array_extended * sizeof(int*));
                        // looking for realloc errors
                        if (valid_moves == NULL){
                            printf("Error: not enough memory to reallocate the valid moves array\n");
                            return NULL;
                        }
                    }
                    // incrementing the number of moves
                    valid_moves[*nb_moves] = move_value;
                    (*nb_moves)++;
                }
            }
            // if a right en passant is possible, we simulate the move and add it to the valid moves if the player is not in check after the move
            if (is_en_passant_possible(WHITE, bitboards, from_index, from_index+9, chess_log)){
                int to_index = from_index+9;
                int flag = En_Passant_Flag;
                int piece_taken_type = PAWN_BLACK;
                // adding into a move value the information of the move
                int move_value = get_move_value(from_index, to_index, flag);
                // udpate the first part of the log
                update_log(move_value, piece_taken_type);
                // all put in a make move function
                make_move(from_index, to_index, flag, PAWN_WHITE);
                // updating the log with all the castle related information
                update_castle_state_in_log(from_index, to_index, flag, BLACK);
                // changing the player that is playing for the next turn if the move was done
                change_player_that_is_playing();
                // getting the check state after the move
                int check_state_after_move = is_check(WHITE, bitboards, chess_log);
                // undo the last move made
                undo_last_move_AI();
                // if the player is not in check after the move, then there is a possible move
                if (check_state_after_move == NO_CHECK && get_king_index(bitboards, WHITE) != -1){
                    // reallocating the valid moves array if needed
                    if (*nb_moves >= max_size_valid_moves_array){
                        valid_moves = realloc(valid_moves, max_size_valid_moves_array_extended * sizeof(int*));
                        // looking for realloc errors
                        if (valid_moves == NULL){
                            printf("Error: not enough memory to reallocate the valid moves array\n");
                            return NULL;
                        }
                    }
                    // incrementing the number of moves
                    valid_moves[*nb_moves] = move_value;
                    (*nb_moves)++;
                }
            }
        }
        else if (game_settings->color_of_player_that_is_playing == BLACK){
            // if a left en passant is possible, we simulate the move and add it to the valid moves if the player is not in check after the move
            if (is_en_passant_possible(BLACK, bitboards, from_index, from_index-9, chess_log)){
                int to_index = from_index-9;
                int flag = En_Passant_Flag;
                int piece_taken_type = PAWN_WHITE;
                // adding into a move value the information of the move                    
                int move_value = get_move_value(from_index, to_index, flag);
                // udpate the first part of the log 
                update_log(move_value, piece_taken_type);
                // all put in a make move function 
                make_move(from_index, to_index, flag, PAWN_BLACK);
                // updating the log with all the castle related information
                update_castle_state_in_log(from_index, to_index, flag, WHITE);
                // changing the player that is playing for the next turn if the move was done
                change_player_that_is_playing();
                // getting the check state after the move
                int check_state_after_move = is_check(BLACK, bitboards, chess_log);
                // undo the last move made
                undo_last_move_AI();
                // if the player is not in check after the move, then there is a possible move
                if (check_state_after_move == NO_CHECK && get_king_index(bitboards, BLACK) != -1){
                    // reallocating the valid moves array if needed
                    if (*nb_moves >= max_size_valid_moves_array){
                        valid_moves = realloc(valid_moves, max_size_valid_moves_array_extended * sizeof(int*));
                        // looking for realloc errors
                        if (valid_moves == NULL){
                            printf("Error: not enough memory to reallocate the valid moves array\n");
                            return NULL;
                        }
                    }
                    // incrementing the number of moves
                    valid_moves[*nb_moves] = move_value;
                    (*nb_moves)++;
                }
            }
            // if a right en passant is possible, we simulate the move and add it to the valid moves if the player is not in check after the move
            if (is_en_passant_possible(BLACK, bitboards, from_index, from_index-7, chess_log)){
                int to_index = from_index-7;
                int flag = En_Passant_Flag;
                int piece_taken_type = PAWN_WHITE;
                // adding into a move value the information of the move
                int move_value = get_move_value(from_index, to_index, flag);
                // udpate the first part of the log
                update_log(move_value, piece_taken_type);
                // all put in a make move function
                make_move(from_index, to_index, flag, PAWN_BLACK);
                // updating the log with all the castle related information
                update_castle_state_in_log(from_index, to_index, flag, WHITE);
                // changing the player that is playing for the next turn if the move was done
                change_player_that_is_playing();
                // getting the check state after the move
                int check_state_after_move = is_check(BLACK, bitboards, chess_log);
                // undo the last move made
                undo_last_move_AI();
                // if the player is not in check after the move, then there is a possible move
                if (check_state_after_move == NO_CHECK && get_king_index(bitboards, BLACK) != -1){
                    // reallocating the valid moves array if needed
                    if (*nb_moves >= max_size_valid_moves_array){
                        valid_moves = realloc(valid_moves, max_size_valid_moves_array_extended * sizeof(int*));
                        // looking for realloc errors
                        if (valid_moves == NULL){
                            printf("Error: not enough memory to reallocate the valid moves array\n");
                            return NULL;
                        }
                    }
                    // incrementing the number of moves
                    valid_moves[*nb_moves] = move_value;
                    (*nb_moves)++;
                }
            }
        }
        // if the piece is a white pawn 
        if (type_of_piece == PAWN_WHITE){
            bit_board white_pawn_moves = calculate_pawn_moves_with_blockers(from_index, WHITE, bitboards[WHITE_PIECES] | bitboards[BLACK_PIECES]);
            // getting all to indexes where the pawn can go
            while (white_pawn_moves) {
                // Get the index of the least significant bit that is set
                int to_index = __builtin_ctzll(white_pawn_moves);
                int flag = No_Flag;
                int piece_taken_type = NOTHING;
                // Clear the least significant '1' bit
                white_pawn_moves &= white_pawn_moves - 1;
                // if there is a piece of the same color at the to_index, we don't need to check the possible moves
                if ((bitboards[WHITE_PIECES] & (1ULL << to_index))){
                    continue;
                }
                // we now can simulate each moves and check if the player is not in check after the move
                if (has_pawn_moved_two_squares(WHITE, bitboards, from_index, to_index)){
                    flag = Pawn_Two_Up_Flag;
                }
                else if (is_promotion_possible(WHITE, bitboards, from_index, to_index)){
                    flag = Promote_To_Queen_Flag;
                }
                // if the move is a capture, we need to know if it's a capture, to play the sound of the capture (not needed when we will consider the AI move as a useful part)
                if (will_capture(WHITE, bitboards, to_index)){
                    piece_taken_type = get_type_of_piece(bitboards, to_index);
                }
                // adding into a move value the information of the move
                int move_value = get_move_value(from_index, to_index, flag);
                // udpate the first part of the log
                update_log(move_value, piece_taken_type);
                // all put in a make move function
                make_move(from_index, to_index, flag, PAWN_WHITE);
                if (flag == Promote_To_Queen_Flag){
                    // the AI will always promote to a queen
                    add_flag_to_move(&chess_log->moves[chess_log->actual_size-1]->move_value, Promote_To_Queen_Flag);
                    bitboards[QUEEN_WHITE] |= (1ULL << to_index);
                    bitboards[PAWN_WHITE] &= ~(1ULL << to_index);
                }
                // updating the log with all the castle related information
                update_castle_state_in_log(from_index, to_index, flag, BLACK);
                // changing the player that is playing for the next turn if the move was done
                change_player_that_is_playing();
                // getting the check state after the move
                int check_state_after_move = is_check(WHITE, bitboards, chess_log);
                // undo the last move made
                undo_last_move_AI();
                // if the player is not in check after the move, then there is a possible move
                if (check_state_after_move == NO_CHECK && get_king_index(bitboards, WHITE) != -1 && piece_taken_type != NOTHING){
                    // reallocating the valid moves array if needed
                    if (*nb_moves >= max_size_valid_moves_array){
                        valid_moves = realloc(valid_moves, max_size_valid_moves_array_extended * sizeof(int*));
                        // looking for realloc errors
                        if (valid_moves == NULL){
                            printf("Error: not enough memory to reallocate the valid moves array\n");
                            return NULL;
                        }
                    }
                    // incrementing the number of moves
                    valid_moves[*nb_moves] = move_value;
                    (*nb_moves)++;
                }
            }
        }
        // if the piece is a black pawn
        else if (type_of_piece == PAWN_BLACK){
            bit_board black_pawn_moves = calculate_pawn_moves_with_blockers(from_index, BLACK, bitboards[WHITE_PIECES] | bitboards[BLACK_PIECES]);
            // getting all to indexes where the pawn can go
            while (black_pawn_moves) {
                // Get the index of the least significant bit that is set
                int to_index = __builtin_ctzll(black_pawn_moves);
                int flag = No_Flag;
                int piece_taken_type = NOTHING;
                // Clear the least significant '1' bit
                black_pawn_moves &= black_pawn_moves - 1;
                // if there is a piece of the same color at the to_index, we don't need to check the possible moves
                if ((bitboards[BLACK_PIECES] & (1ULL << to_index))){
                    continue;
                }
                // we now can simulate each moves and check if the player is not in check after the move
                if (has_pawn_moved_two_squares(BLACK, bitboards, from_index, to_index)){
                    flag = Pawn_Two_Up_Flag;
                }
                else if (is_promotion_possible(WHITE, bitboards, from_index, to_index)){
                    flag = Promote_To_Queen_Flag;
                }
                // if the move is a capture, we need to know if it's a capture, to play the sound of the capture (not needed when we will consider the AI move as a useful part)
                if (will_capture(BLACK, bitboards, to_index)){
                    piece_taken_type = get_type_of_piece(bitboards, to_index);
                }
                // adding into a move value the information of the move
                int move_value = get_move_value(from_index, to_index, flag);
                // udpate the first part of the log
                update_log(move_value, piece_taken_type);
                // all put in a make move function
                make_move(from_index, to_index, flag, PAWN_BLACK);
                if (flag == Promote_To_Queen_Flag){
                    // the AI will always promote to a queen
                    add_flag_to_move(&chess_log->moves[chess_log->actual_size-1]->move_value, Promote_To_Queen_Flag);
                    bitboards[QUEEN_BLACK] |= (1ULL << to_index);
                    bitboards[PAWN_BLACK] &= ~(1ULL << to_index);
                }
                // updating the log with all the castle related information
                update_castle_state_in_log(from_index, to_index, flag, WHITE);
                // changing the player that is playing for the next turn if the move was done
                change_player_that_is_playing();
                // getting the check state after the move
                int check_state_after_move = is_check(BLACK, bitboards, chess_log);
                // undo the last move made
                undo_last_move_AI();
                // if the player is not in check after the move, then there is a possible move
                if (check_state_after_move == NO_CHECK && get_king_index(bitboards, BLACK) != -1 && piece_taken_type != NOTHING){
                    // reallocating the valid moves array if needed
                    if (*nb_moves >= max_size_valid_moves_array){
                        valid_moves = realloc(valid_moves, max_size_valid_moves_array_extended * sizeof(int*));
                        // looking for realloc errors
                        if (valid_moves == NULL){
                            printf("Error: not enough memory to reallocate the valid moves array\n");
                            return NULL;
                        }
                    }
                    // incrementing the number of moves
                    valid_moves[*nb_moves] = move_value;
                    (*nb_moves)++;
                }
            }
        }
        // if the piece is a white knight
        else if (type_of_piece == KNIGHT_WHITE){
            bit_board white_knight_moves = precomputed_knight_attacks[from_index];
            // getting all to indexes where the knight can go
            while (white_knight_moves) {
                // Get the index of the least significant bit that is set
                int to_index = __builtin_ctzll(white_knight_moves);
                int flag = No_Flag;
                int piece_taken_type = NOTHING;
                // Clear the least significant '1' bit
                white_knight_moves &= white_knight_moves - 1;
                // if there is a piece of the same color at the to_index, we don't need to check the possible moves
                if ((bitboards[WHITE_PIECES] & (1ULL << to_index))){
                    continue;
                }
                // we now can simulate each moves and check if the player is not in check after the move
                // if the move is a capture, we need to know if it's a capture, to play the sound of the capture (not needed when we will consider the AI move as a useful part)
                if (will_capture(WHITE, bitboards, to_index)){
                    piece_taken_type = get_type_of_piece(bitboards, to_index);
                }
                // adding into a move value the information of the move
                int move_value = get_move_value(from_index, to_index, flag);
                // udpate the first part of the log
                update_log(move_value, piece_taken_type);
                // all put in a make move function
                make_move(from_index, to_index, flag, KNIGHT_WHITE);
                // updating the log with all the castle related information
                update_castle_state_in_log(from_index, to_index, flag, BLACK);
                // changing the player that is playing for the next turn if the move was done
                change_player_that_is_playing();
                // getting the check state after the move
                int check_state_after_move = is_check(WHITE, bitboards, chess_log);
                // undo the last move made
                undo_last_move_AI();
                // if the player is not in check after the move, then there is a possible move
                if (check_state_after_move == NO_CHECK && get_king_index(bitboards, WHITE) != -1 && piece_taken_type != NOTHING){
                    // reallocating the valid moves array if needed
                    if (*nb_moves >= max_size_valid_moves_array){
                        valid_moves = realloc(valid_moves, max_size_valid_moves_array_extended * sizeof(int*));
                        // looking for realloc errors
                        if (valid_moves == NULL){
                            printf("Error: not enough memory to reallocate the valid moves array\n");
                            return NULL;
                        }
                    }
                    // incrementing the number of moves
                    valid_moves[*nb_moves] = move_value;
                    (*nb_moves)++;
                }
            }
        }
        // if the piece is a black knight 
        else if (type_of_piece == KNIGHT_BLACK){
            bit_board black_knight_moves = precomputed_knight_attacks[from_index];
            // getting all to indexes where the knight can go
            while (black_knight_moves) {
                // Get the index of the least significant bit that is set
                int to_index = __builtin_ctzll(black_knight_moves);
                int flag = No_Flag;
                int piece_taken_type = NOTHING;
                // Clear the least significant '1' bit
                black_knight_moves &= black_knight_moves - 1;
                // if there is a piece of the same color at the to_index, we don't need to check the possible moves
                if ((bitboards[BLACK_PIECES] & (1ULL << to_index))){
                    continue;
                }
                // we now can simulate each moves and check if the player is not in check after the move
                // if the move is a capture, we need to know if it's a capture, to play the sound of the capture (not needed when we will consider the AI move as a useful part)
                if (will_capture(BLACK, bitboards, to_index)){
                    piece_taken_type = get_type_of_piece(bitboards, to_index);
                }
                // adding into a move value the information of the move
                int move_value = get_move_value(from_index, to_index, flag);
                // udpate the first part of the log
                update_log(move_value, piece_taken_type);
                // all put in a make move function
                make_move(from_index, to_index, flag, KNIGHT_BLACK);
                // updating the log with all the castle related information
                update_castle_state_in_log(from_index, to_index, flag, WHITE);
                // changing the player that is playing for the next turn if the move was done
                change_player_that_is_playing();
                // getting the check state after the move
                int check_state_after_move = is_check(BLACK, bitboards, chess_log);
                // undo the last move made
                undo_last_move_AI();
                // if the player is not in check after the move, then there is a possible move
                if (check_state_after_move == NO_CHECK && get_king_index(bitboards, BLACK) != -1 && piece_taken_type != NOTHING){
                    // reallocating the valid moves array if needed
                    if (*nb_moves >= max_size_valid_moves_array){
                        valid_moves = realloc(valid_moves, max_size_valid_moves_array_extended * sizeof(int*));
                        // looking for realloc errors
                        if (valid_moves == NULL){
                            printf("Error: not enough memory to reallocate the valid moves array\n");
                            return NULL;
                        }
                    }
                    // incrementing the number of moves
                    valid_moves[*nb_moves] = move_value;
                    (*nb_moves)++;
                }
            }
        }
        // if the piece is a sliding piece
        else if (type_of_piece == ROOK_WHITE || type_of_piece == BISHOP_WHITE || type_of_piece == QUEEN_WHITE){
            // if the piece is a white rook or a white queen 
            if (type_of_piece == ROOK_WHITE || type_of_piece == QUEEN_WHITE){
                bit_board white_rook_moves = calculate_rook_attacks_with_blockers(from_index, bitboards[WHITE_PIECES] | bitboards[BLACK_PIECES]);
                // getting all to indexes where the rook can go
                while (white_rook_moves) {
                    // Get the index of the least significant bit that is set
                    int to_index = __builtin_ctzll(white_rook_moves);
                    int flag = No_Flag;
                    int piece_taken_type = NOTHING;
                    // Clear the least significant '1' bit
                    white_rook_moves &= white_rook_moves - 1;
                    // if there is a piece of the same color at the to_index, we don't need to check the possible moves
                    if ((bitboards[WHITE_PIECES] & (1ULL << to_index))){
                        continue;
                    }
                    // we now can simulate each moves and check if the player is not in check after the move
                    // if the move is a capture, we need to know if it's a capture, to play the sound of the capture (not needed when we will consider the AI move as a useful part)
                    if (will_capture(WHITE, bitboards, to_index)){
                        piece_taken_type = get_type_of_piece(bitboards, to_index);
                    }
                    // adding into a move value the information of the move
                    int move_value = get_move_value(from_index, to_index, flag);
                    // udpate the first part of the log
                    update_log(move_value, piece_taken_type);
                    // all put in a make move function
                    make_move(from_index, to_index, flag, (type_of_piece == ROOK_WHITE) ? ROOK_WHITE : QUEEN_WHITE);
                    // updating the log with all the castle related information
                    update_castle_state_in_log(from_index, to_index, flag, BLACK);
                    // changing the player that is playing for the next turn if the move was done
                    change_player_that_is_playing();
                    // getting the check state after the move
                    int check_state_after_move = is_check(WHITE, bitboards, chess_log);
                    // undo the last move made
                    undo_last_move_AI();
                    // if the player is not in check after the move, then there is a possible move
                    if (check_state_after_move == NO_CHECK && get_king_index(bitboards, WHITE) != -1 && piece_taken_type != NOTHING){
                        // reallocating the valid moves array if needed
                        if (*nb_moves >= max_size_valid_moves_array){
                            valid_moves = realloc(valid_moves, max_size_valid_moves_array_extended * sizeof(int*));
                            // looking for realloc errors
                            if (valid_moves == NULL){
                                printf("Error: not enough memory to reallocate the valid moves array\n");
                                return NULL;
                            }
                        }
                        // incrementing the number of moves
                        valid_moves[*nb_moves] = move_value;
                        (*nb_moves)++;
                    }
                }
            }
              // if the piece is a white bishop or a white queen 
            if (type_of_piece == BISHOP_WHITE || type_of_piece == QUEEN_WHITE){
                bit_board white_bishop_moves = calculate_bishop_attacks_with_blockers(from_index, bitboards[WHITE_PIECES] | bitboards[BLACK_PIECES]);
                // getting all to indexes where the bishop can go
                while (white_bishop_moves) {
                    // Get the index of the least significant bit that is set
                    int to_index = __builtin_ctzll(white_bishop_moves);
                    int flag = No_Flag;
                    int piece_taken_type = NOTHING;
                    // Clear the least significant '1' bit
                    white_bishop_moves &= white_bishop_moves - 1;
                    // if there is a piece of the same color at the to_index, we don't need to check the possible moves
                    if ((bitboards[WHITE_PIECES] & (1ULL << to_index))){
                        continue;
                    }
                    // we now can simulate each moves and check if the player is not in check after the move
                    // if the move is a capture, we need to know if it's a capture, to play the sound of the capture (not needed when we will consider the AI move as a useful part)
                    if (will_capture(WHITE, bitboards, to_index)){
                        piece_taken_type = get_type_of_piece(bitboards, to_index);
                    }
                    // adding into a move value the information of the move
                    int move_value = get_move_value(from_index, to_index, flag);
                    // udpate the first part of the log
                    update_log(move_value, piece_taken_type);
                    // all put in a make move function
                    make_move(from_index, to_index, flag, (type_of_piece == BISHOP_WHITE) ? BISHOP_WHITE : QUEEN_WHITE);
                    // updating the log with all the castle related information
                    update_castle_state_in_log(from_index, to_index, flag, BLACK);
                    // changing the player that is playing for the next turn if the move was done
                    change_player_that_is_playing();
                    // getting the check state after the move
                    int check_state_after_move = is_check(WHITE, bitboards, chess_log);
                    // undo the last move made
                    undo_last_move_AI();
                    // if the player is not in check after the move, then there is a possible move
                    if (check_state_after_move == NO_CHECK && get_king_index(bitboards, WHITE) != -1 && piece_taken_type != NOTHING){
                        // reallocating the valid moves array if needed
                        if (*nb_moves >= max_size_valid_moves_array){
                            valid_moves = realloc(valid_moves, max_size_valid_moves_array_extended * sizeof(int*));
                            // looking for realloc errors
                            if (valid_moves == NULL){
                                printf("Error: not enough memory to reallocate the valid moves array\n");
                                return NULL;
                            }
                        }
                        // incrementing the number of moves
                        valid_moves[*nb_moves] = move_value;
                        (*nb_moves)++;
                    }
                }
            }
        }
        else if (type_of_piece == ROOK_BLACK || type_of_piece == BISHOP_BLACK || type_of_piece == QUEEN_BLACK){
            // if the piece is a black rook or a black queen 
            if (type_of_piece == ROOK_BLACK || type_of_piece == QUEEN_BLACK){
                bit_board black_rook_moves = calculate_rook_attacks_with_blockers(from_index, bitboards[WHITE_PIECES] | bitboards[BLACK_PIECES]);
                // getting all to indexes where the rook can go
                while (black_rook_moves) {
                    // Get the index of the least significant bit that is set
                    int to_index = __builtin_ctzll(black_rook_moves);
                    int flag = No_Flag;
                    int piece_taken_type = NOTHING;
                    // Clear the least significant '1' bit
                    black_rook_moves &= black_rook_moves - 1;
                    // if there is a piece of the same color at the to_index, we don't need to check the possible moves
                    if ((bitboards[BLACK_PIECES] & (1ULL << to_index))){
                        continue;
                    }
                    // we now can simulate each moves and check if the player is not in check after the move
                    // if the move is a capture, we need to know if it's a capture, to play the sound of the capture (not needed when we will consider the AI move as a useful part)
                    if (will_capture(BLACK, bitboards, to_index)){
                        piece_taken_type = get_type_of_piece(bitboards, to_index);
                    }
                    // adding into a move value the information of the move
                    int move_value = get_move_value(from_index, to_index, flag);
                    // udpate the first part of the log
                    update_log(move_value, piece_taken_type);
                    // all put in a make move function
                    make_move(from_index, to_index, flag, (type_of_piece == ROOK_BLACK) ? ROOK_BLACK : QUEEN_BLACK);
                    // updating the log with all the castle related information
                    update_castle_state_in_log(from_index, to_index, flag, WHITE);
                    // changing the player that is playing for the next turn if the move was done
                    change_player_that_is_playing();
                    // getting the check state after the move
                    int check_state_after_move = is_check(BLACK, bitboards, chess_log);
                    // undo the last move made
                    undo_last_move_AI();
                    // if the player is not in check after the move, then there is a possible move
                    if (check_state_after_move == NO_CHECK && get_king_index(bitboards, BLACK) != -1 && piece_taken_type != NOTHING){
                        // reallocating the valid moves array if needed
                        if (*nb_moves >= max_size_valid_moves_array){
                            valid_moves = realloc(valid_moves, max_size_valid_moves_array_extended * sizeof(int*));
                            // looking for realloc errors
                            if (valid_moves == NULL){
                                printf("Error: not enough memory to reallocate the valid moves array\n");
                                return NULL;
                            }
                        }
                        // incrementing the number of moves
                        valid_moves[*nb_moves] = move_value;
                        (*nb_moves)++;
                    }
                }
            }
            // if the piece is a black bishop or a black queen 
            if (type_of_piece == BISHOP_BLACK || type_of_piece == QUEEN_BLACK){
                bit_board black_bishop_moves = calculate_bishop_attacks_with_blockers(from_index, bitboards[WHITE_PIECES] | bitboards[BLACK_PIECES]);
                // getting all to indexes where the bishop can go
                while (black_bishop_moves) {
                    // Get the index of the least significant bit that is set
                    int to_index = __builtin_ctzll(black_bishop_moves);
                    int flag = No_Flag;
                    int piece_taken_type = NOTHING;
                    // Clear the least significant '1' bit
                    black_bishop_moves &= black_bishop_moves - 1;
                    // if there is a piece of the same color at the to_index, we don't need to check the possible moves
                    if ((bitboards[BLACK_PIECES] & (1ULL << to_index))){
                        continue;
                    }
                    // we now can simulate each moves and check if the player is not in check after the move
                    // if the move is a capture, we need to know if it's a capture, to play the sound of the capture (not needed when we will consider the AI move as a useful part)
                    if (will_capture(BLACK, bitboards, to_index)){
                        piece_taken_type = get_type_of_piece(bitboards, to_index);
                    }
                    // adding into a move value the information of the move
                    int move_value = get_move_value(from_index, to_index, flag);
                    // udpate the first part of the log
                    update_log(move_value, piece_taken_type);
                    // all put in a make move function
                    make_move(from_index, to_index, flag, (type_of_piece == BISHOP_BLACK) ? BISHOP_BLACK : QUEEN_BLACK);
                    // updating the log with all the castle related information
                    update_castle_state_in_log(from_index, to_index, flag, WHITE);
                    // changing the player that is playing for the next turn if the move was done
                    change_player_that_is_playing();
                    // getting the check state after the move
                    int check_state_after_move = is_check(BLACK, bitboards, chess_log);
                    // undo the last move made
                    undo_last_move_AI();
                    // if the player is not in check after the move, then there is a possible move
                    if (check_state_after_move == NO_CHECK && get_king_index(bitboards, BLACK) != -1 && piece_taken_type != NOTHING){
                        // reallocating the valid moves array if needed
                        if (*nb_moves >= max_size_valid_moves_array){
                            valid_moves = realloc(valid_moves, max_size_valid_moves_array_extended * sizeof(int*));
                            // looking for realloc errors
                            if (valid_moves == NULL){
                                printf("Error: not enough memory to reallocate the valid moves array\n");
                                return NULL;
                            }
                        }
                        // incrementing the number of moves
                        valid_moves[*nb_moves] = move_value;
                        (*nb_moves)++;
                    }
                }
            }
        }
        // if the piece is a white king 
        else if (type_of_piece == KING_WHITE){
            bit_board white_king_moves = precomputed_king_attacks[from_index];
            // getting all to indexes where the king can go
            while (white_king_moves) {
                // Get the index of the least significant bit that is set
                int to_index = __builtin_ctzll(white_king_moves);
                int flag = No_Flag;
                int piece_taken_type = NOTHING;
                // Clear the least significant '1' bit
                white_king_moves &= white_king_moves - 1;
                // if there is a piece of the same color at the to_index, we don't need to check the possible moves
                if ((bitboards[WHITE_PIECES] & (1ULL << to_index))){
                    continue;
                }
                // we now can simulate each moves and check if the player is not in check after the move
                // if the move is a capture, we need to know if it's a capture, to play the sound of the capture (not needed when we will consider the AI move as a useful part)
                if (will_capture(WHITE, bitboards, to_index)){
                    piece_taken_type = get_type_of_piece(bitboards, to_index);
                }
                // adding into a move value the information of the move
                int move_value = get_move_value(from_index, to_index, flag);
                // udpate the first part of the log
                update_log(move_value, piece_taken_type);
                // all put in a make move function
                make_move(from_index, to_index, flag, KING_WHITE);
                // updating the log with all the castle related information
                update_castle_state_in_log(from_index, to_index, flag, BLACK);
                // changing the player that is playing for the next turn if the move was done
                change_player_that_is_playing();
                // getting the check state after the move
                int check_state_after_move = is_check(WHITE, bitboards, chess_log);
                // undo the last move made
                undo_last_move_AI();
                // if the player is not in check after the move, then there is a possible move
                if (check_state_after_move == NO_CHECK && get_king_index(bitboards, WHITE) != -1 && piece_taken_type != NOTHING){
                    // reallocating the valid moves array if needed
                    if (*nb_moves >= max_size_valid_moves_array){
                        valid_moves = realloc(valid_moves, max_size_valid_moves_array_extended * sizeof(int*));
                        // looking for realloc errors
                        if (valid_moves == NULL){
                            printf("Error: not enough memory to reallocate the valid moves array\n");
                            return NULL;
                        }
                    }
                    // incrementing the number of moves
                    valid_moves[*nb_moves] = move_value;
                    (*nb_moves)++;
                }
            }
        }
        // if the piece is a black king 
        else if (type_of_piece == KING_BLACK){
            bit_board black_king_moves = precomputed_king_attacks[from_index];
            // getting all to indexes where the king can go
            while (black_king_moves) {
                // Get the index of the least significant bit that is set
                int to_index = __builtin_ctzll(black_king_moves);
                int flag = No_Flag;
                int piece_taken_type = NOTHING;
                // Clear the least significant '1' bit
                black_king_moves &= black_king_moves - 1;
                // if there is a piece of the same color at the to_index, we don't need to check the possible moves
                if ((bitboards[BLACK_PIECES] & (1ULL << to_index))){
                    continue;
                }
                // we now can simulate each moves and check if the player is not in check after the move
                // if the move is a capture, we need to know if it's a capture, to play the sound of the capture (not needed when we will consider the AI move as a useful part)
                if (will_capture(BLACK, bitboards, to_index)){
                    piece_taken_type = get_type_of_piece(bitboards, to_index);
                }
                // adding into a move value the information of the move
                int move_value = get_move_value(from_index, to_index, flag);
                // udpate the first part of the log
                update_log(move_value, piece_taken_type);
                // all put in a make move function
                make_move(from_index, to_index, flag, KING_BLACK);
                // updating the log with all the castle related information
                update_castle_state_in_log(from_index, to_index, flag, WHITE);
                // changing the player that is playing for the next turn if the move was done
                change_player_that_is_playing();
                // getting the check state after the move
                int check_state_after_move = is_check(BLACK, bitboards, chess_log);
                // undo the last move made
                undo_last_move_AI();
                // if the player is not in check after the move, then there is a possible move
                if (check_state_after_move == NO_CHECK && get_king_index(bitboards, BLACK) != -1 && piece_taken_type != NOTHING){
                    // reallocating the valid moves array if needed
                    if (*nb_moves >= max_size_valid_moves_array){
                        valid_moves = realloc(valid_moves, max_size_valid_moves_array_extended * sizeof(int*));
                        // looking for realloc errors
                        if (valid_moves == NULL){
                            printf("Error: not enough memory to reallocate the valid moves array\n");
                            return NULL;
                        }
                    }
                    // incrementing the number of moves
                    valid_moves[*nb_moves] = move_value;
                    (*nb_moves)++;
                }
            }
        }
    
    }

    // returning the valid moves array
    return valid_moves;

}


void make_move_AI(move move_value){

    // getting the from and to index of the move as well as the flag
    int from_index = get_from_square(move_value);
    int to_index = get_to_square(move_value);
    int flag = get_flag(move_value);
    bool is_pawn_promotion_happening = false;
    if (flag == Promote_To_Queen_Flag){
        is_pawn_promotion_happening = true;
    }

    // getting the type of the captured piece (wether by an en passant or a normal capture)
    int piece_taken_type = NOTHING;
    if (flag == En_Passant_Flag){
        piece_taken_type = get_type_of_piece(bitboards, (game_settings->color_of_player_that_is_playing == WHITE) ? to_index-8 : to_index+8);
    }
    if (will_capture(game_settings->color_of_player_that_is_playing, bitboards, to_index)){
        piece_taken_type = get_type_of_piece(bitboards, to_index);
    }

    // getting the type of piece that will be moved
    int type_move_legal_attacking = get_type_of_piece(bitboards, from_index);

    // udpate the first part of the log and the captured piece and score 
    update_log(move_value, piece_taken_type);
    // all put in a make move function
    make_move(from_index, to_index, flag, type_move_legal_attacking);
    if (is_pawn_promotion_happening){
        // the AI will always promote to a queen
        add_flag_to_move(&chess_log->moves[chess_log->actual_size-1]->move_value, Promote_To_Queen_Flag);
        if (game_settings->color_of_player_that_is_playing == WHITE){
            bitboards[QUEEN_WHITE] |= (1ULL << to_index);
            bitboards[PAWN_WHITE] &= ~(1ULL << to_index);
        }
        else if (game_settings->color_of_player_that_is_playing == BLACK){
            bitboards[QUEEN_BLACK] |= (1ULL << to_index);
            bitboards[PAWN_BLACK] &= ~(1ULL << to_index);
        }
    }
    // updating the log with all the castle related information
    update_castle_state_in_log(from_index, to_index, flag, 1-game_settings->color_of_player_that_is_playing);
    // changing the player that is playing for the next turn if the move was done
    change_player_that_is_playing();
                    
}


void undo_last_move_AI(){

    // if there is no move in the log, we can't undo a move
    if (chess_log->actual_size == 0){
        return;
    }

    // getting the information of the last move
    int from = get_from_square(chess_log->moves[chess_log->actual_size-1]->move_value);
    int to = get_to_square(chess_log->moves[chess_log->actual_size-1]->move_value);
    int flag = get_flag(chess_log->moves[chess_log->actual_size-1]->move_value);
    int moved_piece_type = get_type_of_piece(bitboards, to);
    // if there has been a promotion, we need to remove the piece that has been promoted, so we change back the type to a pawn
    if (is_promotion_flag(flag)){
        bitboards[moved_piece_type] &= ~(1ULL << to);
        if (game_settings->color_of_player_that_is_playing == WHITE){
            moved_piece_type = PAWN_BLACK;
        }
        else if (game_settings->color_of_player_that_is_playing == BLACK){
            moved_piece_type = PAWN_WHITE;
        }
    }
    int captured_piece_type = chess_log->moves[chess_log->actual_size-1]->captured_piece_type;
    // making the move in the opposite way
    move_piece(moved_piece_type, 1-game_settings->color_of_player_that_is_playing, to, from);
    // if there has been a capture, we need to put back the piece that has been taken (normal capture or en passant)
    if (captured_piece_type != NOTHING){
        // since the move has been made, we return the piece of the player that is playing now, so the on that was not playing before
        if (flag == En_Passant_Flag){
            // we put back the pawn that has been taken
            if (game_settings->color_of_player_that_is_playing == WHITE){
                bitboards[PAWN_WHITE] |= (1ULL << (to+8));
                bitboards[WHITE_PIECES] |= (1ULL << (to+8));
            }
            else if (game_settings->color_of_player_that_is_playing == BLACK){
                bitboards[PAWN_BLACK] |= (1ULL << (to-8));
                bitboards[BLACK_PIECES] |= (1ULL << (to-8));
            }
        }
        else {
            // we put back the piece that has been taken
            bitboards[captured_piece_type] |= (1ULL << to);

            if (game_settings->color_of_player_that_is_playing == WHITE){
                bitboards[WHITE_PIECES] |= (1ULL << to);
            }
            else if (game_settings->color_of_player_that_is_playing == BLACK){
                bitboards[BLACK_PIECES] |= (1ULL << to);
            }
        }
    }
    // if there has been a castle, we need to undo the castle that has been done
    if (flag == Castle_Flag){
        // putting back the rook that has been moved
        if (from == 4 && to == 6){
            bitboards[ROOK_WHITE] &= ~(1ULL << 5);
            bitboards[ROOK_WHITE] |= (1ULL << 7);
            bitboards[WHITE_PIECES] &= ~(1ULL << 5);
            bitboards[WHITE_PIECES] |= (1ULL << 7);
        }
        else if (from == 4 && to == 2){
            bitboards[ROOK_WHITE] &= ~(1ULL << 3);
            bitboards[ROOK_WHITE] |= (1ULL << 0);
            bitboards[WHITE_PIECES] &= ~(1ULL << 3);
            bitboards[WHITE_PIECES] |= (1ULL << 0);
        }
        else if (from == 60 && to == 62){
            bitboards[ROOK_BLACK] &= ~(1ULL << 61);
            bitboards[ROOK_BLACK] |= (1ULL << 63);
            bitboards[BLACK_PIECES] &= ~(1ULL << 61);
            bitboards[BLACK_PIECES] |= (1ULL << 63);
        }
        else if (from == 60 && to == 58){
            bitboards[ROOK_BLACK] &= ~(1ULL << 59);
            bitboards[ROOK_BLACK] |= (1ULL << 56);
            bitboards[BLACK_PIECES] &= ~(1ULL << 59);
            bitboards[BLACK_PIECES] |= (1ULL << 56);
        }
    }

    // we remove the last move from the log
    remove_last_move_from_log();
    // if there has been a castle, we need to undo the castle that has been done in the log parameters, it's done when we suppress the last element of the log

    // changing the player that is playing
    change_player_that_is_playing();

}
