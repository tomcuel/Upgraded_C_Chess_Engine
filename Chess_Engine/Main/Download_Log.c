#include "Download_Log.h"


void download_log(){

    // creating a file 
    FILE* file = fopen("game_log.txt", "w");
    // checking if the file was created
    if (file == NULL){
        printf("Error creating the file\n");
        return;
    }


    // writing the formal log 
    fprintf(file, "Formal Log :\n");

    int color_of_player_have_to_play = WHITE;
    for (int i = 0; i < chess_log->actual_size; i++){
        // adding the number of the move
        if (i % 2 == 0){
            fprintf(file, "%d.", i/2 + 1);
        }
        // adding the move
        // getting the string we want to display
        char* move_str = malloc(10*sizeof(char));

        move move_played = chess_log->moves[i]->move_value;
        // first we need to treat special cases before : 
        if (get_flag(move_played) == Castle_Flag){
            // if the castle is a short castle
            if (get_to_square(move_played) == 6 || get_to_square(move_played) == 62){
                sprintf(move_str, "O-O");
            }
            // if the castle is a long castle
            else if (get_to_square(move_played) == 2 || get_to_square(move_played) == 58){
                sprintf(move_str, "O-O-O");
            }
        }
        else {
            
            // if there is a promotion we need to add the piece that the pawn is promoted to by adding "=Q" for a queen, "=R" for a rook, "=B" for a bishop and "=N" for a knight
            // others special rules needs to be applied if there is a capture 
            if (is_promotion_flag(get_flag(move_played))){
                // if there is a capture during the promotion
                if (chess_log->moves[i]->captured_piece_type != NOTHING){
                    sprintf(move_str, "%s%c", move_str, get_file(get_from_square(move_played)) + 'a');
                    sprintf(move_str, "%sx", move_str);
                }

                // adding the square where the piece has been going (the destination square) 
                sprintf(move_str, "%s%c%d", move_str, get_file(get_to_square(move_played)) + 'a', get_rank(get_to_square(move_played)) + 1);

                // adding the piece that the pawn has been promoted to
                int promoted_flag = get_flag(move_played);
                if (promoted_flag == Promote_To_Queen_Flag){
                    sprintf(move_str, "%s=Q", move_str);
                }
                else if (promoted_flag == Promote_To_Rook_Flag){
                    sprintf(move_str, "%s=R", move_str);
                }
                else if (promoted_flag == Promote_To_Bishop_Flag){
                    sprintf(move_str, "%s=B", move_str);
                }
                else if (promoted_flag == Promote_To_Knight_Flag){
                    sprintf(move_str, "%s=N", move_str);
                }
            }
            // no promotion, we do the normal thing
            else {
                //  for the different pieces : K=King, Q=Queen, R=Rook, B=Bishop, N=Knight, nothing for pawn
                // since we are adding this log info after a move was played, the piece that we move is the one that is at the destination square
                int piece_moved = get_type_of_piece(bitboards_log->bitboards[i], get_to_square(move_played));
                // adding the letter corresponding to the piece moved in the move_str
                switch(piece_moved){
                    case PAWN_WHITE:
                        break;
                    case KNIGHT_WHITE:
                        sprintf(move_str, "N");
                        break;
                    case BISHOP_WHITE:
                        sprintf(move_str, "B");
                        break;
                    case ROOK_WHITE:
                        sprintf(move_str, "R");
                        break;
                    case QUEEN_WHITE:
                        sprintf(move_str, "Q");
                        break;
                    case KING_WHITE:
                        sprintf(move_str, "K");
                        break;
                    case PAWN_BLACK:
                        break;
                    case KNIGHT_BLACK:
                        sprintf(move_str, "N");
                        break;
                    case BISHOP_BLACK:
                        sprintf(move_str, "B");
                        break;
                    case ROOK_BLACK:
                        sprintf(move_str, "R");
                        break;
                    case QUEEN_BLACK:
                        sprintf(move_str, "Q");
                        break;
                    case KING_BLACK:
                        sprintf(move_str, "K");
                        break;
                }

                // if this a capture, we need to add an "x" before, if it's a pawn that is taking, we need to indicate its column before the "x"
                if (chess_log->moves[i]->captured_piece_type != NOTHING){
                    if (piece_moved == PAWN_WHITE || piece_moved == PAWN_BLACK){
                        sprintf(move_str, "%s%c", move_str, get_file(get_from_square(move_played)) + 'a');
                    }
                    sprintf(move_str, "%sx", move_str);
                }

                // adding the square where the piece has been going (the destination square) 
                sprintf(move_str, "%s%c%d", move_str, get_file(get_to_square(move_played)) + 'a', get_rank(get_to_square(move_played)) + 1);
            }

           
            // one parameter is the log (but the function always get the last element, no the one at the i-th move), we need to change the last element of the log to be the one at the i-th move and then putting it back
            move last_move = chess_log->moves[chess_log->actual_size-1]->move_value;
            chess_log->moves[chess_log->actual_size-1]->move_value = chess_log->moves[i]->move_value;
            int last_captured_piece_type = chess_log->moves[chess_log->actual_size-1]->captured_piece_type;
            chess_log->moves[chess_log->actual_size-1]->captured_piece_type = chess_log->moves[i]->captured_piece_type;
            castling_rights_flags last_castling_rights = chess_log->moves[chess_log->actual_size-1]->castling_rights;
            chess_log->moves[chess_log->actual_size-1]->castling_rights = chess_log->moves[i]->castling_rights;
            // same thing for the bitboards
            bit_board stored_bitboards[NUMBER_OF_BIBOARD]; 
            for (int j=0; j<NUMBER_OF_BIBOARD; j++){
                stored_bitboards[j] = bitboards[j];
            }
            for (int j=0; j<NUMBER_OF_BIBOARD; j++){
                bitboards[j] = bitboards_log->bitboards[i][j];
            }

            // at the end we add "+" if it's a check, "#" if it's a checkmate
            int check_state = get_check_state(1-color_of_player_have_to_play);
            if (check_state == CHECK){
                sprintf(move_str, "%s+", move_str);
            }
            else if (check_state == CHECK_MATE){
                sprintf(move_str, "%s#", move_str);
            }

            // putting back the last move in the log with the right values
            chess_log->moves[chess_log->actual_size-1]->move_value = last_move;
            chess_log->moves[chess_log->actual_size-1]->captured_piece_type = last_captured_piece_type;
            chess_log->moves[chess_log->actual_size-1]->castling_rights = last_castling_rights;
            // same thing for the bitboards
            for (int j=0; j<NUMBER_OF_BIBOARD; j++){
                bitboards[j] = stored_bitboards[j];
            }

        }

        // writing the move_str in the file
        fprintf(file, "%s ", move_str);

        // freeing the move_str
        free(move_str);

        if (color_of_player_have_to_play == WHITE){
            color_of_player_have_to_play = BLACK;
        }
        else {
            color_of_player_have_to_play = WHITE;
        }

    }

    
    // we store the game settings
    fprintf(file, "\n\nGame Settings :\n");
    fprintf(file, "Game Mode : %d\n", game_settings->game_mode);
    fprintf(file, "white_player_type : %d\n", game_settings->white_player_type);
    fprintf(file, "white_AI_difficulty : %d\n", game_settings->white_AI_difficulty);
    fprintf(file, "black_player_type : %d\n", game_settings->black_player_type);
    fprintf(file, "black_AI_difficulty : %d\n", game_settings->black_AI_difficulty);
    fprintf(file, "player_that_is_playing : %d\n", game_settings->player_that_is_playing);
    fprintf(file, "color_of_player_that_is_playing : %d\n", game_settings->color_of_player_that_is_playing);
    fprintf(file, "loosing_player : %d\n", game_settings->loosing_player);
    fprintf(file, "time_mode : %d\n", game_settings->time_mode);
    fprintf(file, "time_at_start : %f\n", game_settings->time_at_start);
    fprintf(file, "blitz_time : %f\n", game_settings->blitz_time);
    fprintf(file, "white_time_remaining : %f\n", game_settings->white_time_remaining);
    fprintf(file, "black_time_remaining : %f\n", game_settings->black_time_remaining);


    // then we store the log
    fprintf(file, "\nLog :\n");
    for (int i = 0; i < chess_log->actual_size; i++){
        fprintf(file, "Move_value : %d\n", chess_log->moves[i]->move_value);
    }


    // closing the file
    fclose(file);

}


void open_file_and_setup_chess_game(bool* has_opened){
    
    // opening the file
    FILE* file = fopen("game_log.txt", "r");
    // checking if the file was opened
    if (file == NULL){
        printf("Error opening the file\n");
        return;
    }
    // setting the has_opened to true
    else {
        *has_opened = true;
    }

    // creating a log to store the moves of the file before updating the actual log when it will be the time
    Log* log_copy = create_a_copy_of_log(chess_log);

    // looking for the game settings and updating them
    char line[256]; // Buffer to hold each line
    int line_number = 0;

    // we need to pass the formal log before doing anything
    fgets(line, sizeof(line), file); // "Formal Log :"
    while (fgets(line, sizeof(line), file)) {
        if (strcmp(line, "\n") == 0){
            break;
        }
    }

    while (fgets(line, sizeof(line), file)) {
        double number; // To handle both integer and floating-point values
        if (sscanf(line, "%*[^:]: %lf", &number) == 1) {
            
            // the first 13 lines are the game settings
            if (line_number > 0 && line_number < 14){
                switch (line_number){
                    case 1:
                        game_settings->game_mode = (int)number;
                        break;
                    case 2:
                        game_settings->white_player_type = (int)number;
                        break;
                    case 3:
                        game_settings->white_AI_difficulty = (int)number;
                        break;
                    case 4:
                        game_settings->black_player_type = (int)number;
                        break;
                    case 5:
                        game_settings->black_AI_difficulty = (int)number;
                        break;
                    case 6:
                        game_settings->player_that_is_playing = (int)number;
                        break;
                    case 7:
                        game_settings->color_of_player_that_is_playing = (int)number;
                        break;
                    case 8:
                        game_settings->loosing_player = (int)number;
                        break;
                    case 9:
                        game_settings->time_mode = (int)number;
                        break;
                    case 10:
                        game_settings->time_at_start = number;
                        break;
                    case 11:
                        game_settings->blitz_time = number;
                        break;
                    case 12:
                        game_settings->white_time_remaining = number;
                        break;
                    case 13:
                        game_settings->black_time_remaining = number;
                        break;
                }
            }
            // the rest of the lines are the log
            else if (line_number > 15){
                log_copy->moves[log_copy->actual_size]->move_value = (move)number;
                log_copy->actual_size++;
            }

        }
        line_number++;

    }

    // this need to be the white starting to play, since we recreate the game from the start
    game_settings->player_that_is_playing = White_Player;
    game_settings->color_of_player_that_is_playing = WHITE;

    // we then make the moves of the log after 
    for (int i = 0; i < log_copy->actual_size; i++){
        
        // getting if a capture will happen, to update the captured pieces and the score
        int taken_piece = NOTHING;
        if (get_flag(log_copy->moves[i]->move_value) == En_Passant_Flag){
            taken_piece = get_type_of_piece(bitboards, (game_settings->color_of_player_that_is_playing == WHITE) ? get_to_square(log_copy->moves[i]->move_value) - 8 : get_to_square(log_copy->moves[i]->move_value) + 8);
        }
        else if (will_capture(game_settings->color_of_player_that_is_playing, bitboards, get_to_square(log_copy->moves[i]->move_value))){
            taken_piece = get_type_of_piece(bitboards, get_to_square(log_copy->moves[i]->move_value));
        }
        update_captured_piece_and_score(taken_piece);

        // making the move
        make_move_AI(log_copy->moves[i]->move_value);

        // adding the biboard to the log to be able to detect draws after
        add_bitboards_to_log(bitboards);

    }

    // freeing the log copy
    // looking for malloc errors
    if (log_copy != NULL){
        // freeing the memory
        for (int i = 0; i < log_copy->max_size; i++){
            // looking for malloc errors
            if (log_copy->moves[i] != NULL){
                free(log_copy->moves[i]);
            }
        }
        free(log_copy->moves);
        free(log_copy);
    }

    // closing the file
    fclose(file);

    // updating the opening book
    update_opening_book();

}
