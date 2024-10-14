#include "Transposition_Table.h"


bit_board** Generate_Random_Transposition_Tables;
bit_board side_to_move_white;
bit_board side_to_move_black;
bit_board* castling_rights_hash;
bit_board* en_passant_file_hash; // the file where the opposition pawn moved two squares for the en passant capture
TT* transposition_tables;


bit_board generate_random_uint64() {
    
    // Generate two 32-bit random numbers
    bit_board high = (bit_board)rand();
    bit_board low = (bit_board)rand();

    // Combine the two to make a 64-bit random number
    return (high << 32) | low;

}


void initialize_random_transposition_tables(){
    
    // Allocate memory for the tables
    Generate_Random_Transposition_Tables = (bit_board**)malloc(NUMBER_SQUARES * sizeof(bit_board*));
    // looking for malloc errors
    if (Generate_Random_Transposition_Tables == NULL) {
        printf("Error: malloc failed in initialize_transposition_tables\n");
        exit(1);
    }
    for (int i = 0; i < NUMBER_SQUARES; i++){
        Generate_Random_Transposition_Tables[i] = (bit_board*)malloc(12 * sizeof(bit_board));
        // looking for malloc errors
        if (Generate_Random_Transposition_Tables[i] == NULL) {
            printf("Error: malloc failed in initialize_transposition_tables\n");
            exit(1);
        }
    }
    for (int i = 0; i < NUMBER_SQUARES; i++){
        for (int j = 0; j < 12; j++){
            Generate_Random_Transposition_Tables[i][j] = generate_random_uint64();
        }
    }

    // Generate random numbers for the side to move
    side_to_move_white = generate_random_uint64();
    side_to_move_black = generate_random_uint64();
    

    // Generate random numbers for the castling rights
    castling_rights_hash = (bit_board*)malloc(64 * sizeof(bit_board));
    // looking for malloc errors    
    if (castling_rights_hash == NULL) {
        printf("Error: malloc failed in initialize_transposition_tables\n");
        exit(1);
    }
    for (int i = 0; i < 64; i++){
        castling_rights_hash[i] = generate_random_uint64();
    }

    // Generate random numbers for the en passant square
    en_passant_file_hash = (bit_board*)malloc(BOARD_SIZE * sizeof(bit_board));
    // looking for malloc errors
    if (en_passant_file_hash == NULL) {
        printf("Error: malloc failed in initialize_transposition_tables\n");
        exit(1);
    }
    for (int i = 0; i < BOARD_SIZE; i++){
        en_passant_file_hash[i] = generate_random_uint64();
    }

}


void free_random_transposition_tables(){
    
    for (int i = 0; i < NUMBER_SQUARES; i++){
        free(Generate_Random_Transposition_Tables[i]);
    }
    free(Generate_Random_Transposition_Tables);
    free(castling_rights_hash);
    free(en_passant_file_hash);

}


void initialize_transposition_tables(int MB_size){

    int TT_Entry_bytes_size = sizeof(TT_entry); // Get the size of the Entry structure
    int desired_table_size_in_bytes = MB_size * 1024 * 1024 * 24; // Convert size in MB to bytes (24bytes for each entry)
    int number_entries = desired_table_size_in_bytes / TT_Entry_bytes_size; // Calculate number of entries
    // Allocate memory for the transposition tables
    transposition_tables = (TT*)malloc(sizeof(TT));
    // looking for malloc errors
    if (transposition_tables == NULL) {
        printf("Error: malloc failed in initialize_transposition_tables\n");
        exit(1);
    }
    transposition_tables->size = number_entries;
    transposition_tables->entries = (TT_entry*)malloc(sizeof(TT_entry) * number_entries);
    // looking for malloc errors
    if (transposition_tables->entries == NULL) {
        printf("Error: malloc failed in initialize_transposition_tables\n");
        exit(1);
    }

    // Initialize the entries 
    for (int i = 0; i < number_entries; i++){
        transposition_tables->entries[i].zobrist_key = 0;
        transposition_tables->entries[i].depth = 0;
        transposition_tables->entries[i].value = 0;
        transposition_tables->entries[i].cut_flag = 0;
        transposition_tables->entries[i].move = 0;
    }

}


void reset_transposition_tables(){
    
    for (int i = 0; i < transposition_tables->size; i++){
        transposition_tables->entries[i].zobrist_key = 0;
        transposition_tables->entries[i].depth = 0;
        transposition_tables->entries[i].value = 0;
        transposition_tables->entries[i].cut_flag = 0;
        transposition_tables->entries[i].move = 0;
    }

}


void free_transposition_tables(){
    
    if (transposition_tables == NULL){
        return;
    }
    free(transposition_tables->entries);
    free(transposition_tables);

}


bit_board get_zobrist_key(){

    // the zobrist key
    bit_board zobrist_key = 0;

    // hashing the different values to get the zobrist key
    for (int i = 0; i < NUMBER_SQUARES; i++){
        int piece_type = get_type_of_piece(bitboards, i);
        if (piece_type != NOTHING){
            zobrist_key ^= Generate_Random_Transposition_Tables[i][piece_type];
        }
    }

    // hashing concerning the color that is to play
    if (game_settings->color_of_player_that_is_playing == WHITE){
        zobrist_key ^= side_to_move_white;
    }
    else {
        zobrist_key ^= side_to_move_black;
    }

    // hashing concerning the castling rights
    zobrist_key ^= castling_rights_hash[chess_log->moves[chess_log->actual_size-1]->castling_rights];

    // hashing concerning the en passant square
    move previous_move = chess_log->moves[chess_log->actual_size-1]->move_value;
    if (get_flag(previous_move) == Pawn_Two_Up_Flag){
        zobrist_key ^= en_passant_file_hash[get_file(get_to_square(previous_move))];
    }

    // returning the zobrist key
    return zobrist_key;

}


int get_index_zobrist_in_TT(bit_board zobrist_key){
    
    return (zobrist_key % transposition_tables->size);

}


int lookup_for_evaluation_in_TT(int index_in_TT, bit_board zobrist_key, int ply_remaining, int ply_from_root, int alpha, int beta){

    // Get the entry corresponding to the index
    TT_entry entry = transposition_tables->entries[index_in_TT];

    if (entry.zobrist_key == zobrist_key && zobrist_key != 0 && entry.value != 0){
        if (entry.depth >= ply_remaining){
            if (entry.cut_flag == EXACT){
                return entry.value;
            }
            else if (entry.cut_flag == ALPHA_CUT && entry.value <= alpha){
                return alpha;
            }
            else if (entry.cut_flag == BETA_CUT && entry.value >= beta){
                return beta;
            }
        }
    }

    // if no valid entry 
    return FAILED_LOOKUP;    

}


void store_evaluation_in_TT(int index_in_TT, bit_board zobrist_key, int ply_remaining, int value, int cut_flag, move best_move){

    // we must continue to store this information only if the depth is greater than the one already, so that we don't overwrite a better evaluation
    if (transposition_tables->entries[index_in_TT].depth <= ply_remaining){
        // updating the infos in the corresponding entry
        transposition_tables->entries[index_in_TT].zobrist_key = zobrist_key;
        transposition_tables->entries[index_in_TT].depth = ply_remaining;
        transposition_tables->entries[index_in_TT].value = value;
        transposition_tables->entries[index_in_TT].cut_flag = cut_flag;
        transposition_tables->entries[index_in_TT].move = best_move;
    }
    
}


move get_stored_move_in_TT(int index_in_TT){

    return transposition_tables->entries[index_in_TT].move;

}