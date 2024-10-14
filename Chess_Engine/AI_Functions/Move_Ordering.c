#include "Move_Ordering.h"


int hash_move_bias = 1000000;
int winning_piece_bias = 8000;
int losing_piece_bias = 2000;
int promoted_piece_bias = 6000;
int castling_bias = 10000;


void order_moves(bool is_captures_only, move* valid_moves, int nb_moves){

    // creating an array to store the scores of the moves
    int* scores = (int*)malloc(nb_moves*sizeof(int));
    // looking for malloc errors
    if(scores == NULL){
        printf("Error in order_moves : malloc error\n");
        exit(1);
    }

    // sorting the moves by their value, depending on some parameters
    for (int i = 0; i < nb_moves; i++){

        // we first initialize the value of the move to 0
        scores[i] = 0;

        // getting the differents informations about the move
        int from = get_from_square(valid_moves[i]);
        int to = get_to_square(valid_moves[i]);
        int flag = get_flag(valid_moves[i]);

        // looking if the move is a capture
        bool is_capture_happening = will_capture(game_settings->color_of_player_that_is_playing, bitboards, to);
        if (flag == En_Passant_Flag){
            is_capture_happening = true;
        }

        // capturing a piece is a good move, but it's better to capture a piece that is worth more than the piece that is moving
        if (is_capture_happening){
            int capture_delta = get_value_of_piece(get_type_of_piece(bitboards, from)) - get_value_of_piece(get_type_of_piece(bitboards, to));
            // looking if the opponent can recapture the piece
            int recapture_possible = is_case_threatened(game_settings->color_of_player_that_is_playing, to, bitboards, chess_log);
            // if the opponent can recapture the piece, we don't want to capture it
            if (recapture_possible){
                // if the opponent can recapture the piece, we want to capture it only if it's worth more than the piece that is moving
                // if the piece that is moving is worth more than the piece that is being captured, we don't want to capture it
                scores[i] += ((capture_delta > 0) ? winning_piece_bias : losing_piece_bias) + capture_delta;
            }
            // if the opponent can't recapture the piece, we want to capture it
            else{
                scores[i] += winning_piece_bias + capture_delta;
            }
        }
        // those evaluations of the moves are not useful if we only want to order the captures
        if (!is_captures_only){
            // promoting a pawn is a good move
            // it first need to be a pawn of the good color that is moving (not taken care of in the valid_moves array, but only in is legal move)
            // when a capture is happening, the promotion is not as good of a move
            if (is_promotion_flag(flag) && !is_capture_happening){
                    scores[i] += promoted_piece_bias;
            }
            // castling is a good move
            // it first need to be a king of the good color that is moving (not taken care of in the valid_moves array, but only in is legal move)
            if (flag == Castle_Flag){
                scores[i] += castling_bias;
            }
            // moving a piece is not a good move if the square is attacked by an opponent piece
            if (is_case_threatened(game_settings->color_of_player_that_is_playing, to, bitboards, chess_log)){
                scores[i] -= 25;
            }
        }
        // moving a piece is not a good move if the square is attacked by an opponent pawn
        if (is_square_attacked_by_opponent_pawn(to)){
            scores[i] -= 50;
        }

    }

    // sorting the moves by their score
    quick_sort(valid_moves, scores, 0, nb_moves-1);

    // freeing the scores array
    free(scores);

}


bool is_square_attacked_by_opponent_pawn(int square){

    int file_square = get_file(square);

    // if the player is white, we check if the square is attacked by a black pawn
    if (game_settings->color_of_player_that_is_playing == WHITE){
        // the black pawn could be on the left and one square up (square + 7), but we need to check if the square is not on the left border of the board
        if (square + 7 < NUMBER_SQUARES && file_square != 0 && (bitboards[PAWN_BLACK] & (1ULL << (square + 7)))){
            return true;
        }
        // the black pawn could be on the right and one square up (square + 9), but we need to check if the square is not on the right border of the board
        if (square + 9 < NUMBER_SQUARES && file_square != 7 && (bitboards[PAWN_BLACK] & (1ULL << (square + 9)))){
            return true;
        }
    }
    // if the player is black, we check if the square is attacked by a white pawn
    else if (game_settings->color_of_player_that_is_playing == BLACK){
        // the white pawn could be on the left and one square down (square - 9), but we need to check if the square is not on the left border of the board
        if (square - 9 >= 0 && file_square != 0 && (bitboards[PAWN_WHITE] & (1ULL << (square - 9)))){
            return true;
        }
        // the white pawn could be on the right and one square down (square - 7), but we need to check if the square is not on the right border of the board
        if (square - 7 >= 0 && file_square != 7 && (bitboards[PAWN_WHITE] & (1ULL << (square - 7)))){
            return true;
        }
    }

    // default return value
    return false;

}


void quick_sort(move* valid_moves, int* scores, int low, int high){
    
    if (low < high){
        int pivot = partition(valid_moves, scores, low, high);
        quick_sort(valid_moves, scores, low, pivot - 1);
        quick_sort(valid_moves, scores, pivot + 1, high);
    }

}


int partition(move* valid_moves, int* scores, int low, int high){

    int pivot_score = scores[high];
    // put everything that is lower than the pivot score to the left of the pivot
    int i = low - 1;
    for (int j = low; j < high; j++){
        if (scores[j] > pivot_score){
            i++;
            int temp_score = scores[i];
            scores[i] = scores[j];
            scores[j] = temp_score;
            move temp_move = valid_moves[i];
            valid_moves[i] = valid_moves[j];
            valid_moves[j] = temp_move;
        }
    }
    // Swap the pivot score and move
    int temp_score = scores[i + 1];
    scores[i + 1] = scores[high];
    scores[high] = temp_score;

    move temp_move = valid_moves[i + 1];
    valid_moves[i + 1] = valid_moves[high];
    valid_moves[high] = temp_move;

    return i + 1;

}
