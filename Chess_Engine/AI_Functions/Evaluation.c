#include "Evaluation.h"


int evaluate_position_lvl2_lvl3(){

    int score = 0;
    // getting the score of the pieces
    for (int i=0; i<64; i++){
        int piece = get_type_of_piece(bitboards, i);
        // counting the material value of the pieces
        if (bitboards[WHITE_PIECES] & (1ULL << i)){
            score += get_value_of_piece(piece);
        }
        else if (bitboards[BLACK_PIECES] & (1ULL << i)){
            score -= get_value_of_piece(piece);
        }
        // adding the score of the positional preferences of the pieces
        switch(piece){
            case PAWN_WHITE:
                score += whitePawn_PST[7-i/8][i%8];
                break;
            case PAWN_BLACK:
                score -= blackPawn_PST[7-i/8][i%8];
                break;
            case KNIGHT_WHITE:
                score += whiteKnight_PST[7-i/8][i%8];
                break;
            case KNIGHT_BLACK:
                score -= blackKnight_PST[7-i/8][i%8];
                break;
            case BISHOP_WHITE:
                score += whiteBishop_PST[7-i/8][i%8];
                break;
            case BISHOP_BLACK:  
                score -= blackBishop_PST[7-i/8][i%8];
                break;
            case ROOK_WHITE:
                score += whiteRook_PST[7-i/8][i%8];
                break;
            case ROOK_BLACK:
                score -= blackRook_PST[7-i/8][i%8];
                break;
            case QUEEN_WHITE:
                score += whiteQueen_PST[7-i/8][i%8];
                break;
            case QUEEN_BLACK:   
                score -= blackQueen_PST[7-i/8][i%8];
                break;
            case KING_WHITE:    
                score += whiteKing_PST[7-i/8][i%8];
                break;
            case KING_BLACK:
                score -= blackKing_PST[7-i/8][i%8];
                break;
        }
    }
    // returning the score
    return score;

}


// array to defines some bonuses and penalties for the pawns, in the different evaluations functions
const int passed_pawn_bonuses[7] = {0, 120, 80, 50, 30, 15, 15};
const int isolated_pawn_penalty_by_count[9] = {0, -10, -25, -50, -75, -75, -75, -75, -75};
const int king_pawn_shield_scores[6] = {4, 7, 4, 3, 6, 3};


void piece_square_tables_evaluation(float endgame_white_transition, float endgame_black_transition, int* white_piece_square_tables_score, int* black_piece_square_tables_score){

    for (int i=0; i<64; i++){
        int piece = get_type_of_piece(bitboards, i);
        if (piece != NOTHING){
            switch(piece){
                case PAWN_WHITE:
                    (*white_piece_square_tables_score) += (int) endgame_white_transition * whitePawn_PST_end[7-get_rank(i)][get_file(i)] + (1-endgame_white_transition) * whitePawn_PST[7-get_rank(i)][get_file(i)];
                    break;
                case PAWN_BLACK:
                    (*black_piece_square_tables_score) += (int) endgame_black_transition * blackPawn_PST_end[7-get_rank(i)][get_file(i)] + (1-endgame_black_transition) * blackPawn_PST[7-get_rank(i)][get_file(i)];
                    break;
                case KNIGHT_WHITE:
                    (*white_piece_square_tables_score) += whiteKnight_PST[7-get_rank(i)][get_file(i)];
                    break;
                case KNIGHT_BLACK:
                    (*black_piece_square_tables_score) += blackKnight_PST[7-get_rank(i)][get_file(i)];
                    break;
                case BISHOP_WHITE:
                    (*white_piece_square_tables_score) += whiteBishop_PST[7-get_rank(i)][get_file(i)];
                    break;
                case BISHOP_BLACK:  
                    (*black_piece_square_tables_score) += blackBishop_PST[7-get_rank(i)][get_file(i)];
                    break;
                case ROOK_WHITE:
                    (*white_piece_square_tables_score) += whiteRook_PST[7-get_rank(i)][get_file(i)];
                    break;
                case ROOK_BLACK:
                    (*black_piece_square_tables_score) += blackRook_PST[7-get_rank(i)][get_file(i)];
                    break;
                case QUEEN_WHITE:
                    (*white_piece_square_tables_score) += whiteQueen_PST[7-get_rank(i)][get_file(i)];
                    break;
                case QUEEN_BLACK:
                    (*black_piece_square_tables_score) += blackQueen_PST[7-get_rank(i)][get_file(i)];
                    break;
                case KING_WHITE:
                    (*white_piece_square_tables_score) += (int) endgame_white_transition * whiteKing_PST_end[7-get_rank(i)][get_file(i)] + (1-endgame_white_transition) * whiteKing_PST[7-get_rank(i)][get_file(i)];
                    break;
                case KING_BLACK:
                    (*black_piece_square_tables_score) += (int) endgame_black_transition * blackKing_PST_end[7-get_rank(i)][get_file(i)] + (1-endgame_black_transition) * blackKing_PST[7-get_rank(i)][get_file(i)];
                    break;
            }
        }
    }

}


int* get_pawn_positions(bit_board pawn_bitboard, int nb_pawns){

    int* pawn_positions = (int*)malloc(sizeof(int)*nb_pawns);
    // looking for malloc errors
    if (pawn_positions == NULL){
        printf("Error in malloc\n");
        return NULL;
    }
    int current_index = 0;

    while (pawn_bitboard) {
        // Find the index of the least significant bit that is set
        int index = __builtin_ctzll(pawn_bitboard);
        
        // Add the index to the array and increment the index
        pawn_positions[current_index] = index;
        current_index++;
        
        // Clear the bit we just found
        pawn_bitboard &= pawn_bitboard - 1;
    }

    // returning the indexes of the pawns
    return pawn_positions;

}


bit_board get_adjacent_file_mask(int file_index){

    // getting the file mask shifted to the left (need to be within the board, otherwise it will be 0)
    bit_board file_left_mask = File_A_mask << max(0, file_index - 1);
    // getting the file mask shifted to the right (need to be within the board, otherwise it will be 0)
    bit_board file_right_mask = File_A_mask << min(7, file_index + 1);

    // returning the mask of the pawn by combining the file mask and the two shifted file masks
    return file_left_mask | file_right_mask;

}


bit_board get_pawn_mask(int pawn_position, bit_board pawn_bitboard, int color){

    // getting the file index of the pawn position
    int file_index = get_file(pawn_position);
    // getting the mask of the pawn
    // getting the file mask 
    bit_board file_mask = File_A_mask << file_index;
    bit_board adjacent_mask = get_adjacent_file_mask(file_index);
    // getting the mask of the pawn by combining the file mask and the two shifted file masks
    bit_board pawn_mask = file_mask | adjacent_mask;

    // getting the rank index of the pawn position
    int rank_index = get_rank(pawn_position);
    // getting the rank mask, looking forward (forward means different things for white and black)
    int forward_rank_index = (color == WHITE) ? (rank_index + 1) : (7-(rank_index - 1));
    bit_board rank_mask = 0;
    if (color == WHITE) {
        // getting the rank mask, looking forward
        rank_mask = Full_Bitboard_mask << (forward_rank_index * 8);
    } 
    else {
        // getting the rank mask, looking forward, the other way around on the board
        rank_mask = Full_Bitboard_mask >> (forward_rank_index * 8);
    }

    // returning the mask of the pawn (combining the file and rank masks)
    return pawn_mask & rank_mask;

}


int evaluate_pawns(int color, int nb_pawns, bit_board friendly_pawn_bitboard, bit_board opponent_pawn_bitboard){

    int bonus = 0;
    int number_of_isolated_pawns = 0;

    // getting the indexes of the different pawns of the color 
    int* pawn_positions = get_pawn_positions(friendly_pawn_bitboard, nb_pawns);

    // we look for each pawn to determine its positional score
    for (int i=0; i<nb_pawns; i++){

        // getting a bitboard composed of 1 at the possible reachable squares for the pawn (the mask)
        // it's the squares up and the one that left and right of the pawn (if it is not on the edge of the board)
        bit_board pawn_mask = get_pawn_mask(pawn_positions[i], friendly_pawn_bitboard, color);
        // if the pawn is a passed pawn (no opponent pawn in front of it or ready to eat it on the left or right)
        if ((opponent_pawn_bitboard & pawn_mask) == 0){

            // getting the rank of the pawn and the number of squares to promote
            int rank = get_rank(pawn_positions[i]);
            int nb_squares_to_promote = (color == WHITE) ? 7 - rank : rank;
            // adding the bonus of the passed pawn to the total bonus
            bonus += passed_pawn_bonuses[nb_squares_to_promote];

        }
        // if the pawn is isolated (no friendly pawn on the left or right)
        if ((friendly_pawn_bitboard & get_adjacent_file_mask(get_file(pawn_positions[i]))) == 0){
            number_of_isolated_pawns++;
        }

    }

    // freeing the memory
    if (pawn_positions != NULL){
        free(pawn_positions);
    }
    // returning the bonuses minus the penalty points
    return bonus + isolated_pawn_penalty_by_count[number_of_isolated_pawns];

}


int mop_up_score(int color, int friendly_material, int opponent_material, float opponent_endgame_transition){

    // if the friendly material is less than the opponent material, we need to push the king closer to the opponent king
    if (friendly_material > opponent_material + 2*PAWN_VALUE && opponent_endgame_transition > 0.3){
        
        int mop_up_score = 0;
        // getting the colors of the kings 
        int friendly_color = (color == WHITE) ? WHITE : BLACK;
        int opponent_color = (color == WHITE) ? BLACK : WHITE;
        // getting the indexes of the differents kings 
        int friendly_king_index = get_king_index(bitboards, friendly_color);
        int opponent_king_index = get_king_index(bitboards, opponent_color);
        // encouraging the friendly king to go closer to the opponent king
        mop_up_score += 4 * (14 - Orthogonal_Distance[friendly_king_index][opponent_king_index]);
        // encouraging the friendly king to push the opponent king to the edge of the board
        mop_up_score += 10 * Centre_Manhattan_Distance[friendly_king_index];
        // returning the mop up score multiplied by the endgame transition
        return ((int) mop_up_score * opponent_endgame_transition);

    }

    // default if we're not in a situation of endgame to push the king closer to the opponent king
    return 0;
    
}


int king_pawn_shield_score(int color, int opponent_material, float opponent_endgame_transition, int nb_opponent_queens, int nb_opponent_rooks, int opponent_PST_score){

    // there is no need of a king pawn shield if we're in the endgame since we're pushing our king towards the other king
    if (opponent_endgame_transition >= 1){
        return 0;
    }

    // setting some penalties
    int penalty = 0;
    int uncastled_king_penalty = 0;

    // getting where the king is
    int king_square = get_king_index(bitboards, color);
    int king_file = get_file(king_square);

    // we look if there is a good pawn shield for the king, when it's in a safe spot on a side file
    if (king_file >= 2 && king_file <= 5){

        int* pawn_shield_squares = (int*)malloc(sizeof(int)*6);
        // looking for malloc errors
        if (pawn_shield_squares == NULL){
            printf("Error in malloc\n");
            return 0;
        }

        // udpating the pawn shield squares with the precomputed values
        for (int i=0; i<6; i++){
            pawn_shield_squares[i] = (color == WHITE) ? Pawn_Shield_Squares_White[king_square][i] : Pawn_Shield_Squares_Black[king_square][i];
        }
        // getting the number of pawn shield squares
        int nb_pawn_shield_squares = 0;
        for (int i=0; i<6; i++){
            if (pawn_shield_squares[i] != -1){
                nb_pawn_shield_squares++;
            }
        }

        // going through the pawn shield squares
        for (int i = 0; i<divide_by_two(nb_pawn_shield_squares); i++){

            // if the square is not a pawn shield square, we add a penalty
            if ((!(bitboards[PAWN_WHITE] & (1ULL << pawn_shield_squares[i])) && color == WHITE) || (!(bitboards[PAWN_BLACK] & (1ULL << pawn_shield_squares[i])) && color == BLACK)){
                
                // we add a little penalty if the square is not a pawn shield square but the one above is (rank +- 1 is not but rank +-2 is)
                if (nb_pawn_shield_squares > 3 && ((bitboards[PAWN_WHITE] & (1ULL << pawn_shield_squares[i+3]) && color == WHITE) || (bitboards[PAWN_BLACK] & (1ULL << pawn_shield_squares[i+3]) && color == BLACK))){
                    penalty += king_pawn_shield_scores[i+3];
                }  
                // we add a penalty if the square is not a pawn shield square (a bit stronger than the one before)
                else {
                    penalty += king_pawn_shield_scores[i];
                }

            }

        }

        // incrementing the penalty to make it stronger
        penalty *= penalty;

        // free the memory
        free(pawn_shield_squares);

    }
    // we then look if the king is castled, if not, we add a penalty depending on the developpement of the others player pieces (PST)
    else {

        float opponent_development_score = float_clamp((opponent_PST_score + 10.0f) / 130.0f, 0.0f, 1.0f);
        uncastled_king_penalty = (int)(50 * opponent_development_score);

    }

    // dealing with open file against the king
    int open_file_penalty = 0;

    // if there is enough threating pieces on the opposite side, we look if some penalties needs to be applied
    if (nb_opponent_rooks > 1 || (nb_opponent_rooks > 0 && nb_opponent_queens > 0)){

        // getting the friendly and opponent pawns bitboards
        bit_board friendly_pawn_bitboard = (color == WHITE) ? bitboards[PAWN_WHITE] : bitboards[PAWN_BLACK];
        bit_board opponent_pawn_bitboard = (color == WHITE) ? bitboards[PAWN_BLACK] : bitboards[PAWN_WHITE];

        int clamped_king_file = int_clamp(king_file, 1, 6);
        // looking if the center files near the king are open
        for (int attack_file = clamped_king_file; attack_file <= clamped_king_file+1; attack_file++){

            // getting the file mask 
            bit_board file_A = 0x101010101010101; // A file full of bits 
            bit_board file_mask = file_A << attack_file;
            bool is_king_file = (attack_file == king_file); // if the file is the king file, return true, otherwise false

            // if there is no opponent pawn on the file, then it's an open file for a potential rook or queen, we need to apply a penalty for that (since it's mainly because of us that an ennemy file can be empty)
            if ((opponent_pawn_bitboard & file_mask) == 0){
                
                open_file_penalty += is_king_file ? 25 : 15;
                // then, if the file is free, we need to look if there is a pawn of our own on the file to defend the king from a potential rook or queen
                if ((friendly_pawn_bitboard & file_mask) == 0){
                    open_file_penalty += is_king_file ? 15 : 10;
                }

            }

        }

    }

    // getting the weight we need to apply to the penalties
    float pawn_shield_weight = 1 - opponent_endgame_transition;
    // if there is no opponent queen, we even can lower the penalty
    if (nb_opponent_queens == 0){
        pawn_shield_weight *= 0.6f;
    }

    // returning the penalties
    return ((int)((-penalty -uncastled_king_penalty -open_file_penalty) * pawn_shield_weight));

}


int evaluate(){

    // value to state if a color is in its endgame
    int queen_endgame_weight = 45;
    int rook_endgame_weight = 20;
    int bishop_endgame_weight = 10;
	int knight_endgame_weight = 10;
    int endgame_start_weight = 2 * rook_endgame_weight + 2 * knight_endgame_weight + 2 * bishop_endgame_weight + queen_endgame_weight;


    // getting all the necessary info concerning the white material
    // getting the numbers of pieces
    int nb_white_pawns = __builtin_popcountll(bitboards[PAWN_WHITE]);
    int nb_white_knights = __builtin_popcountll(bitboards[KNIGHT_WHITE]);
    int nb_white_bishops = __builtin_popcountll(bitboards[BISHOP_WHITE]);
    int nb_white_rooks = __builtin_popcountll(bitboards[ROOK_WHITE]);
    int nb_white_queens = __builtin_popcountll(bitboards[QUEEN_WHITE]);
    // int nb_white_major_pieces = nb_white_rooks + nb_white_queens; // not used
    // int nb_white_minor_pieces = nb_white_knights + nb_white_bishops; // not used
    // getting the material value of the white pieces
    int white_material = nb_white_pawns * PAWN_VALUE + nb_white_knights * KNIGHT_VALUE + nb_white_bishops * BISHOP_VALUE + nb_white_rooks * ROOK_VALUE + nb_white_queens * QUEEN_VALUE;
    // getting our near the endgame we are
    int endgame_weight_sum_white = nb_white_rooks * rook_endgame_weight + nb_white_bishops * bishop_endgame_weight + nb_white_knights * knight_endgame_weight + nb_white_queens * queen_endgame_weight;
    float endgame_white_transition = 0;
    if (1 > (float) endgame_weight_sum_white / endgame_start_weight){
        endgame_white_transition = 1 - (float) endgame_weight_sum_white / endgame_start_weight;
    }


    // getting all the necessary info concerning the black material
    // getting the numbers of pieces
    int nb_black_pawns = __builtin_popcountll(bitboards[PAWN_BLACK]);
    int nb_black_knights = __builtin_popcountll(bitboards[KNIGHT_BLACK]);
    int nb_black_bishops = __builtin_popcountll(bitboards[BISHOP_BLACK]);
    int nb_black_rooks = __builtin_popcountll(bitboards[ROOK_BLACK]);
    int nb_black_queens = __builtin_popcountll(bitboards[QUEEN_BLACK]);
    // int nb_black_major_pieces = nb_black_rooks + nb_black_queens; // not used
    // int nb_black_minor_pieces = nb_black_knights + nb_black_bishops; // not used
    // getting the material value of the black pieces
    int black_material = nb_black_pawns * PAWN_VALUE + nb_black_knights * KNIGHT_VALUE + nb_black_bishops * BISHOP_VALUE + nb_black_rooks * ROOK_VALUE + nb_black_queens * QUEEN_VALUE;
    // getting our near the endgame we are
    int endgame_weight_sum_black = nb_black_rooks * rook_endgame_weight + nb_black_bishops * bishop_endgame_weight + nb_black_knights * knight_endgame_weight + nb_black_queens * queen_endgame_weight;
    float endgame_black_transition = 0;
    if (1 > (float) endgame_weight_sum_black / endgame_start_weight){
        endgame_black_transition = 1 - (float) endgame_weight_sum_black / endgame_start_weight;
    }


    // getting the score of the position, it a white - black score, if the score is positive, white is winning, if it is negative, black is winning
    int score = 0;
    
    // adding the material value of the pieces
    score += white_material - black_material;

    // adding the score of the positional preferences of the pieces
    int white_piece_square_tables_score = 0;
    int black_piece_square_tables_score = 0;
    piece_square_tables_evaluation(endgame_white_transition, endgame_black_transition, &white_piece_square_tables_score, &black_piece_square_tables_score);
    score += white_piece_square_tables_score - black_piece_square_tables_score;

    // adding the mp_up_score, to see if the king is pushing the opponent king in a endgame situation
    score += mop_up_score(WHITE, white_material, black_material, endgame_black_transition); 
    score -= mop_up_score(BLACK, black_material, white_material, endgame_white_transition);

    // adding the pawn score, to see if there are passed pawns, isolated pawns, etc.
    score += evaluate_pawns(WHITE, nb_white_pawns, bitboards[PAWN_WHITE], bitboards[PAWN_BLACK]);
    score -= evaluate_pawns(BLACK, nb_black_pawns, bitboards[PAWN_BLACK], bitboards[PAWN_WHITE]);

    // adding the king pawn shield score, to see if the king is protected by pawns
    score += king_pawn_shield_score(WHITE, black_material, endgame_black_transition, nb_black_queens, nb_black_rooks, black_piece_square_tables_score);
    score -= king_pawn_shield_score(BLACK, white_material, endgame_white_transition, nb_white_queens, nb_white_rooks, white_piece_square_tables_score);


    // if the player playing is black, we need to change the sign of the score
    int turn_color = (game_settings->color_of_player_that_is_playing == WHITE) ? 1 : -1;
    // returning the score
    return score * turn_color;

}
