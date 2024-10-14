#include "Openings.h"
#include <unistd.h>


void load_opening_book(){

/*
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current working directory: %s\n", cwd);
    } else {
        perror("getcwd() error");
    }
*/

    // Opening the file with all the 8 first openings in formal chess language
    // one thing here that isn't considered is to have two knights for example that goes to the same square, we need to add the rank or file from where it comes, but I don't do that and simply suppress the lines where it happens
    FILE* formal_file = fopen("Chess_Engine/AI_Data/Opening_in_Games.txt", "r");
    // Creating the opening book with the 8 first openings with move values 
    FILE* opening_book = fopen("Chess_Engine/AI_Data/Opening_Book_Init.txt", "w");

    // If the file doesn't exist, we need to stop the function
    if (formal_file == NULL) {
        printf("Error: Unable to open 'Openings_in_Games.txt'\n");
    }
    if (opening_book == NULL) {
        printf("Error: Unable to open 'Opening_Book_Init.txt'\n");
    }

    // If one of the files cannot be opened, return
    if (formal_file == NULL || opening_book == NULL) {
        if (formal_file != NULL) {
            fclose(formal_file);
        }
        if (opening_book != NULL) {
            fclose(opening_book);
        }
        return;
    }

    // reading the file with the openings in formal chess language
    bool is_file_empty = false;
    while (!is_file_empty) {
        // getting the openings moves
        char* opening_move = (char*)malloc(10*sizeof(char));
        // looking for malloc errors
        if (opening_move == NULL){
            printf("Error: memory allocation failed in load_opening_book\n");
            return;
        }
        char* opening_move_value = (char*)malloc(10*sizeof(char));
        // looking for malloc errors
        if (opening_move_value == NULL){
            printf("Error: memory allocation failed in load_opening_book\n");
            return;
        }
        for (int i = 0; i < NUMBER_OF_OPENING_MOVES; i++){
            fscanf(formal_file, "%s", opening_move);
            move move_value = 0;
            int from_square = 0;
            int to_square = 0;
            int flag = No_Flag;
            // an empty line and we break 
            if (strcmp(opening_move, "") == 0){
                is_file_empty = true;
                break;
            }
            // if the move is a castle
            if (strcmp(opening_move, "O-O") == 0){
                from_square = (game_settings->color_of_player_that_is_playing == WHITE) ? 4 : 60;
                to_square = (game_settings->color_of_player_that_is_playing == WHITE) ? 6 : 62;
                flag = Castle_Flag;
            }
            else if (strcmp(opening_move, "O-O-O") == 0){
                from_square = (game_settings->color_of_player_that_is_playing == WHITE) ? 4 : 60;
                to_square = (game_settings->color_of_player_that_is_playing == WHITE) ? 2 : 58;
                flag = Castle_Flag;
            }
            else {
                // there is no promotion in the opening book since 3/4 moves can't lead to a promotion (5 would have)
                
                // it's the index of the case square
                int index = 0;
                char from_file = 'a';
                bool is_there_a_file_for_the_piece = false;
                if (opening_move[0] == 'N' || opening_move[0] == 'B' || opening_move[0] == 'R' || opening_move[0] == 'Q' || opening_move[0] == 'K'){
                    index = 1;
                    // if there are a file that is specified for the piece, just need to take that into account, because if two pieces can move to the same square, we need to know from where it comes (ex : Nfc3)
                    if (opening_move[1] >= 'a' && opening_move[1] <= 'h' && opening_move[2] >= 'a' && opening_move[2] <= 'h'){
                        is_there_a_file_for_the_piece = true;
                        from_file = opening_move[1];
                        index = 2;
                    }
                }
                
                // if a capture is happening (ex : exd4 or Nfxd4)
                if (opening_move[1] == 'x' || opening_move[2] == 'x'){
                    index = 2; 
                    if (is_there_a_file_for_the_piece){
                        index = 3;
                    }
                }
                // getting the square to where the piece is moving
                to_square = get_index((int)(opening_move[index+1]-'1'), (int)(opening_move[index]-'a'));
                
                // now we need to get from where the piece moved
                // if the move is a knight move
                if (opening_move[0] == 'N'){
                    bit_board knight_mask = precomputed_knight_attacks[to_square];
                    while (knight_mask){
                        int temp_from_square = __builtin_ctzll(knight_mask);
                        if (bitboards[game_settings->color_of_player_that_is_playing == WHITE ? KNIGHT_WHITE : KNIGHT_BLACK] & (1ULL << temp_from_square)){
                            // if we're in the Nfc3 case, we need to check if the file is the good one, because two knights can move to the same square
                            if (is_there_a_file_for_the_piece){
                                if (get_file(temp_from_square) == (int)(from_file-'a')){
                                    from_square = temp_from_square;
                                    break;
                                }
                            }
                            // no Nfc3 case, so we do the basic stuff
                            else {
                                from_square = temp_from_square;
                                break;
                            }
                        }
                        knight_mask &= knight_mask - 1;
                    } 
                }
                // if the move is a bishop move
                else if (opening_move[0] == 'B'){
                    bit_board bishop_mask = calculate_bishop_attacks_with_blockers(to_square, bitboards[WHITE_PIECES] | bitboards[BLACK_PIECES]);
                    while (bishop_mask){
                        int temp_from_square = __builtin_ctzll(bishop_mask);
                        if (bitboards[game_settings->color_of_player_that_is_playing == WHITE ? BISHOP_WHITE : BISHOP_BLACK] & (1ULL << temp_from_square)){
                            // if we're in the Bfc3 case, we need to check if the file is the good one, that we don't select the wrong bishop (can happen after a pawn promotion, because bishop don't cover the same squares)
                            if (is_there_a_file_for_the_piece){
                                if (get_file(temp_from_square) == (int)(from_file-'a')){
                                    from_square = temp_from_square;
                                    break;
                                }
                            }
                            // no Bfc3 case, so we do the basic stuff
                            else {
                                from_square = temp_from_square;
                                break;
                            }
                        }
                        bishop_mask &= bishop_mask - 1;
                    }
                }
                // if the move is a rook move
                else if (opening_move[0] == 'R'){
                    bit_board rook_mask = calculate_rook_attacks_with_blockers(to_square, bitboards[WHITE_PIECES] | bitboards[BLACK_PIECES]);
                    while (rook_mask){
                        int temp_from_square = __builtin_ctzll(rook_mask);
                        if (bitboards[game_settings->color_of_player_that_is_playing == WHITE ? ROOK_WHITE : ROOK_BLACK] & (1ULL << temp_from_square)){
                            // if we're in the Rfc3 case, we need to check if the file is the good one, that we don't select the other rook possible
                            if (is_there_a_file_for_the_piece){
                                if (get_file(temp_from_square) == (int)(from_file-'a')){
                                    from_square = temp_from_square;
                                    break;
                                }
                            }
                            // no Rfc3 case, so we do the basic stuff
                            else {
                                from_square = temp_from_square;
                                break;
                            }
                        }
                        rook_mask &= rook_mask - 1;
                    }
                }
                // if the move is a queen move
                else if (opening_move[0] == 'Q'){
                    bit_board queen_mask = calculate_bishop_attacks_with_blockers(to_square, bitboards[WHITE_PIECES] | bitboards[BLACK_PIECES]) | calculate_rook_attacks_with_blockers(to_square, bitboards[WHITE_PIECES] | bitboards[BLACK_PIECES]);
                    while (queen_mask){
                        int temp_from_square = __builtin_ctzll(queen_mask);
                        if (bitboards[game_settings->color_of_player_that_is_playing == WHITE ? QUEEN_WHITE : QUEEN_BLACK] & (1ULL << temp_from_square)){
                            // if we're in the Qfc3 case, we need to check if the file is the good one (can happen after a pawn promotion), so we don't select the wrong queen
                            if (is_there_a_file_for_the_piece){
                                if (get_file(temp_from_square) == (int)(from_file-'a')){
                                    from_square = temp_from_square;
                                    break;
                                }
                            }
                            // no Qfc3 case, so we do the basic stuff
                            else {
                                from_square = temp_from_square;
                                break;
                            }
                        }
                        queen_mask &= queen_mask - 1;
                    }
                }
                // if the move is a king move
                else if (opening_move[0] == 'K'){
                    bit_board king_mask = precomputed_king_attacks[to_square];
                    while (king_mask){
                        int temp_from_square = __builtin_ctzll(king_mask);
                        if (bitboards[game_settings->color_of_player_that_is_playing == WHITE ? KING_WHITE : KING_BLACK] & (1ULL << temp_from_square)){
                            // only one king so no file problem
                            from_square = temp_from_square;
                            break;
                        }
                        king_mask &= king_mask - 1;
                    }
                    
                }
                // if the move is a pawn move
                else {
                    if (game_settings->color_of_player_that_is_playing == WHITE){
                        
                        // if there is a standard capture 
                        if (opening_move[1] == 'x'){
                            // if there is a capture on the left
                            if ((bitboards[PAWN_WHITE] & (1ULL << (to_square - 9))) && (bitboards[BLACK_PIECES] & (1ULL << to_square)) && get_file(to_square) != 0 && get_file(to_square-9) == (int)(opening_move[0]-'a')){
                                from_square = to_square - 9;
                            }
                            // if there is a capture on the right
                            else if ((bitboards[PAWN_WHITE] & (1ULL << (to_square - 7))) && (bitboards[BLACK_PIECES] & (1ULL << to_square)) && get_file(to_square) != 7 && get_file(to_square-7) == (int)(opening_move[0]-'a')){
                                from_square = to_square - 7;
                            }
                            // if there is a left en_passant possible 
                            else if (is_en_passant_possible(WHITE, bitboards, to_square-9, to_square, chess_log)){
                                from_square = to_square - 9;
                                flag = En_Passant_Flag;
                            }
                            // if there is a right en_passant possible 
                            else if (is_en_passant_possible(WHITE, bitboards, to_square-7, to_square, chess_log)){
                                from_square = to_square - 7;
                                flag = En_Passant_Flag;
                            }
                        }
                        // if there is a simple move
                        else if (bitboards[PAWN_WHITE] & (1ULL << (to_square - 8))){
                            from_square = to_square - 8;
                        }
                        // if there is a double move
                        else if ((bitboards[PAWN_WHITE] & (1ULL << (to_square - 16))) && get_rank(to_square) == 3){
                            from_square = to_square - 16;
                            flag = Pawn_Two_Up_Flag;
                        }

                    }
                    else if (game_settings->color_of_player_that_is_playing == BLACK){
                        
                        // if there is a standard capture
                        if (opening_move[1] == 'x'){
                            // if there is a capture on the left
                            if ((bitboards[PAWN_BLACK] & (1ULL << (to_square + 7))) && (bitboards[WHITE_PIECES] & (1ULL << to_square)) && get_file(to_square) != 0 && get_file(to_square+7) == (int)(opening_move[0]-'a')){
                                from_square = to_square + 7;
                            }
                            // if there is a capture on the right
                            else if ((bitboards[PAWN_BLACK] & (1ULL << (to_square + 9))) && (bitboards[WHITE_PIECES] & (1ULL << to_square)) && get_file(to_square) != 7 && get_file(to_square+9) == (int)(opening_move[0]-'a')){
                                from_square = to_square + 9;
                            }
                              // if there is a left en_passant possible 
                            else if (is_en_passant_possible(BLACK, bitboards, to_square+7, to_square, chess_log)){
                                from_square = to_square + 7;
                                flag = En_Passant_Flag;
                            }
                            // if there is a right en_passant possible 
                            else if (is_en_passant_possible(BLACK, bitboards, to_square+9, to_square, chess_log)){
                                from_square = to_square + 9;
                                flag = En_Passant_Flag;
                            }
                        }
                        // if there is a simple move
                        else if (bitboards[PAWN_BLACK] & (1ULL << (to_square + 8))){
                            from_square = to_square + 8;
                        }
                        // if there is a double move
                        else if ((bitboards[PAWN_BLACK] & (1ULL << (to_square + 16))) && get_rank(to_square) == 4){
                            from_square = to_square + 16;
                            flag = Pawn_Two_Up_Flag;
                        }

                    }
                }

            }

            move_value = get_move_value(from_square, to_square, flag);
            make_move_AI(move_value);
            sprintf(opening_move_value, "%d", move_value);
            fprintf(opening_book, "%s ", opening_move_value);

        }
        

        if (!is_file_empty){
            // undoing the moves made
            for (int i = 0; i < NUMBER_OF_OPENING_MOVES; i++){
                undo_last_move_AI();
            }
            // going to the next line of the opening book
            fprintf(opening_book, "\n");
        }
        free(opening_move);
        free(opening_move_value);
    }

    // closing the files
    fclose(formal_file);
    fclose(opening_book);

    // copying the opening book into the read file
    copy_file_into_file("Chess_Engine/AI_Data/Opening_Book_Init.txt", "Chess_Engine/AI_Data/Opening_Book_read.txt");

    // reset everything 
    reset_bitboards();
    reset_log();
    
}


void copy_file_into_file(const char* copy_from, const char* copy_into){
    
    char line[SIZE_LINE_OPENING_BOOK];
    // loading the data for the opening book write back into the opening book read
    FILE* file_to_copy_from = fopen(copy_from, "r");
    FILE* file_to_copy_into = fopen(copy_into, "w");
    // If the file doesn't exist, we need to stop the function
    if (file_to_copy_from == NULL) {
        printf("Error: Unable to open %s\n", copy_from);
    }
    if (file_to_copy_into == NULL) {
        printf("Error: Unable to open %s\n", copy_into);
    }
    while (fgets(line, sizeof(line), file_to_copy_from) != NULL){
        fprintf(file_to_copy_into, "%s", line);
    }
    // closing the files
    fclose(file_to_copy_from);
    fclose(file_to_copy_into);

}


move get_move_in_opening_book_line_at_index(int index, char* line){

    // Pointer to traverse the line
    const char* ptr = line; 
    // Track the search index
    int search_index = 0;  

    // Iterate through the line to find the value at the specified index
    while (*ptr != '\0') {
        int move_value;
        // Read the integer at the current position
        if (sscanf(ptr, "%d", &move_value) == 1) {
            // Return the value if we reached the specified index
            if (search_index == index) {
                return (move) move_value; 
            }
            // Increment the current index
            search_index++; 
        }
        
        // Move the pointer past the current integer
        while (*ptr != ' ' && *ptr != '\0') {
            ptr++;
        }
        // Skip the space
        if (*ptr == ' ') {
            ptr++;
        }
    }
    
    // If the index is out of bounds, return an error value
    return 0;  // Or handle it as appropriate

}


void update_opening_book(){

    // if we're too far in the game, we don't need to update the opening book
    if (chess_log->actual_size > NUMBER_OF_OPENING_MOVES){
        return;
    }

    // Open file for reading and writing
    FILE *file = fopen("Chess_Engine/AI_Data/Opening_Book_read.txt", "r+");  
    if (file == NULL) {
        perror("Error opening file");
        return ;
    }

    char line[SIZE_LINE_OPENING_BOOK];
    // To track where we are reading and writing from in the file
    long read_pos = 0;    
    long write_pos = 0;
    // Read each line, process it, and write back only valid lines
    while (fgets(line, sizeof(line), file) != NULL) {
        // Store current read position (after the fgets call)
        read_pos = ftell(file);  

        // looking if the line does for now match the game
        int i=0;
        while(get_move_in_opening_book_line_at_index(i, line) == chess_log->moves[i]->move_value && i<chess_log->actual_size){
            i++;
        }
        // skipping the line if it's not the same
        if (i != chess_log->actual_size){
            continue;
        }

        // Move to the write position
        fseek(file, write_pos, SEEK_SET);  // Move to the write position
        // Write the valid line back to the file
        fputs(line, file);
        // Update the write position to the end of the newly written line
        write_pos = ftell(file);
        // Return to the next read position to continue reading from the correct spot
        fseek(file, read_pos, SEEK_SET);
    }

    // Truncate the file to the correct length to remove leftover content
    ftruncate(fileno(file), write_pos);
    // closing the file
    fclose(file);

}


bool is_move_in_move_array(move move_value, move* moves_array, int nb_moves){

    for (int i = 0; i < nb_moves; i++){
        if (moves_array[i] == move_value){
            return true;
        }
    }
    return false;

}


move get_move_from_book(){

    // if we're too far in the game, we need to stop the search in the opening book, because we want to test the AI, not to replicate games
    if (chess_log->actual_size > NUMBER_OF_OPENING_MOVES){
        return 0;
    }

    // opening the read file
    FILE* opening_book_read = fopen("Chess_Engine/AI_Data/Opening_Book_read.txt", "r");
    // getting the line of the opening book
    char line[SIZE_LINE_OPENING_BOOK];
    int max_size = SIZE_LINE_OPENING_BOOK;
    move* moves__possibles_from_book = (move*)malloc(max_size*sizeof(move));
    // looking for malloc errors
    if (moves__possibles_from_book == NULL){
        printf("Error: memory allocation failed in get_move_from_book\n");
        return 0;
    }
    int nb_moves = 0;
    // going through the lines of the opening book
    while (fgets(line, sizeof(line), opening_book_read) != NULL){
        int i=0;
        while(get_move_in_opening_book_line_at_index(i, line) == chess_log->moves[i]->move_value && i<chess_log->actual_size){
            i++;
        }
        if (i == chess_log->actual_size){
            move move_possible = get_move_in_opening_book_line_at_index(chess_log->actual_size, line);
            if (!is_move_in_move_array(move_possible, moves__possibles_from_book, nb_moves)){
                moves__possibles_from_book[nb_moves] = move_possible;
                nb_moves++;
            }
        }
    }
    // closing the file
    fclose(opening_book_read);

    printf("nb_moves : %d\n", nb_moves);
    for (int i = 0; i < nb_moves; i++){
        printf("move %d : %d\n", i, moves__possibles_from_book[i]);
    }
    printf("\n");

    if (nb_moves == 0){
        return 0;
    }
    set_seed();
    return moves__possibles_from_book[random_int(0, nb_moves - 1)];

}
