#include "AI.h"


void make_AI_play(int level_of_AI, move* selected_move_lvl7, int* selected_score_lvl7, bool* is_move_taken_from_book_lvl7, int* depth_reached_lvl7){

    // making different AI play depending on the level
    // for the level 1 AI : random play but considering captures (ordered by the best difference of value between the piece that takes and the piece that is taken)
    if (level_of_AI == LVL1){

        srand((unsigned int)time(NULL));  // Seed rand() with current time for randomness
        make_AI_random_capture_play();

    }
    // level 2 is the alpha_beta pruning method, with a depth we can ajust here
    else if (level_of_AI == LVL2){
        
        int lvl2_depth = 2;
        make_AI_alpha_beta_play(lvl2_depth);

    }
    // level 3 is the alpha_beta pruning method, with a depth we can ajust here
    // when the seach is completed, it also does an alpha_beta pruning on the moves that are making a captures until there are no more if possible, or at a certain depth given here, to limit (quiescence search)
    else if (level_of_AI == LVL3){
        
        int lvl3_depth = 2;
        make_AI_alpha_beta_play_quiescence_search(lvl3_depth);

    }
    // level 4 is the alpha_beta pruning method, with a cleaner evaluation function, ajusted depending on the phase of the game
    else if (level_of_AI == LVL4){
        
        int lvl4_depth = 2;
        make_AI_alpha_beta_play_quiescence_search_eval_up(lvl4_depth);

    }
    // level 5 is the alpha_beta pruning method, with the implementation of the iterative deepening to search deeper and more efficiently, first it will be slower, but then it will be faster with the transposition tables
    else if (level_of_AI == LVL5){
        
        make_AI_alpha_beta_play_iterative_deepening();

    }
    // level 6 is the alpha_beta pruning method, with the implementation of the transposition table to fast things up, to be able to search deeper for the same time still with the iterative deepening
    else if (level_of_AI == LVL6){
        
       make_AI_alpha_beta_play_transposition_tables();

    }
    // level 7 is the alpha_beta pruning method, with the implementation of the transposition table to fast things up, to be able to search deeper for the same time still with the iterative deepening, and the implementation extended search where it's critical
    else if (level_of_AI == LVL7){
        
        // resetting the selected move and the selected score, as well as the boolean to know if the move is taken from the opening book before running the best AI
        *selected_move_lvl7 = 0;
        *selected_score_lvl7 = 0;
        *is_move_taken_from_book_lvl7 = false;
        *depth_reached_lvl7 = 0;
        run_best_AI_level(selected_move_lvl7, selected_score_lvl7, is_move_taken_from_book_lvl7, depth_reached_lvl7);

    }

    // adding the biboard to the log to be able to detect draws after
    add_bitboards_to_log(bitboards);

}


void make_AI_random_capture_play(){

    // getting the selected move
    move selected_move = 0;

    // generate all the possible moves for the AI at this point
    int nb_moves_capture = 0;
    move* valid_moves_capture = generate_all_possible_moves_that_capture(&nb_moves_capture);
    
    int best_taken_piece_value = 0;
    int lowest_value_of_piece_that_takes = 1000000;
    for (int i = 0; i < nb_moves_capture; i++){

        // getting the moves indexes
        int valid_move_from = get_from_square(valid_moves_capture[i]);
        int valid_move_to = get_to_square(valid_moves_capture[i]);
        
        // getting the value of the piece we're moving to make the capture
        int piece_type_that_take = get_type_of_piece(bitboards, valid_move_from);
        int value_of_piece_that_take = get_value_of_piece(piece_type_that_take);
        // getting the value of the piece we're capturing (counting the en passant capture)
        int piece_type_that_is_taken = NOTHING;
        if (is_en_passant_possible(game_settings->color_of_player_that_is_playing, bitboards, valid_move_from, valid_move_to, chess_log)){
            piece_type_that_is_taken = get_type_of_piece(bitboards, (game_settings->color_of_player_that_is_playing == WHITE) ? valid_move_to - 8 : valid_move_to + 8);
        }
        else {
            piece_type_that_is_taken = get_type_of_piece(bitboards, valid_move_to);
        }
        int value_of_piece_that_is_taken = get_value_of_piece(piece_type_that_is_taken);

        // looking if this capture is the best one
        if (value_of_piece_that_take < lowest_value_of_piece_that_takes && value_of_piece_that_is_taken > best_taken_piece_value){
            // updating the best capture found and its euristic value
            lowest_value_of_piece_that_takes = value_of_piece_that_take;
            best_taken_piece_value = value_of_piece_that_is_taken;
            // updating the selected move
            selected_move = valid_moves_capture[i];
        }

    }
    // deallocating the valid moves memory taken 
    free(valid_moves_capture);

    if (is_move_null(selected_move)){

        // generate all the possible moves for the AI at this point, because no capture is possible
        int nb_moves = 0;
        move* valid_moves = generate_all_possible_moves(&nb_moves);
        
        // selecting a random move
        int random_index = random_int(0, nb_moves - 1);
        selected_move = valid_moves[random_index];
        
        // deallocating the valid moves memory taken
        free(valid_moves);

    }

    // getting if a capture will happen, to update the captured pieces and the score
    int taken_piece = NOTHING;
    if (get_flag(selected_move) == En_Passant_Flag){
        taken_piece = get_type_of_piece(bitboards, (game_settings->color_of_player_that_is_playing == WHITE) ? get_to_square(selected_move) - 8 : get_to_square(selected_move) + 8);
    }
    else if (will_capture(game_settings->color_of_player_that_is_playing, bitboards, get_to_square(selected_move))){
        taken_piece = get_type_of_piece(bitboards, get_to_square(selected_move));
    }
    update_captured_piece_and_score(taken_piece);
    
    // making the selected move
    make_move_AI(selected_move);
    printf("random move from %d to %d\n", get_from_square(selected_move), get_to_square(selected_move));

}


int Alpha_Beta_LVL2_Search_Valid_Moves(int depth, int lvl2_depth, int alpha, int beta, move* selected_move){

    // a depth of 0, we need to evaluate the position
    if (depth == 0){
        int turncolor = (game_settings->color_of_player_that_is_playing == WHITE) ? 1 : -1;
        return turncolor * evaluate_position_lvl2_lvl3();
    }
    
    // generating all the possible moves for the AI at this point and ordering them to make the search faster, because we will search the best moves first
    int nb_moves = 0; 
    move* valid_moves = generate_all_possible_moves(&nb_moves);
    // if there are no moves, we need to check if the king is in check, if it is, we return the worst score possible since it's a mate, else we return 0 since it's a draw
    if (nb_moves == 0){
        if (is_check(game_settings->color_of_player_that_is_playing, bitboards, chess_log) == CHECK && get_king_index(bitboards, game_settings->color_of_player_that_is_playing) != -1){
            free(valid_moves);
            return -MAX_IA_SCORE;
        }
        free(valid_moves);
        return 0;
    }

    // ordering the moves to make the search faster
    order_moves(false, valid_moves, nb_moves);
    // searching for the best move by evaluating the position after each move
    for (int i = 0; i < nb_moves; i++){

        // making the move, getting the score of the move by going one move deeper, and undoing the move
        make_move_AI(valid_moves[i]);
        int score = -Alpha_Beta_LVL2_Search_Valid_Moves(depth - 1, lvl2_depth, -beta, -alpha, selected_move);
        undo_last_move_AI();
        
        // pruning the search if the score is better than the beta value
        if (score >= beta){
            free(valid_moves);
            return beta;
        }
        // updating the alpha value if the score is better than the current alpha value
        if (score > alpha){
            alpha = score;

            // if we're at the first depth, we need to update the selected move, it's the best move found yet 
            if (depth == lvl2_depth){
                *selected_move = valid_moves[i];
            }
        }

    }

    // returning the lower bound of the score if nothing better has been found
    free(valid_moves);
    return alpha;

}


void make_AI_alpha_beta_play(int lvl2_depth){

    move selected_move = 0;

    // making the search for the best move for this AI level
    int score = Alpha_Beta_LVL2_Search_Valid_Moves(lvl2_depth, lvl2_depth, -MAX_IA_SCORE, MAX_IA_SCORE, &selected_move);
    printf("lvl2 score : %d for move from %d to %d\n", score, get_from_square(selected_move), get_to_square(selected_move));
    printf("\n");

    if (is_move_null(selected_move)){
        // since a depth of more than 1 is not possible, because there is not enough material, we need to add this part of the code to simulate a move based only on the next move
        // we can here see how useful will be the iterative deepening that will be implemented later 
        printf("no move found at first : ");
        int score = Alpha_Beta_LVL2_Search_Valid_Moves(1, 1, -MAX_IA_SCORE, MAX_IA_SCORE, &selected_move);
        printf("lvl2 score : %d for move from %d to %d\n", score, get_from_square(selected_move), get_to_square(selected_move));
        printf("\n");
    }

    // getting if a capture will happen, to update the captured pieces and the score
    int taken_piece = NOTHING;
    if (get_flag(selected_move) == En_Passant_Flag){
        taken_piece = get_type_of_piece(bitboards, (game_settings->color_of_player_that_is_playing == WHITE) ? get_to_square(selected_move) - 8 : get_to_square(selected_move) + 8);
    }
    else if (will_capture(game_settings->color_of_player_that_is_playing, bitboards, get_to_square(selected_move))){
        taken_piece = get_type_of_piece(bitboards, get_to_square(selected_move));
    }
    update_captured_piece_and_score(taken_piece);

    // making the move
    make_move_AI(selected_move);

}


int Alpha_Beta_LVL3_Search_Capture_Moves(int alpha, int beta){

    // evaluating the position
    int turncolor = (game_settings->color_of_player_that_is_playing == WHITE) ? 1 : -1;
    int evaluation = turncolor * evaluate_position_lvl2_lvl3();
    // pruning the search if the evaluation is better than the beta value
    if (evaluation >= beta){
       return beta;
    }
    // updating the alpha value if the evaluation is better than the current alpha value
    if (evaluation > alpha){
        alpha = evaluation;
    }

    // since we're dealing with captures, we need to check if the king is still on the board, if not, we return the worst score possible since it's a mate
    if (get_king_index(bitboards, game_settings->color_of_player_that_is_playing) == -1){
        return -MAX_IA_SCORE;
    }

    // generating all the possible moves that captures for the AI at this point and ordering them to make the search faster, because we will search the best moves first
    int nb_moves = 0; 
    move* valid_moves = generate_all_possible_moves_that_capture(&nb_moves);
    // if there is no capture left, we return the evaluation
    if (nb_moves == 0){
        free(valid_moves);
        return evaluation;
    }

    // ordering the moves to make the search faster (we only order the captures)
    order_moves(true, valid_moves, nb_moves);
    // searching for the best move by evaluating the position after each move
    for (int i = 0; i < nb_moves; i++){

        // making the move, getting the score of the position after the move (updating the evaluation), and undoing the move
        make_move_AI(valid_moves[i]);
        evaluation = -Alpha_Beta_LVL3_Search_Capture_Moves(-beta, -alpha);
        undo_last_move_AI();
        
        // pruning the search if the evaluation is better than the beta value
        if (evaluation >= beta){
            free(valid_moves);
            return beta;
        }
        // updating the alpha value if the evaluation is better than the current alpha value
        if (evaluation > alpha){
            alpha = evaluation;
        }

    }

    // returning the lower bound of the score if nothing better has been found
    free(valid_moves);
    return alpha;

}


int Alpha_Beta_LVL3_Search_Moves(int depth, int lvl3_depth, int alpha, int beta, move* selected_move){

    if (depth == 0){
        // making the search for the captures happening afterwards
        return Alpha_Beta_LVL3_Search_Capture_Moves(alpha, beta);
    }
    
    // generating all the possible moves for the AI at this point and ordering them to make the search faster, because we will search the best moves first
    int nb_moves = 0; 
    move* valid_moves = generate_all_possible_moves(&nb_moves);
    // if there are no moves, we need to check if the king is in check, if it is, we return the worst score possible since it's a mate, else we return 0 since it's a draw
    if (nb_moves == 0){
        if (is_check(game_settings->color_of_player_that_is_playing, bitboards, chess_log) == CHECK && get_king_index(bitboards, game_settings->color_of_player_that_is_playing) != -1){
            free(valid_moves);
            return -MAX_IA_SCORE;
        }
        free(valid_moves);
        return 0;
    }

    // ordering the moves to make the search faster
    order_moves(false, valid_moves, nb_moves);
    // searching for the best move by evaluating the position after each move
    for (int i = 0; i < nb_moves; i++){

        // making the move, getting the score of the move by going one move deeper, and undoing the move
        make_move_AI(valid_moves[i]);
        int score = -Alpha_Beta_LVL3_Search_Moves(depth - 1, lvl3_depth, -beta, -alpha, selected_move);
        undo_last_move_AI();
        
        // pruning the search if the score is better than the beta value
        if (score >= beta){
            free(valid_moves);
            return beta;
        }
        // updating the alpha value if the score is better than the current alpha value
        if (score > alpha){
            alpha = score;

            // if we're at the first depth, we need to update the selected move, it's the best move found yet
            if (depth == lvl3_depth){
                *selected_move = valid_moves[i];
            }
        }

    }

    // returning the lower bound of the score if nothing better has been found
    free(valid_moves);
    return alpha;

}


void make_AI_alpha_beta_play_quiescence_search(int lvl3_depth){
    
    move selected_move = 0;

    // making the search for the best move for this AI level
    int score = Alpha_Beta_LVL3_Search_Moves(lvl3_depth, lvl3_depth, -MAX_IA_SCORE, MAX_IA_SCORE, &selected_move);
    printf("lvl3 score : %d for move from %d to %d\n", score, get_from_square(selected_move), get_to_square(selected_move));
    printf("\n");

    if (is_move_null(selected_move)){
        // since a depth of more than 1 is not possible, because there is not enough material, we need to add this part of the code to simulate a move based only on the next move
        // we can here see how useful will be the iterative deepening that will be implemented later 
        printf("no move found at first : ");
        score = Alpha_Beta_LVL3_Search_Moves(1, 1, -MAX_IA_SCORE, MAX_IA_SCORE, &selected_move);
        printf("lvl3 score : %d for move from %d to %d\n", score, get_from_square(selected_move), get_to_square(selected_move));
        printf("\n");
    }

    // getting if a capture will happen, to update the captured pieces and the score
    int taken_piece = NOTHING;
    if (get_flag(selected_move) == En_Passant_Flag){
        taken_piece = get_type_of_piece(bitboards, (game_settings->color_of_player_that_is_playing == WHITE) ? get_to_square(selected_move) - 8 : get_to_square(selected_move) + 8);
    }
    else if (will_capture(game_settings->color_of_player_that_is_playing, bitboards, get_to_square(selected_move))){
        taken_piece = get_type_of_piece(bitboards, get_to_square(selected_move));
    }
    update_captured_piece_and_score(taken_piece);

    // making the move
    make_move_AI(selected_move);
}


int Alpha_Beta_LVL4_Search_Capture_Moves_eval_up(int alpha, int beta){

    // evaluating the position
    int evaluation = evaluate();
    // pruning the search if the evaluation is better than the beta value
    if (evaluation >= beta){
       return beta;
    }
    // updating the alpha value if the evaluation is better than the current alpha value
    if (evaluation > alpha){
        alpha = evaluation;
    }

    // since we're dealing with captures, we need to check if the king is still on the board, if not, we return the worst score possible since it's a mate
    if (get_king_index(bitboards, game_settings->color_of_player_that_is_playing) == -1){
        return -MAX_IA_SCORE;
    }

    // generating all the possible moves that captures for the AI at this point and ordering them to make the search faster, because we will search the best moves first
    int nb_moves = 0; 
    move* valid_moves = generate_all_possible_moves_that_capture(&nb_moves);
    // if there is no capture left, we return the evaluation
    if (nb_moves == 0){
        free(valid_moves);
        return evaluation;
    }

    // ordering the moves to make the search faster (we only order the captures)
    order_moves(true, valid_moves, nb_moves);
    // searching for the best move by evaluating the position after each move
    for (int i = 0; i < nb_moves; i++){

        // making the move, getting the score of the position after the move (updating the evaluation), and undoing the move
        make_move_AI(valid_moves[i]);
        evaluation = -Alpha_Beta_LVL4_Search_Capture_Moves_eval_up(-beta, -alpha);
        undo_last_move_AI();
        
        // pruning the search if the evaluation is better than the beta value
        if (evaluation >= beta){
            free(valid_moves);
            return beta;
        }
        // updating the alpha value if the evaluation is better than the current alpha value
        if (evaluation > alpha){
            alpha = evaluation;
        }

    }

    // returning the lower bound of the score if nothing better has been found
    free(valid_moves);
    return alpha;

}


int Alpha_Beta_LVL4_Search_Moves_eval_up(int depth, int lvl4_depth, int alpha, int beta, move* selected_move){

    if (depth == 0){
        // making the search for the captures happening afterwards
        return Alpha_Beta_LVL4_Search_Capture_Moves_eval_up(alpha, beta);
    }

    // generating all the possible moves for the AI at this point and ordering them to make the search faster, because we will search the best moves first
    int nb_moves = 0; 
    move* valid_moves = generate_all_possible_moves(&nb_moves);
    // if there are no moves, we need to check if the king is in check, if it is, we return the worst score possible since it's a mate, else we return 0 since it's a draw
    if (nb_moves == 0){
        if (is_check(game_settings->color_of_player_that_is_playing, bitboards, chess_log) == CHECK && get_king_index(bitboards, game_settings->color_of_player_that_is_playing) != -1){
            free(valid_moves);
            return -MAX_IA_SCORE;
        }
        free(valid_moves);
        return 0;
    }

    // ordering the moves to make the search faster
    order_moves(false, valid_moves, nb_moves);
    // searching for the best move by evaluating the position after each move
    for (int i = 0; i < nb_moves; i++){

        // making the move, getting the score of the move by going one move deeper, and undoing the move
        make_move_AI(valid_moves[i]);
        int score = -Alpha_Beta_LVL4_Search_Moves_eval_up(depth - 1, lvl4_depth, -beta, -alpha, selected_move);
        undo_last_move_AI();
        
        // pruning the search if the score is better than the beta value
        if (score >= beta){
            return beta;
        }
        // updating the alpha value if the score is better than the current alpha value
        if (score > alpha){
            alpha = score;

            // if we're at the first depth, we need to update the selected move, it's the best move found yet
            if (depth == lvl4_depth){
                *selected_move = valid_moves[i];
            }
        }

    }

    free(valid_moves);
    return alpha;

}


void make_AI_alpha_beta_play_quiescence_search_eval_up(int lvl4_depth){
    
    move selected_move = 0;

    // making the search for the best move for this AI level
    int score = Alpha_Beta_LVL4_Search_Moves_eval_up(lvl4_depth, lvl4_depth, -MAX_IA_SCORE, MAX_IA_SCORE, &selected_move);
    printf("lvl4 score : %d for move from %d to %d\n", score, get_from_square(selected_move), get_to_square(selected_move));
    printf("\n");

    if (is_move_null(selected_move)){
        // since a depth of more than 1 is not possible, because there is not enough material, we need to add this part of the code to simulate a move based only on the next move
        // we can here see how useful will be the iterative deepening that will be implemented later 
        printf("no move found at first : ");
        score = Alpha_Beta_LVL4_Search_Moves_eval_up(1, 1, -MAX_IA_SCORE, MAX_IA_SCORE, &selected_move);
        printf("lvl4 score : %d for move from %d to %d for depth one\n", score, get_from_square(selected_move), get_to_square(selected_move));
        printf("\n");
    }

    // getting if a capture will happen, to update the captured pieces and the score
    int taken_piece = NOTHING;
    if (get_flag(selected_move) == En_Passant_Flag){
        taken_piece = get_type_of_piece(bitboards, (game_settings->color_of_player_that_is_playing == WHITE) ? get_to_square(selected_move) - 8 : get_to_square(selected_move) + 8);
    }
    else if (will_capture(game_settings->color_of_player_that_is_playing, bitboards, get_to_square(selected_move))){
        taken_piece = get_type_of_piece(bitboards, get_to_square(selected_move));
    }
    update_captured_piece_and_score(taken_piece);

    // making the move
    make_move_AI(selected_move);

}


void test_iterative_deepening(move* selected_move){

    printf("iterative deepening test\n");
    // setting the variables for the iterative deepening
    move best_move = 0;
    int best_score = 0;
    move best_move_this_iteration = 0;
    int best_score_this_iteration = INT_MIN;

    // choosing the think time of the AI (will be dealed in another way later), but currently it's only for testing
    int think_time_limit = INT_MAX; // for the depth 1 search so it's not stopped
    int start_time = (int)SDL_GetTicks();
    bool is_search_canceled = false;

    // running the depth 1 search without time restriction
    int depth_1_score = Alpha_Beta_LVL5_Search_Moves_iterative_deepening(1, 0, NEGATIVE_INFINITY, POSITIVE_INFINITY, &best_move, &best_score, &is_search_canceled, think_time_limit, start_time);
    printf("score : %d for move from %d to %d for depth 1\n", depth_1_score, get_from_square(best_move), get_to_square(best_move));
    int time_passed = (int)SDL_GetTicks() - start_time;

    // putting back the time limit for the iterative deepening
    think_time_limit = 5000; // for the depth 2 search and more (3 seconds)

    // if the depth 1 already took too much time, we need to stop the search since depth 2 will take more time
    if (time_passed > think_time_limit){
        is_search_canceled = true;
    }
    // running the iterative deepening (depth one is already done in the make play function)
    for (int search_depth = 2; search_depth < MAX_DEPTH_ITERATIVE_DEEPENING; search_depth++){

        // making the search for the best move for this AI level
        int score = Alpha_Beta_LVL5_Search_Moves_iterative_deepening(search_depth, 0, NEGATIVE_INFINITY, POSITIVE_INFINITY, &best_move_this_iteration, &best_score_this_iteration, &is_search_canceled, think_time_limit, start_time);
        printf("score : %d for move from %d to %d for depth %d\n", score, get_from_square(best_move_this_iteration), get_to_square(best_move_this_iteration), search_depth);

        // if the search has been canceled, we need to stop the iterative deepening search
        if (is_search_canceled){ 
            break; // stop the search when the move score is 0 or best_move_this_iteration is 0 but without having to verify it here
        }
        // otherwise, we need to update the best move found since it's sure that we have found a move
        else {
            best_move = best_move_this_iteration;
            best_score = best_score_this_iteration;
            best_move_this_iteration = 0;
            best_score_this_iteration = INT_MIN;

            if (abs(best_score) > IMMEDIATE_MATE_SCORE - 1000){
                break; // stop the search when the move score make a mate since there is not need to look further
            }
        }

    }

    // udpating the selected move if it's not null
    if (!is_move_null(best_move)){
        *selected_move = best_move;
        printf("best score : %d for move from %d to %d\n", best_score, get_from_square(best_move), get_to_square(best_move));
        printf("\n");
    }
}


int Alpha_Beta_LVL5_Search_Capture_Moves_iterative_deepening(int alpha, int beta, bool* is_search_canceled, int think_time_limit, int start_time){

    // before making the search, we need to check if the time left to think is not over
    if ((int)SDL_GetTicks() - start_time > think_time_limit){
        *is_search_canceled = true;
        return 0;
    }

    // if the search is canceled, we need to stop the search
    if (*is_search_canceled){
        return 0;
    }

    // evaluating the position
    int evaluation = evaluate();
    // pruning the search if the evaluation is better than the beta value
    if (evaluation >= beta){
       return beta;
    }
    // updating the alpha value if the evaluation is better than the current alpha value
    if (evaluation > alpha){
        alpha = evaluation;
    }

    // since we're dealing with captures, we need to check if the king is still on the board, if not, we return the worst score possible since it's a mate
    if (get_king_index(bitboards, game_settings->color_of_player_that_is_playing) == -1){
        return -MAX_IA_SCORE;
    }

    // generating all the possible moves that captures for the AI at this point and ordering them to make the search faster, because we will search the best moves first
    int nb_moves = 0; 
    move* valid_moves = generate_all_possible_moves_that_capture(&nb_moves);
    // if there is no capture left, we return the evaluation
    if (nb_moves == 0){
        free(valid_moves);
        return evaluation;
    }

    // ordering the moves to make the search faster (we only order the captures)
    order_moves(true, valid_moves, nb_moves);
    // searching for the best move by evaluating the position after each move
    for (int i = 0; i < nb_moves; i++){

        // making the move, getting the score of the position after the move (updating the evaluation), and undoing the move
        make_move_AI(valid_moves[i]);
        evaluation = -Alpha_Beta_LVL5_Search_Capture_Moves_iterative_deepening(-beta, -alpha, is_search_canceled, think_time_limit, start_time);
        undo_last_move_AI();
        
        // if the search is canceled, during the search at depth-1, we need to stop the search
        if (*is_search_canceled){
            free(valid_moves);
            return 0;
        }
        
        // pruning the search if the evaluation is better than the beta value
        if (evaluation >= beta){
            free(valid_moves);
            return beta;
        }
        // updating the alpha value if the evaluation is better than the current alpha value
        if (evaluation > alpha){
            alpha = evaluation;
        }

    }

    // returning the lower bound of the score if nothing better has been found
    free(valid_moves);
    return alpha;

}


int Alpha_Beta_LVL5_Search_Moves_iterative_deepening(int ply_remaining, int ply_from_root, int alpha, int beta, move* best_move_this_iteration, int* best_score_this_iteration, bool* is_search_canceled, int think_time_limit, int start_time){

    // before making the search, we need to check if the time left to think is not over
    if ((int)SDL_GetTicks() - start_time > think_time_limit){
        *is_search_canceled = true;
        return 0;
    }

    // if the search is canceled, we need to stop the search
    if (*is_search_canceled){
        return 0;
    }

    // making some cut off to continue the alpha beta pruning 
    if (ply_from_root > 0){
        alpha = max(alpha, -IMMEDIATE_MATE_SCORE + ply_from_root);
        beta = min(beta, IMMEDIATE_MATE_SCORE - ply_from_root);
        // cut off if necessary
        if (alpha >= beta){
            return alpha;
        }
    }

    if (ply_remaining == 0){
        // making the search for the captures happening afterwards (the quiescence search is the same as the one for the level 4 AI)
        return Alpha_Beta_LVL5_Search_Capture_Moves_iterative_deepening(alpha, beta, is_search_canceled, think_time_limit, start_time);
    }

    // generating all the possible moves for the AI at this point and ordering them to make the search faster, because we will search the best moves first
    int nb_moves = 0; 
    move* valid_moves = generate_all_possible_moves(&nb_moves);
    // if there are no moves, we need to check if the king is in check, if it is, we return the worst score possible since it's a mate, else we return 0 since it's a draw
    if (nb_moves == 0){
        if (is_check(game_settings->color_of_player_that_is_playing, bitboards, chess_log) == CHECK && get_king_index(bitboards, game_settings->color_of_player_that_is_playing) != -1){
            free(valid_moves);
            return -MAX_IA_SCORE;
        }
        free(valid_moves);
        return 0;
    }

    // ordering the moves to make the search faster
    order_moves(false, valid_moves, nb_moves);
    // searching for the best move by evaluating the position after each move
    for (int i = 0; i < nb_moves; i++){

        // making the move first
        make_move_AI(valid_moves[i]);
    
        int eval = -Alpha_Beta_LVL5_Search_Moves_iterative_deepening(ply_remaining-1, ply_from_root+1, -beta, -alpha, best_move_this_iteration, best_score_this_iteration, is_search_canceled, think_time_limit, start_time);

        // undoing the move to make the search and not modify the game state
        undo_last_move_AI();
        
        // if the search is canceled, during the search at depth-1, we need to stop the search
        if (*is_search_canceled){
            free(valid_moves);
            return 0;
        }
        
        // pruning the search if the score is better than the beta value
        if (eval >= beta){
            return beta;
        }
        // updating the alpha value if the score is better than the current alpha value
        if (eval > alpha){
            alpha = eval;
            
            // if we're at the first depth (the root here), we need to update the selected move, it's the best move found yet
            if (ply_from_root == 0){
                *best_move_this_iteration = valid_moves[i];
                *best_score_this_iteration = eval;
            }
        }

    }

    // returning the lower bound of the score if nothing better has been found
    free(valid_moves);
    return alpha;

}


void make_AI_alpha_beta_play_iterative_deepening(){

    move selected_move = 0;

    // testing to play with the iterative deepening
    test_iterative_deepening(&selected_move);
    
    // getting if a capture will happen, to update the captured pieces and the score
    int taken_piece = NOTHING;
    if (get_flag(selected_move) == En_Passant_Flag){
        taken_piece = get_type_of_piece(bitboards, (game_settings->color_of_player_that_is_playing == WHITE) ? get_to_square(selected_move) - 8 : get_to_square(selected_move) + 8);
    }
    else if (will_capture(game_settings->color_of_player_that_is_playing, bitboards, get_to_square(selected_move))){
        taken_piece = get_type_of_piece(bitboards, get_to_square(selected_move));
    }
    update_captured_piece_and_score(taken_piece);

    // making the move
    make_move_AI(selected_move);

}


void test_iterative_deepening_transposition_tables(move* selected_move){

    printf("iterative deepening with transposition tables\n");
    // setting the variables for the iterative deepening
    move best_move = 0;
    int best_score = 0;
    move best_move_this_iteration = 0;
    int best_score_this_iteration = INT_MIN;

    // choosing the think time of the AI (will be dealed in another way later), but currently it's only for testing
    int think_time_limit = INT_MAX; // for the depth 1 search so it's not stopped
    int start_time = (int)SDL_GetTicks();
    bool is_search_canceled = false;

    // running the depth 1 search without time restriction
    int depth_1_score = Alpha_Beta_LVL6_Search_Moves_transposition_tables(1, 0, NEGATIVE_INFINITY, POSITIVE_INFINITY, &best_move, &best_score, &is_search_canceled, think_time_limit, start_time);
    printf("score : %d for move from %d to %d for depth 1\n", depth_1_score, get_from_square(best_move), get_to_square(best_move));
    int time_passed = (int)SDL_GetTicks() - start_time;

    // putting back the time limit for the iterative deepening
    think_time_limit = 5000; // for the depth 2 search and more (3 seconds)

    // if the depth 1 already took too much time, we need to stop the search since depth 2 will take more time
    if (time_passed > think_time_limit){
        is_search_canceled = true;
    }

    // running the iterative deepening (depth one is already done in the make play function)
    for (int search_depth = 2; search_depth < MAX_DEPTH_ITERATIVE_DEEPENING; search_depth++){

        // making the search for the best move for this AI level
        int score = Alpha_Beta_LVL6_Search_Moves_transposition_tables(search_depth, 0, NEGATIVE_INFINITY, POSITIVE_INFINITY, &best_move_this_iteration, &best_score_this_iteration, &is_search_canceled, think_time_limit, start_time);
        printf("score : %d for move from %d to %d for depth %d\n", score, get_from_square(best_move_this_iteration), get_to_square(best_move_this_iteration), search_depth);

        // if the search has been canceled, we need to stop the iterative deepening search
        if (is_search_canceled){ 
            break; // stop the search when the move score is 0 or best_move_this_iteration is 0 but without having to verify it here
        }
        // otherwise, we need to update the best move found since it's sure that we have found a move
        else {
            best_move = best_move_this_iteration;
            best_score = best_score_this_iteration;
            best_move_this_iteration = 0;
            best_score_this_iteration = INT_MIN;

            if (abs(best_score) > IMMEDIATE_MATE_SCORE - 1000){
                break; // stop the search when the move score make a mate since there is not need to look further
            }
        }

    }

    // udpating the selected move if it's not null
    if (!is_move_null(best_move)){
        *selected_move = best_move;
        printf("best score : %d for move from %d to %d\n", best_score, get_from_square(best_move), get_to_square(best_move));
        printf("\n");
    }
}


int Alpha_Beta_LVL6_Search_Moves_transposition_tables(int ply_remaining, int ply_from_root, int alpha, int beta, move* best_move_this_iteration, int* best_score_this_iteration, bool* is_search_canceled, int think_time_limit, int start_time){

    // before making the search, we need to check if the time left to think is not over
    if ((int)SDL_GetTicks() - start_time > think_time_limit){
        *is_search_canceled = true;
        return 0;
    }

    // if the search is canceled, we need to stop the search
    if (*is_search_canceled){
        return 0;
    }

    // making some cut off to continue the alpha beta pruning 
    if (ply_from_root > 0){
        alpha = max(alpha, -IMMEDIATE_MATE_SCORE + ply_from_root);
        beta = min(beta, IMMEDIATE_MATE_SCORE - ply_from_root);
        // cut off if necessary
        if (alpha >= beta){
            return alpha;
        }
    }

    // looking if we have already evaluated this position in the transposition tables
    bit_board hashed_zobrist_key = 0;
    int index_in_TT = 0;
    if (chess_log->actual_size > 0){
        hashed_zobrist_key = get_zobrist_key();
        index_in_TT = get_index_zobrist_in_TT(hashed_zobrist_key);
        int TT_value = lookup_for_evaluation_in_TT(index_in_TT, hashed_zobrist_key, ply_remaining, ply_from_root, alpha, beta);
        if (TT_value != FAILED_LOOKUP){
            if (ply_from_root == 0){
                *best_move_this_iteration = transposition_tables->entries[index_in_TT].move;
                *best_score_this_iteration = transposition_tables->entries[index_in_TT].value;
            }
            return TT_value;
        }
    }

    if (ply_remaining == 0){
        // making the search for the captures happening afterwards (the quiescence search is the same as the one for the level 4 AI)
        return Alpha_Beta_LVL5_Search_Capture_Moves_iterative_deepening(alpha, beta, is_search_canceled, think_time_limit, start_time);
    }

    // generating all the possible moves for the AI at this point and ordering them to make the search faster, because we will search the best moves first
    int nb_moves = 0; 
    move* valid_moves = generate_all_possible_moves(&nb_moves);
    // if there are no moves, we need to check if the king is in check, if it is, we return the worst score possible since it's a mate, else we return 0 since it's a draw
    if (nb_moves == 0){
        if (is_check(game_settings->color_of_player_that_is_playing, bitboards, chess_log) == CHECK && get_king_index(bitboards, game_settings->color_of_player_that_is_playing) != -1){
            free(valid_moves);
            return -MAX_IA_SCORE;
        }
        free(valid_moves);
        return 0;
    }

    // adding some variables for the transposition tables
    int cut_flag = ALPHA_CUT;
    move best_move_in_this_position = 0;

    // ordering the moves to make the search faster
    order_moves(false, valid_moves, nb_moves);
    // searching for the best move by evaluating the position after each move
    for (int i = 0; i < nb_moves; i++){

        // making the move first
        make_move_AI(valid_moves[i]);
    
        int eval = -Alpha_Beta_LVL6_Search_Moves_transposition_tables(ply_remaining-1, ply_from_root+1, -beta, -alpha, best_move_this_iteration, best_score_this_iteration, is_search_canceled, think_time_limit, start_time);

        // undoing the move to make the search and not modify the game state
        undo_last_move_AI();
        
        // if the search is canceled, during the search at depth-1, we need to stop the search
        if (*is_search_canceled){
            free(valid_moves);
            return 0;
        }
        
        // pruning the search if the score is better than the beta value
        if (eval >= beta){
            store_evaluation_in_TT(index_in_TT, hashed_zobrist_key, ply_remaining, beta, BETA_CUT, valid_moves[i]);
            return beta;
        }
        // updating the alpha value if the score is better than the current alpha value
        if (eval > alpha){
            alpha = eval;

            // udpating the transposition tables variables
            cut_flag = EXACT;
            best_move_in_this_position = valid_moves[i];
            
            // if we're at the first depth (the root here), we need to update the selected move, it's the best move found yet
            if (ply_from_root == 0){
                *best_move_this_iteration = valid_moves[i];
                *best_score_this_iteration = eval;
            }
        }

    }

    // storing the evaluation in the transposition tables
    store_evaluation_in_TT(index_in_TT, hashed_zobrist_key, ply_remaining, alpha, cut_flag, best_move_in_this_position);

    // returning the lower bound of the score if nothing better has been found
    free(valid_moves);
    return alpha;

}


void make_AI_alpha_beta_play_transposition_tables(){

    move selected_move = 0;

    // testing to play with the iterative deepening
    test_iterative_deepening_transposition_tables(&selected_move);
    
    // getting if a capture will happen, to update the captured pieces and the score
    int taken_piece = NOTHING;
    if (get_flag(selected_move) == En_Passant_Flag){
        taken_piece = get_type_of_piece(bitboards, (game_settings->color_of_player_that_is_playing == WHITE) ? get_to_square(selected_move) - 8 : get_to_square(selected_move) + 8);
    }
    else if (will_capture(game_settings->color_of_player_that_is_playing, bitboards, get_to_square(selected_move))){
        taken_piece = get_type_of_piece(bitboards, get_to_square(selected_move));
    }
    update_captured_piece_and_score(taken_piece);

    // making the move
    make_move_AI(selected_move);

}
