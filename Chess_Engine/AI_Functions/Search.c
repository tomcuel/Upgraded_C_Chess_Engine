#include "Search.h"


// setting the variables for the iterative deepening
move best_move;
int best_score;
move best_move_this_iteration;
int best_score_this_iteration;
// choosing the think time of the AI (will be dealed in another way later), but currently it's only for testing
int search_time_in_ms = 5000; // 5 seconds, for the tests
int think_time_limit; // for the depth 1 search so it's not stopped
int start_time;
bool is_search_canceled;


void run_best_AI_level(move* selected_move, int* selected_score, bool* is_move_taken_from_book, int* depth_reached){

    // looking in the book opening if the move is in the book
    move move_from_book = get_move_from_book();
    if (!is_move_null(move_from_book)){
        *selected_move = move_from_book;
        *is_move_taken_from_book = true;
    }
    else {
        // running the iterative
        run_iterative_deepening(selected_move, selected_score, depth_reached);
    }

    // getting if a capture will happen, to update the captured pieces and the score
    int taken_piece = NOTHING;
    if (get_flag(*selected_move) == En_Passant_Flag){
        taken_piece = get_type_of_piece(bitboards, (game_settings->color_of_player_that_is_playing == WHITE) ? get_to_square(*selected_move) - 8 : get_to_square(*selected_move) + 8);
    }
    else if (will_capture(game_settings->color_of_player_that_is_playing, bitboards, get_to_square(*selected_move))){
        taken_piece = get_type_of_piece(bitboards, get_to_square(*selected_move));
    }
    update_captured_piece_and_score(taken_piece);

    // making the move
    make_move_AI(*selected_move);
    // updating the opening book after the move has been made
    update_opening_book();

}


int choose_think_time(int color_playing){

    int ms = 1000; // 1 second

    int time_remaining = (color_playing == WHITE) ? game_settings->white_time_remaining : game_settings->black_time_remaining;
    int time_at_start = game_settings->time_at_start;
    // more than 30sec for 10min, 1min30 for 30min, 3min for 60min;
    if (time_remaining < (time_at_start/20)){ 
        return (time_remaining/10)*ms;
    }
    
    return (time_at_start/30)*ms;
}


void run_iterative_deepening(move* selected_move, int* selected_score, int* depth_reached){

    printf("iterative deepening with transposition tables and search extensions\n");
    // setting the variables for the iterative deepening
    is_search_canceled = false;
    best_move = 0;
    best_score = 0;
    best_move_this_iteration = 0;
    best_score_this_iteration = INT_MIN;

    start_time = (int)SDL_GetTicks(); // the time when the search started, initialized in the run_iterative_deepening function
    think_time_limit = /*search_time_in_ms;*/ choose_think_time(game_settings->color_of_player_that_is_playing); 
    
    // running the iterative deepening (depth one is already done in the make play function)
    for (int search_depth = 1; search_depth < MAX_DEPTH_ITERATIVE_DEEPENING; search_depth++){

        // making the search for the best move for this AI level
        int score = Search(search_depth, 0, NEGATIVE_INFINITY, POSITIVE_INFINITY, 0);
        printf("score : %d for move from %d to %d for depth %d\n", score, get_from_square(best_move_this_iteration), get_to_square(best_move_this_iteration), search_depth);
        *depth_reached = search_depth;

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
        *selected_score = best_score;
        printf("best score : %d for move from %d to %d\n", best_score, get_from_square(best_move), get_to_square(best_move));
        printf("\n");
    }
    // back_up in case we didn't find any move, generally no used, time needs to be less than 100ms to reach this point, and it's only a one or two positions after the opening moves
    else {
        int backup_search_time = (int)SDL_GetTicks();
        is_search_canceled = false;
        think_time_limit = INT_MAX; // for the depth 1 search so it's not stopped
        Search(1, 0, NEGATIVE_INFINITY, POSITIVE_INFINITY, 0);
        int time_passed_during_backup_search = (int)SDL_GetTicks() - backup_search_time;
        printf("time passed during backup search : %d\n", time_passed_during_backup_search);
        *selected_move = best_move_this_iteration;
        *selected_score = best_score_this_iteration;
        printf("best score : %d for move from %d to %d, depth 1 recup\n", best_score_this_iteration, get_from_square(best_move_this_iteration), get_to_square(best_move_this_iteration));

    }

    // resetting the variables for the iterative deepening
    is_search_canceled = false;
    
}


int Search(int ply_remaining, int ply_from_root, int alpha, int beta, int nb_extensions){

    // if the search is canceled, we need to stop the search
    if (is_search_canceled){
        return 0;
    }

    // before making the search, we need to check if the time left to think is not over
    if ((int)SDL_GetTicks() - start_time > think_time_limit){
        is_search_canceled = true;
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
                best_move_this_iteration = transposition_tables->entries[index_in_TT].move;
                best_score_this_iteration = transposition_tables->entries[index_in_TT].value;
            }
            return TT_value;
        }
    }

    if (ply_remaining == 0){
        // making the search for the captures happening afterwards (the quiescence search)
        return Quiescience_Search(alpha, beta);
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

        int valid_move_from = get_from_square(valid_moves[i]);
        int valid_move_to = get_to_square(valid_moves[i]);
        int flag = get_flag(valid_moves[i]);

        // getting if a capture will happen, used later 
        bool is_capture_happening = will_capture(game_settings->color_of_player_that_is_playing, bitboards, valid_move_to);
        if (flag == En_Passant_Flag){
            is_capture_happening = true;
        }

        // making the move first
        make_move_AI(valid_moves[i]);

        // Extend the depth of the search in certain interesting cases
        int extension = 0;
        if (extension < MAX_NUMBER_OF_EXTENSIONS){

            // getting some information to know if we need to extend the search
            int targeted_rank = get_rank(valid_move_to);
            int moved_piece_type = get_type_of_piece(bitboards, valid_move_from);

            // a check is interesting to look further
            if (is_check(game_settings->color_of_player_that_is_playing, bitboards, chess_log) == CHECK){
                extension = 1;
            }
            // it's also interesting to look further if a promotion is near
            else if ((moved_piece_type == PAWN_WHITE || moved_piece_type == PAWN_BLACK) && (targeted_rank == 1 || targeted_rank == 6)){
                extension = 1;
            }

        }

        bool need_full_search = true;
        int eval = 0;

        // Reduce the depth of the search for moves later in the move list as these are less likely to be good (assuming our move ordering isn't terrible)
        if (extension == 0 && ply_remaining >= 3 && i >= 3 && !is_capture_happening){
            // here is our reduced depth
            int reduced_depth = 1;
            // calculating the evaluation of the position at the reduced depth
            eval = -Search(ply_remaining-1-reduced_depth, ply_from_root+1, -alpha - 1, -alpha, nb_extensions);
            // If the evaluation is better than expected, we'd better to a full-depth search to get a more accurate evaluation
			need_full_search = (eval > alpha);
        }
    
        // Perform a full-depth search
        if (need_full_search){
            // calculating the evaluation of the position at the full depth (extended by the interesting cases)
            eval = -Search(ply_remaining-1+extension, ply_from_root+1, -beta, -alpha, nb_extensions+extension);
        }

        // undoing the move to make the search and not modify the game state
        undo_last_move_AI();

        // if the search is canceled, during the search at depth-1, we need to stop the search
        if (is_search_canceled){
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
                best_move_this_iteration = valid_moves[i];
                best_score_this_iteration = eval;
            }
        }

    }

    // storing the evaluation in the transposition tables
    store_evaluation_in_TT(index_in_TT, hashed_zobrist_key, ply_remaining, alpha, cut_flag, best_move_in_this_position);

    // returning the lower bound of the score if nothing better has been found
    free(valid_moves);
    return alpha;

}


int Quiescience_Search(int alpha, int beta){

    // before making the search, we need to check if the time left to think is not over
    if ((int)SDL_GetTicks() - start_time > think_time_limit){
        is_search_canceled = true;
        return 0;
    }

    // if the search is canceled, we need to stop the search
    if (is_search_canceled){
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
        evaluation = -Quiescience_Search(-beta, -alpha);
        undo_last_move_AI();
        
        // if the search is canceled, during the search at depth-1, we need to stop the search
        if (is_search_canceled){
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
