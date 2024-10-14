#include "Moves_Treatment.h"


bit_board** precomputed_pawn_attacks;
bit_board** precomputed_pawn_moves;
bit_board* precomputed_knight_attacks;
bit_board* precomputed_king_attacks;
bit_board* precomputed_rook_attacks;
bit_board* precomputed_bishop_attacks;


void initialize_pawn_attacks() {

    // allocate memory for the precomputed pawn attacks
    precomputed_pawn_attacks = (bit_board**) malloc(2 * sizeof(bit_board*));
    // looking for malloc errors
    if (precomputed_pawn_attacks == NULL){
        printf("Error: not enough memory to allocate the precomputed pawn attacks array\n");
        return;
    }
    for (int i = 0; i < 2; i++){
        precomputed_pawn_attacks[i] = (bit_board*) malloc(64 * sizeof(bit_board));
        // looking for malloc errors
        if (precomputed_pawn_attacks[i] == NULL){
            printf("Error: not enough memory to allocate the precomputed pawn attacks array\n");
            return;
        }
    }

    for (int square = 0; square < 64; square++) {
        bit_board white_attacks = Empty_Bitboard_mask;
        bit_board black_attacks = Empty_Bitboard_mask;
        int rank = get_rank(square);
        int file = get_file(square);

        // White pawns attack one square diagonally up
        if (rank < 7) {
            // Diagonal up-left
            if (file > 0) {
                white_attacks |= (1ULL << (square + 7));
            }
            // Diagonal up-right
            if (file < 7) {
                white_attacks |= (1ULL << (square + 9));
            }
        }

        // Black pawns attack one square diagonally down
        if (rank > 0) {
            // Diagonal down-left
            if (file > 0) {
                black_attacks |= (1ULL << (square - 9));
            }
            // Diagonal down-right
            if (file < 7) {
                black_attacks |= (1ULL << (square - 7));
            }
        }

        precomputed_pawn_attacks[WHITE][square] = white_attacks;
        precomputed_pawn_attacks[BLACK][square] = black_attacks;
    }

}


void initialize_pawn_moves(){

    // allocate memory for the precomputed pawn moves
    precomputed_pawn_moves = (bit_board**) malloc(2 * sizeof(bit_board*));
    // looking for malloc errors
    if (precomputed_pawn_moves == NULL){
        printf("Error: not enough memory to allocate the precomputed pawn moves array\n");
        return;
    }
    for (int i = 0; i < 2; i++){
        precomputed_pawn_moves[i] = (bit_board*) malloc(64 * sizeof(bit_board));
        // looking for malloc errors
        if (precomputed_pawn_moves[i] == NULL){
            printf("Error: not enough memory to allocate the precomputed pawn moves array\n");
            return;
        }
    }

    for (int square = 0; square < 64; square++) {
        bit_board white_moves = Empty_Bitboard_mask;
        bit_board black_moves = Empty_Bitboard_mask;
        int rank = get_rank(square);
        int file = get_file(square);

        // White pawns moves
        if (rank < 7) {
            // up one square
            white_moves |= (1ULL << (square + 8)); 
            // up two squares from the starting rank
            if (rank == 1) {
                white_moves |= (1ULL << (square + 16)); 
            }
            // capture diagonally left
            if (file > 0) {
                white_moves |= (1ULL << (square + 7)); 
            }
            // capture diagonally right
            if (file < 7) {
                white_moves |= (1ULL << (square + 9));
            }
        }
        

        // Black pawns moves
        if (rank > 0) {
            // down one square
            black_moves |= (1ULL << (square - 8)); 
            // down two squares from the starting rank
            if (rank == 6) {
                black_moves |= (1ULL << (square - 16)); 
            }
            // capture diagonally left
            if (file > 0) {
                black_moves |= (1ULL << (square - 9)); 
            }
            // capture diagonally right
            if (file < 7) {
                black_moves |= (1ULL << (square - 7));
            }
        }

        precomputed_pawn_moves[WHITE][square] = white_moves;
        precomputed_pawn_moves[BLACK][square] = black_moves;
    }

}


void initialize_knight_attacks() {

    // allocate memory for the precomputed knight attacks
    precomputed_knight_attacks = (bit_board*) malloc(64 * sizeof(bit_board));
    // looking for malloc errors
    if (precomputed_knight_attacks == NULL){
        printf("Error: not enough memory to allocate the precomputed knight attacks array\n");
        return;
    }
    
    // Knight offsets 
    int knight_offsets[8][2] = {
        { 2, 1 }, { 2, -1 }, { -2, 1 }, { -2, -1 },
        { 1, 2 }, { 1, -2 }, { -1, 2 }, { -1, -2 }
    };

    // All possible knight moves from this square
    for (int square = 0; square < 64; square++) {
        bit_board attacks = Empty_Bitboard_mask;
        int rank = get_rank(square);
        int file = get_file(square);

        for (int i = 0; i < 8; i++) {
            int new_rank = rank + knight_offsets[i][0];
            int new_file = file + knight_offsets[i][1];
            if (new_rank >= 0 && new_rank < 8 && new_file >= 0 && new_file < 8) {
                int new_square = new_rank * 8 + new_file;
                attacks |= (1ULL << new_square);
            }
        }
        precomputed_knight_attacks[square] = attacks;
    }

}


void initialize_king_attacks() {

    // allocate memory for the precomputed king attacks
    precomputed_king_attacks = (bit_board*) malloc(64 * sizeof(bit_board));
    // looking for malloc errors
    if (precomputed_king_attacks == NULL){
        printf("Error: not enough memory to allocate the precomputed king attacks array\n");
        return;
    }

    // King offsets
    int king_offsets[8][2] = {
        { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 },
        { 1, 1 }, { 1, -1 }, { -1, 1 }, { -1, -1 }
    };

    // All possible king moves from this square
    for (int square = 0; square < 64; square++) {
        bit_board attacks = Empty_Bitboard_mask;
        int rank = get_rank(square);
        int file = get_file(square);

        for (int i = 0; i < 8; i++) {
            int new_rank = rank + king_offsets[i][0];
            int new_file = file + king_offsets[i][1];
            if (new_rank >= 0 && new_rank < 8 && new_file >= 0 && new_file < 8) {
                int new_square = new_rank * 8 + new_file;
                attacks |= (1ULL << new_square);
            }
        }
        precomputed_king_attacks[square] = attacks;
    }

}


void initialize_rook_attacks() {

    // allocate memory for the precomputed rook attacks
    precomputed_rook_attacks = (bit_board*) malloc(64 * sizeof(bit_board));
    // looking for malloc errors
    if (precomputed_rook_attacks == NULL){
        printf("Error: not enough memory to allocate the precomputed rook attacks array\n");
        return;
    }

    // Direction offsets for rook (horizontal and vertical)
    int rook_offsets[4][2] = {
        { 1, 0 }, { -1, 0 }, { 0, 1 }, { 0, -1 }
    };

    // All possible rook moves from this square
    for (int square = 0; square < 64; square++) {
        bit_board attacks = Empty_Bitboard_mask;
        int rank = get_rank(square);
        int file = get_file(square);

        for (int i = 0; i < 4; i++) {
            int new_rank = rank + rook_offsets[i][0];
            int new_file = file + rook_offsets[i][1];
            while (new_rank >= 0 && new_rank < 8 && new_file >= 0 && new_file < 8) {
                int new_square = new_rank * 8 + new_file;
                attacks |= (1ULL << new_square);
                new_rank += rook_offsets[i][0];
                new_file += rook_offsets[i][1];
            }
        }
        precomputed_rook_attacks[square] = attacks;
    }
}


void initialize_bishop_attacks() {

    // allocate memory for the precomputed bishop attacks
    precomputed_bishop_attacks = (bit_board*) malloc(64 * sizeof(bit_board));
    // looking for malloc errors
    if (precomputed_bishop_attacks == NULL){
        printf("Error: not enough memory to allocate the precomputed bishop attacks array\n");
        return;
    }

    // Direction offsets for bishop (diagonal)
    int bishop_offsets[4][2] = {
        { 1, 1 }, { -1, -1 }, { 1, -1 }, { -1, 1 }
    };

    // All possible bishop moves from this square
    for (int square = 0; square < 64; square++) {
        bit_board attacks = Empty_Bitboard_mask;
        int rank = get_rank(square);
        int file = get_file(square);

        for (int i = 0; i < 4; i++) {
            int new_rank = rank + bishop_offsets[i][0];
            int new_file = file + bishop_offsets[i][1];
            while (new_rank >= 0 && new_rank < 8 && new_file >= 0 && new_file < 8) {
                int new_square = new_rank * 8 + new_file;
                attacks |= (1ULL << new_square);
                new_rank += bishop_offsets[i][0];
                new_file += bishop_offsets[i][1];
            }
        }
        precomputed_bishop_attacks[square] = attacks;
    }

}


void initialize_attacks() {
    
    initialize_pawn_attacks();
    initialize_pawn_moves();
    initialize_knight_attacks();
    initialize_king_attacks();
    initialize_rook_attacks();
    initialize_bishop_attacks();

}


bit_board calculate_pawn_moves_with_blockers(int pawn_pos, int color_moving, bit_board all_pieces){

    bit_board pawn_move = precomputed_pawn_moves[color_moving][pawn_pos];
    int rank = get_rank(pawn_pos);
    int file = get_file(pawn_pos);

    // for the white pawns 
    if (color_moving == WHITE){
        // if the square in front of the pawn is occupied, the pawn can't move there
        if ((all_pieces & (1ULL << (pawn_pos + 8)))){
            pawn_move &= ~(1ULL << (pawn_pos + 8));
            pawn_move &= ~(1ULL << (pawn_pos + 16));
        }
        // else we look if the pawn is on the starting rank and if the square two squares in front of the pawn is occupied
        else if (rank == 1 && (all_pieces & (1ULL << (pawn_pos + 16)))){
            pawn_move &= ~(1ULL << (pawn_pos + 16));
        }
        // looking for the left diagonal capture not possible (left edge or no piece to capture)
        if (file == 0 || !(all_pieces & (1ULL << (pawn_pos + 7)))){
            pawn_move &= ~(1ULL << (pawn_pos + 7));
        }
        // looking for the right diagonal capture not possible (right edge or no piece to capture)
        if (file == 7 || !(all_pieces & (1ULL << (pawn_pos + 9)))){
            pawn_move &= ~(1ULL << (pawn_pos + 9));
        }
    }

    // for the black pawns 
    if (color_moving == BLACK){
        // if the square in front of the pawn is occupied, the pawn can't move there
        if ((all_pieces & (1ULL << (pawn_pos - 8)))){
            pawn_move &= ~(1ULL << (pawn_pos - 8));
            pawn_move &= ~(1ULL << (pawn_pos - 16));
        }
        // else we look if the pawn is on the starting rank and if the square two squares in front of the pawn is occupied
        else if (rank == 6 && (all_pieces & (1ULL << (pawn_pos - 16)))){
            pawn_move &= ~(1ULL << (pawn_pos - 16));
        }
        // looking for the left diagonal capture not possible (left edge or no piece to capture)
        if (file == 0 || !(all_pieces & (1ULL << (pawn_pos - 9)))){
            pawn_move &= ~(1ULL << (pawn_pos - 9));
        }
        // looking for the right diagonal capture not possible (right edge or no piece to capture)
        if (file == 7 || !(all_pieces & (1ULL << (pawn_pos - 7)))){
            pawn_move &= ~(1ULL << (pawn_pos - 7));
        }
    }
    
    return pawn_move;

}


bit_board calculate_rook_attacks_with_blockers(int rook_pos, bit_board all_pieces) {
    
    // Calculate the full attack bitboard without blockers
    bit_board full_attack = precomputed_rook_attacks[rook_pos];

    // Create a bitboard to store the effective attacks with blockers
    bit_board effective_attacks = Empty_Bitboard_mask;

    // Directions: up, down, left, right
    int directions[] = {8, -8, 1, -1}; // 8 for up, -8 for down, 1 for right, -1 for left

    // For each direction
    for (int dir = 0; dir < 4; dir++) {
        int current_square = rook_pos; // Start from the rook's position
        int prev_file = get_file(rook_pos); // Get the file of the current square
        
        while (true) {
            // Move to the next square in the current direction
            current_square += directions[dir];
            
            // Check if we are out of bounds
            if (current_square < 0 || current_square >= 64) {
                break; // Out of bounds
            }

            // For left/right movement, check that the file doesn't wrap around
            if (directions[dir] == 1 || directions[dir] == -1) {
                int current_file = get_file(current_square);
                if (abs(current_file - prev_file) != 1) {
                    break; // Stop if the file change isn't valid
                }
                prev_file = current_file; // Update the previous file for the next iteration
            }

            // If this square is a blocker, add it to effective attacks and stop in this direction
            if (all_pieces & (1ULL << current_square)) {
                effective_attacks |= (1ULL << current_square);
                break; // Stop scanning in this direction
            }
            
            // If this square is part of the full attack, add it to effective attacks
            if (full_attack & (1ULL << current_square)) {
                effective_attacks |= (1ULL << current_square); // Add this square to effective attacks
            }
        }
    }
    
    return effective_attacks;
}


bit_board calculate_bishop_attacks_with_blockers(int bishop_pos, bit_board all_pieces) {
    
    // Calculate the full attack bitboard without blockers
    bit_board full_attack = precomputed_bishop_attacks[bishop_pos];

    // Create a bitboard to store the effective attacks with blockers
    bit_board effective_attacks = Empty_Bitboard_mask;

    // Directions: top-left, top-right, bottom-left, bottom-right
    int directions[] = {-9, -7, 7, 9}; // Diagonal movements

    // For each direction
    for (int dir = 0; dir < 4; dir++) {
        int current_square = bishop_pos; // Start from the bishop's position
        int prev_file = get_file(bishop_pos); // Get file of the current square
        
        while (true) {
            // Move to the next square in the current direction
            current_square += directions[dir];

            // Check if we are out of bounds
            if (current_square < 0 || current_square >= 64) {
                break; // Out of bounds
            }
            
            int current_file = get_file(current_square); // Get the file of the new square

            // Check if this square crosses the lateral edge (ensures diagonal movement stays valid)
            if (abs(current_file - prev_file) != 1) {
                break; // Crossed file boundary, stop scanning
            }

            // If the square is part of the full attack, add it to effective attacks
            if (full_attack & (1ULL << current_square)) {
                effective_attacks |= (1ULL << current_square); // Add square to effective attacks
            }

            // Check if this square is a blocker
            if (all_pieces & (1ULL << current_square)) {
                break; // Stop scanning in this direction when we hit a blocker
            }

            prev_file = current_file; // Update previous file
        }
    }

    return effective_attacks;
}


move get_move_value_without_flag(int from, int to){
    
    return (move)(from | to << 6);

}


move get_move_value(int from, int to, int flag){
    
    return (move)(from | to << 6 | flag << 12);

}


void add_flag_to_move(move* move_value, int flag){
    
    *move_value = *move_value | flag << 12;

}


bool is_move_null(move move_value){

    return (move_value == 0);

}


bool are_same_move(move move_a, move move_b){

    return move_a == move_b;

}


int get_from_square(move move_value){

    return move_value & start_square_mask;

}


int get_to_square(move move_value){

    return (move_value & target_square_mask) >> 6;

}


int get_flag(move move_value){

    return move_value >> 12;

}


bool is_promotion_flag(int move_flag){
    
    return move_flag >= Promote_To_Queen_Flag;

}


int get_type_of_promoted_piece(int move_flag, int color){
    
    if (move_flag == Promote_To_Queen_Flag && color == WHITE){
        return QUEEN_WHITE;
    }
    if (move_flag == Promote_To_Queen_Flag && color == BLACK){
        return QUEEN_BLACK;
    }
    if (move_flag == Promote_To_Rook_Flag && color == WHITE){
        return ROOK_WHITE;
    }
    if (move_flag == Promote_To_Rook_Flag && color == BLACK){
        return ROOK_BLACK;
    }
    if (move_flag == Promote_To_Bishop_Flag && color == WHITE){
        return BISHOP_WHITE;
    }
    if (move_flag == Promote_To_Bishop_Flag && color == BLACK){
        return BISHOP_BLACK;
    }
    if (move_flag == Promote_To_Knight_Flag && color == WHITE){
        return KNIGHT_WHITE;
    }
    if (move_flag == Promote_To_Knight_Flag && color == BLACK){
        return KNIGHT_BLACK;
    }
    return NOTHING;

}


void set_castling_flag(castling_rights_flags* castling_rights, castling_rights_flags flag) {
    
    *castling_rights |= flag;

}


bool is_castling_flag_set(castling_rights_flags castling_rights, castling_rights_flags flag) {
    
    return (castling_rights & flag) != 0;

}


int is_legal_move(int attacking_color, bit_board* bitboard_array, int from, int to, int flag){

    // we already know the type of the piece that is attacking if the flag is an en_passant one or a castling one
    if (flag == En_Passant_Flag){
        if (attacking_color == WHITE){
            return PAWN_WHITE;
        }
        else if (attacking_color == BLACK){
            return PAWN_BLACK;
        }
    }
    if (flag == Castle_Flag){
        if (attacking_color == WHITE){
            return KING_WHITE;
        }
        else if (attacking_color == BLACK){
            return KING_BLACK;
        }
    }

    int from_rank = get_rank(from);
    int to_rank = get_rank(to);
    int from_file = get_file(from);
    int to_file = get_file(to);
    int rank_diff = to_rank - from_rank;
    int file_diff = to_file - from_file;

    // get the type of piece that is attacking at the "from" square
    int piece_type_attacking = get_type_of_piece(bitboard_array, from);
    // if there is no piece at the "from" square, return NOTHING, early exit is easier to avoid calculating other things
    if (piece_type_attacking == NOTHING){
        return NOTHING;
    }
    // depending on the type of the piece that is attacking, we check if the move is legal
    // but not always the same way, to fast things forward we look if that piece is at the "from" square, but for rooks and bishops, we also check if the move somehow look like a rook or a bishop move (straight line moves)
    // precomputed moves and blockers are used to check if the move is legal so that it's faster
    if (piece_type_attacking == PAWN_WHITE && attacking_color == WHITE){
        bit_board pawn_move = calculate_pawn_moves_with_blockers(from, WHITE, bitboard_array[WHITE_PIECES] | bitboard_array[BLACK_PIECES]);
        if ((pawn_move & (1ULL << to)) && !(bitboard_array[WHITE_PIECES] & (1ULL << to))){
            return piece_type_attacking;
        }
    }
    else if (piece_type_attacking == PAWN_BLACK && attacking_color == BLACK){
        bit_board pawn_move = calculate_pawn_moves_with_blockers(from, BLACK, bitboard_array[WHITE_PIECES] | bitboard_array[BLACK_PIECES]);
        if ((pawn_move & (1ULL << to)) && !(bitboard_array[BLACK_PIECES] & (1ULL << to))){
            return piece_type_attacking;
        }
    }
    else if (piece_type_attacking == KNIGHT_WHITE && attacking_color == WHITE){
        bit_board knight_attacks = precomputed_knight_attacks[from];
        if ((knight_attacks & (1ULL << to)) && !(bitboard_array[WHITE_PIECES] & (1ULL << to))){
            return piece_type_attacking;
        }
    }
    else if (piece_type_attacking == KNIGHT_BLACK && attacking_color == BLACK){
        bit_board knight_attacks = precomputed_knight_attacks[from];
        if ((knight_attacks & (1ULL << to)) && !(bitboard_array[BLACK_PIECES] & (1ULL << to))){
            return piece_type_attacking;
        }
    }
    else if (piece_type_attacking == KING_WHITE && attacking_color == WHITE){
        bit_board king_attacks = precomputed_king_attacks[from];
        if ((king_attacks & (1ULL << to)) && !(bitboard_array[WHITE_PIECES] & (1ULL << to))){
            return piece_type_attacking;
        }
    }
    else if (piece_type_attacking == KING_BLACK && attacking_color == BLACK){
        bit_board king_attacks = precomputed_king_attacks[from];
        if ((king_attacks & (1ULL << to)) && !(bitboard_array[BLACK_PIECES] & (1ULL << to))){
            return piece_type_attacking;
        }
    }
    else if ((piece_type_attacking == ROOK_WHITE || piece_type_attacking == QUEEN_WHITE) && attacking_color == WHITE && ((rank_diff == 0 && file_diff != 0) || (rank_diff != 0 && file_diff == 0))){
        bit_board rook_attacks = calculate_rook_attacks_with_blockers(from, bitboard_array[WHITE_PIECES] | bitboard_array[BLACK_PIECES]);
        if ((rook_attacks & (1ULL << to)) && !(bitboard_array[WHITE_PIECES] & (1ULL << to))){
            return piece_type_attacking;
        }
    }
    else if ((piece_type_attacking == ROOK_BLACK || piece_type_attacking == QUEEN_BLACK) && attacking_color == BLACK && ((rank_diff == 0 && file_diff != 0) || (rank_diff != 0 && file_diff == 0))){
        bit_board rook_attacks = calculate_rook_attacks_with_blockers(from, bitboard_array[WHITE_PIECES] | bitboard_array[BLACK_PIECES]);
        if ((rook_attacks & (1ULL << to)) && !(bitboard_array[BLACK_PIECES] & (1ULL << to))){
            return piece_type_attacking;
        }
    }
    else if ((piece_type_attacking == BISHOP_WHITE || piece_type_attacking == QUEEN_WHITE) && attacking_color == WHITE && (rank_diff == file_diff || rank_diff == -file_diff)){
        bit_board bishop_attacks = calculate_bishop_attacks_with_blockers(from, bitboard_array[WHITE_PIECES] | bitboard_array[BLACK_PIECES]);
        if ((bishop_attacks & (1ULL << to)) && !(bitboard_array[WHITE_PIECES] & (1ULL << to))){
            return piece_type_attacking;
        }
    }
    else if ((piece_type_attacking == BISHOP_BLACK || piece_type_attacking == QUEEN_BLACK) && attacking_color == BLACK && (rank_diff == file_diff || rank_diff == -file_diff)){
        bit_board bishop_attacks = calculate_bishop_attacks_with_blockers(from, bitboard_array[WHITE_PIECES] | bitboard_array[BLACK_PIECES]);
        if ((bishop_attacks & (1ULL << to)) && !(bitboard_array[BLACK_PIECES] & (1ULL << to))){
            return piece_type_attacking;
        }
    }

    // default
    return NOTHING;

}


int get_king_index(bit_board* bitboard_array, int color){
    
    if (color == WHITE){
        // if there is no king on the board, return -1
        if (bitboard_array[KING_WHITE] == 0x0000000000000000ULL){
            return -1;
        }
        // return the index of the king, only if the king is present on the board, otherwise, the answer is not consistent
        return __builtin_ctzll(bitboard_array[KING_WHITE]);
    }
    else if (color == BLACK){
        // if there is no king on the board, return -1
        if (bitboard_array[KING_BLACK] == 0x0000000000000000ULL){
            return -1;
        }
        // return the index of the king, only if the king is present on the board, otherwise, the answer is not consistent
        return __builtin_ctzll(bitboard_array[KING_BLACK]);
    }
    return -1;

}


bool is_case_threatened(int color, int case_index, bit_board* bitboard_array, Log* log){

    // look for en passant (the out of range will be dealt with in the is_en_passant_possible function)
    if (is_en_passant_possible(BLACK, bitboard_array, case_index, case_index + 7, log)){
        return true;
    }
    if (is_en_passant_possible(BLACK, bitboard_array, case_index, case_index + 9, log)){
        return true;
    }
    if (is_en_passant_possible(WHITE, bitboard_array, case_index, case_index - 7, log)){
        return true;
    }
    if (is_en_passant_possible(WHITE, bitboard_array, case_index, case_index - 9, log)){
        return true;
    }

    // look for threats from opponent pawns
    bit_board pawn_attacks = precomputed_pawn_attacks[color][case_index];
    if (pawn_attacks & ((color == WHITE) ? bitboard_array[PAWN_BLACK] : bitboard_array[PAWN_WHITE])) {
        return true;
    }

    // look for threats from opponent knights
    bit_board knight_attacks = precomputed_knight_attacks[case_index];
    if (knight_attacks & ((color == WHITE) ? bitboard_array[KNIGHT_BLACK] : bitboard_array[KNIGHT_WHITE])) {
        return true;
    }

    // look for threats from opponent kings
    bit_board king_attacks = precomputed_king_attacks[case_index];
    if (king_attacks & ((color == WHITE) ? bitboard_array[KING_BLACK] : bitboard_array[KING_WHITE])) {
        return true;
    }

    // look for threats from sliding pieces (rooks, bishops, queens)
    bit_board rook_attacks = calculate_rook_attacks_with_blockers(case_index, bitboard_array[WHITE_PIECES] | bitboard_array[BLACK_PIECES]);
    if (rook_attacks & ((color == WHITE) ? bitboard_array[ROOK_BLACK] : bitboard_array[ROOK_WHITE])) {
        return true;
    }
    if (rook_attacks & ((color == WHITE) ? bitboard_array[QUEEN_BLACK] : bitboard_array[QUEEN_WHITE])) {
        return true;
    }
    bit_board bishop_attacks = calculate_bishop_attacks_with_blockers(case_index, bitboard_array[WHITE_PIECES] | bitboard_array[BLACK_PIECES]);
    if (bishop_attacks & ((color == WHITE) ? bitboard_array[BISHOP_BLACK] : bitboard_array[BISHOP_WHITE])) {
        return true;
    }
    if (bishop_attacks & ((color == WHITE) ? bitboard_array[QUEEN_BLACK] : bitboard_array[QUEEN_WHITE])) {
        return true;
    }
   
    // if no threat is found, return false
    return false;

}


int is_check(int color, bit_board* bitboard_array, Log* log){

    // get the index of the king
    int king_index = get_king_index(bitboard_array, color);

    // check if the king is threatened
    if (is_case_threatened(color, king_index, bitboard_array, log)){
        return CHECK;
    }
    return NO_CHECK;
}


bool is_castle_possible(int color, bit_board* bitboard_array, int from, int to, Log* log){

    // the log size must be at least 1
    if (log->actual_size == 0){
        return false;
    }

    // returning 0 if the starting square is not the king (to avoid having to calculate the is case threatened function that is heavy)
    if (color == WHITE && !(bitboard_array[KING_WHITE] & (1ULL << from))){
        return false;
    }
    if (color == BLACK && !(bitboard_array[KING_BLACK] & (1ULL << from))){
        return false;
    }

    // for the white player
    if (color == WHITE){

        // check if the king is moving two squares to the right for a short castle
        if (from == 4 && to == 6){
            
            // first we need to check in the log if all the parameters for this castle are false
            if (is_castling_flag_set(log->moves[log->actual_size-1]->castling_rights, White_King_Moved_Flag) || is_castling_flag_set(log->moves[log->actual_size-1]->castling_rights, White_Rook_H_Moved_Flag)){
                return false;
            }
            // check if the rook is at the right place
            if (!(bitboard_array[ROOK_WHITE] & (1ULL << 7))){
                return false;
            }
            // check if the squares between the king and the rook are empty
            // if a white piece is on the squares 5 or 6, the castle is not possible
            if (bitboard_array[WHITE_PIECES] & (1ULL << 5) || bitboard_array[WHITE_PIECES] & (1ULL << 6)){
                return false;
            }
            // if a black piece is on the squares 5 or 6, the castle is not possible
            if (bitboard_array[BLACK_PIECES] & (1ULL << 5) || bitboard_array[BLACK_PIECES] & (1ULL << 6)){
                return false;
            }
            // check if the squares between the king and the rook are not threatened, but the king need also not to be threatened
            if (is_case_threatened(WHITE, 4, bitboard_array, log)){
                return false;
            }
            if (is_case_threatened(WHITE, 5, bitboard_array, log)){
                return false;
            }
            if (is_case_threatened(WHITE, 6, bitboard_array, log)){
                return false;
            }
            // if all the conditions are met, the castle is possible
            return true;
        }

        // check if the king is moving two squares to the left for a long castle
        if (from == 4 && to == 2){

            // first we need to check in the log if all the parameters for this castle are false
            if (is_castling_flag_set(log->moves[log->actual_size-1]->castling_rights, White_King_Moved_Flag) || is_castling_flag_set(log->moves[log->actual_size-1]->castling_rights, White_Rook_A_Moved_Flag)){
                return false;
            }
            // check if the rook is at the right place
            if (!(bitboard_array[ROOK_WHITE] & (1ULL << 0))){
                return false;
            }
            // check if the squares between the king and the rook are empty
            // if a white piece is on the squares 1 or 2 or 3, the castle is not possible
            if (bitboard_array[WHITE_PIECES] & (1ULL << 3) || bitboard_array[WHITE_PIECES] & (1ULL << 2) || bitboard_array[WHITE_PIECES] & (1ULL << 1)){
                return false;
            }
            // if a black piece is on the squares 1 or 2 or 3, the castle is not possible
            if (bitboard_array[BLACK_PIECES] & (1ULL << 3) || bitboard_array[BLACK_PIECES] & (1ULL << 2) || bitboard_array[BLACK_PIECES] & (1ULL << 1)){
                return false;
            }
            // check if the squares between the king and the rook are not threatened, but the king need also not to be threatened
            if (is_case_threatened(WHITE, 4, bitboard_array, log)){
                return false;
            }
            if (is_case_threatened(WHITE, 3, bitboard_array, log)){
                return false;
            }
            if (is_case_threatened(WHITE, 2, bitboard_array, log)){
                return false;
            }
            // if all the conditions are met, the castle is possible
            return true;
        }

    }
    // for the black player
    else if (color == BLACK){
        
        // check if the king is moving two squares to the right for a short castle
        if (from == 60 && to == 62){

            // first we need to check in the log if all the parameters for this castle are false
            if (is_castling_flag_set(log->moves[log->actual_size-1]->castling_rights, Black_King_Moved_Flag) || is_castling_flag_set(log->moves[log->actual_size-1]->castling_rights, Black_Rook_H_Moved_Flag)){
                return false;
            }
            // check if the rook is at the right place
            if (!(bitboard_array[ROOK_BLACK] & (1ULL << 63))){
                return false;
            }
            // check if the squares between the king and the rook are empty
            // if a black piece is on the squares 61 or 62, the castle is not possible
            if (bitboard_array[BLACK_PIECES] & (1ULL << 61) || bitboard_array[BLACK_PIECES] & (1ULL << 62)){
                return false;
            }
            // if a white piece is on the squares 61 or 62, the castle is not possible
            if (bitboard_array[WHITE_PIECES] & (1ULL << 61) || bitboard_array[WHITE_PIECES] & (1ULL << 62)){
                return false;
            }
            // check if the squares between the king and the rook are not threatened, but the king need also not to be threatened
            if (is_case_threatened(BLACK, 60, bitboard_array, log)){
                return false;
            }
            if (is_case_threatened(BLACK, 61, bitboard_array, log)){
                return false;
            }
            if (is_case_threatened(BLACK, 62, bitboard_array, log)){
                return false;
            }
            // if all the conditions are met, the castle is possible
            return true;
        }

        // check if the king is moving two squares to the left for a long castle
        if (from == 60 && to == 58){

            // first we need to check in the log if all the parameters for this castle are false
            if (is_castling_flag_set(log->moves[log->actual_size-1]->castling_rights, Black_King_Moved_Flag) || is_castling_flag_set(log->moves[log->actual_size-1]->castling_rights, Black_Rook_A_Moved_Flag)){
                return false;
            }
            // check if the rook is at the right place
            if (!(bitboard_array[ROOK_BLACK] & (1ULL << 56))){
                return false;
            }
            // check if the squares between the king and the rook are empty
            // if a black piece is on the squares 59 or 58, the castle is not possible
            if (bitboard_array[BLACK_PIECES] & (1ULL << 59) || bitboard_array[BLACK_PIECES] & (1ULL << 58) || bitboard_array[BLACK_PIECES] & (1ULL << 57)){
                return false;
            }
            // if a white piece is on the squares 59 or 58, the castle is not possible
            // check if the squares between the king and the rook are not threatened, but the king need also not to be threatened
            if (is_case_threatened(BLACK, 60, bitboard_array, log)){
                return false;
            }
            if (is_case_threatened(BLACK, 59, bitboard_array, log)){
                return false;
            }
            if (is_case_threatened(BLACK, 58, bitboard_array, log)){
                return false;
            }
            // if all the conditions are met, the castle is possible
            return true;
        }

    }

    // default, if the castle is not possible
    return false;
}


bool is_promotion_possible(int color, bit_board* bitboard_array, int from, int to){
    
    // for the white player
    if (color == WHITE){
        // check if the pawn is at the last rank (we need to verify if it's really a pawn at the from index)
        if (get_rank(from) == 6 && get_rank(to) == 7 && (bitboard_array[PAWN_WHITE] & (1ULL << from))){
            return true;
        }
    }
    // for the black player
    else if (color == BLACK){
        // check if the pawn is at the last rank (we need to verify if it's really a pawn at the from index)
        if (get_rank(from) == 1 && get_rank(to) == 0 && (bitboard_array[PAWN_BLACK] & (1ULL << from))){
            return true;
        }
    }

    // default, if the promotion is not possible
    return false;
}


bool is_en_passant_possible(int color, bit_board* bitboard_array, int from, int to, Log* log){
    
    // check if the log is not empty
    if (log->actual_size == 0){
        return false;
    }

    // it need to be a pawn at the from index
    if (color == WHITE && !(bitboard_array[PAWN_WHITE] & (1ULL << from))){
        return false;
    }
    if (color == BLACK && !(bitboard_array[PAWN_BLACK] & (1ULL << from))){
        return false;
    }

    // for an en passant to be possible, the last move must be a pawn moving two squares
    if (get_flag(log->moves[log->actual_size-1]->move_value) == Pawn_Two_Up_Flag){

        // for the white player, the pawn must be at the right rank (the fifth, index 4)
        if (color == WHITE && get_rank(from) == 4 && get_rank(to) == 5){
            
            // if we go left to make the en passant, the previous to_index must be the left of this move from_index
            if (get_file(to) == get_file(from) - 1 && get_to_square(log->moves[log->actual_size-1]->move_value) == from - 1 && from - 1 >= 0){
                return true;
            }

            // if we go right to make the en passant
            else if (get_file(to) == get_file(from) + 1 && get_to_square(log->moves[log->actual_size-1]->move_value) == from + 1 && from + 1 < NUMBER_SQUARES){
                return true;
            }

        }
        
        // for the black player, the pawn must be at the right rank (the fourth, index 3)
        else if (color == BLACK && get_rank(from) == 3 && get_rank(to) == 2){
            
            // if we go left to make the en passant, the previous to_index must be the left of this move from_index
            if (get_file(to) == get_file(from) - 1 && get_to_square(log->moves[log->actual_size-1]->move_value) == from - 1 && from - 1 >= 0){
                return true;
            }

            // if we go right to make the en passant
            else if (get_file(to) == get_file(from) + 1 && get_to_square(log->moves[log->actual_size-1]->move_value) == from + 1 && from + 1 < NUMBER_SQUARES){
                return true;
            }

        }
    
    }

    // default, if the en passant is not possible
    return false;
}


bool has_pawn_moved_two_squares(int color, bit_board* bitboard_array, int from, int to){
    
    // for the white player
    if (color == WHITE && bitboard_array[PAWN_WHITE] & (1ULL << from)){
        // check if the pawn is at the right rank (the second, index 1)
        if (get_rank(from) == 1 && get_rank(to) == 3){
            return true;
        }
    }
    // for the black player
    else if (color == BLACK && bitboard_array[PAWN_BLACK] & (1ULL << from)){
        // check if the pawn is at the right rank (the seventh, index 6)
        if (get_rank(from) == 6 && get_rank(to) == 4){
            return true;
        }
    }

    // default, if the pawn has not moved two squares
    return false;

}


bool will_capture(int color, bit_board* bitboard_array, int to){

    // if the color is white, we search if the "to" position is occupied by a black piece
    if (color == WHITE){
        if (bitboard_array[BLACK_PIECES] & (1ULL << to)){
            return true;
        }
    }
    // if the color is black, we search if the "to" position is occupied by a white piece
    else if (color == BLACK){
        if (bitboard_array[WHITE_PIECES] & (1ULL << to)){
            return true;
        }
    }

    // if the "to" position is not occupied by a piece of the opposite color, we return false
    return false;

}


int get_type_of_piece(bit_board* bitboard_array, int position_index){

    for (int i = 0; i < NUMBER_OF_BIBOARD; i++){
        if (bitboard_array[i] & (1ULL << position_index) && i != WHITE_PIECES && i != BLACK_PIECES){
            return i;
        }
    }

    // if the position is empty, we return NOTHING
    return NOTHING;

}
