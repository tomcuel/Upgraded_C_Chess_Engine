#include "Log.h"


Log* chess_log;
Bitboards_Log* bitboards_log;


void create_log(){
    
    chess_log = (Log*)malloc(sizeof(Log));
    // looking for malloc errors
    if (chess_log == NULL){
        printf("Error: memory allocation failed in Create_Log\n");
        return;
    }
    
    // setting the default values for the sizes and if the castles have been done
    chess_log->actual_size = 0;
    chess_log->max_size = max_size_log_array;

    // allocating the memory for the Log_Element
    chess_log->moves = (Log_Element**)malloc(sizeof(Log_Element*)*max_size_log_array);
    // looking for malloc errors
    if (chess_log->moves == NULL){
        printf("Error: memory allocation failed in Create_Log\n");
        return;
    }
    for (int i = 0; i < max_size_log_array; i++){
        chess_log->moves[i] = (Log_Element*)malloc(sizeof(Log_Element));
        // looking for malloc errors
        if (chess_log->moves[i] == NULL){
            printf("Error: memory allocation failed in Create_Log\n");
            return;
        }
        chess_log->moves[i]->move_value = 0;
        chess_log->moves[i]->captured_piece_type = NOTHING;
        chess_log->moves[i]->castling_rights = All_Castling_Rights;
    }

}


Log* create_a_copy_of_log(Log* log){

    Log* log_copy = (Log*)malloc(sizeof(Log));
    // looking for malloc errors
    if (log_copy == NULL){
        printf("Error: memory allocation failed in Create_Log\n");
        return NULL;
    }

    // copying the values
    log_copy->actual_size = log->actual_size;
    log_copy->max_size = log->max_size;

    // allocating the memory for the Log_Element
    log_copy->moves = (Log_Element**)malloc(sizeof(Log_Element*)*log->max_size);
    // looking for malloc errors
    if (log_copy->moves == NULL){
        printf("Error: memory allocation failed in Create_Log\n");
        return NULL;
    }
    for (int i = 0; i < log->max_size; i++){
        log_copy->moves[i] = (Log_Element*)malloc(sizeof(Log_Element));
        // looking for malloc errors
        if (log_copy->moves[i] == NULL){
            printf("Error: memory allocation failed in Create_Log\n");
            return NULL;
        }
        log_copy->moves[i]->move_value = log->moves[i]->move_value;
        log_copy->moves[i]->captured_piece_type = log->moves[i]->captured_piece_type;
        log_copy->moves[i]->castling_rights = log->moves[i]->castling_rights;
    }

    // returning the copy of the log
    return log_copy;

}


void reset_log(){

    // resetting the values
    chess_log->actual_size = 0;
    for (int i = 0; i < chess_log->max_size; i++){
        chess_log->moves[i]->move_value = 0;
        chess_log->moves[i]->captured_piece_type = NOTHING;
        chess_log->moves[i]->castling_rights = All_Castling_Rights;
    }

}


void destroy_log(){
    
    // looking for malloc errors
    if (chess_log != NULL){
        // freeing the memory
        for (int i = 0; i < chess_log->max_size; i++){
            // looking for malloc errors
            if (chess_log->moves[i] != NULL){
                free(chess_log->moves[i]);
            }
        }
        free(chess_log->moves);
        free(chess_log);
    }

}


void remove_last_move_from_log(){

    // we don't need to free the memory of the last element, we just need to decrease the actual size
    chess_log->actual_size--;

}


void create_bitboards_log(){
    
    bitboards_log = (Bitboards_Log*)malloc(sizeof(Bitboards_Log));
    // looking for malloc errors
    if (bitboards_log == NULL){
        printf("Error: memory allocation failed in Create_Log\n");
        return;
    }
    
    // setting the default values for the sizes and if the castles have been done
    bitboards_log->actual_size = 0;
    bitboards_log->max_size = max_size_log_array;

    // allocating the memory for the array of bitboards
    bitboards_log->bitboards = (bit_board**)malloc(sizeof(bit_board*)*max_size_log_array);
    // looking for malloc errors
    if (bitboards_log->bitboards == NULL){
        printf("Error: memory allocation failed in Create_Log\n");
        return;
    }
    for (int i = 0; i < max_size_log_array; i++){
        bitboards_log->bitboards[i] = (bit_board*)malloc(sizeof(bit_board)*NUMBER_OF_BIBOARD);
        // looking for malloc errors
        if (bitboards_log->bitboards[i] == NULL){
            printf("Error: memory allocation failed in Create_Log\n");
            return;
        }
    }

}


void destroy_bitboards_log(){
    
    // looking for malloc errors
    if (bitboards_log != NULL){
        // freeing the memory
        for (int i = 0; i < bitboards_log->max_size; i++){
            // looking for malloc errors
            if (bitboards_log->bitboards[i] != NULL){
                free(bitboards_log->bitboards[i]);
            }
        }
        free(bitboards_log->bitboards);
        free(bitboards_log);
    }

}


void reset_bitboards_log(){

    // resetting the values
    bitboards_log->actual_size = 0;

}


void add_bitboards_to_log(bit_board* bitboards){
    
    // if the log is full, we need to free the memory of the first element and make a shift
    if (bitboards_log->actual_size == bitboards_log->max_size){
        printf("Error: the log is full in Add_Move_to_Log\n");
        return;
    }
    // looking for malloc errors
    if (bitboards_log == NULL){
        printf("Error: log or move_element is NULL in Add_Move_to_Log\n");
        return;
    }

    // copying the bitboards
    for (int i = 0; i < NUMBER_OF_BIBOARD; i++){
        bitboards_log->bitboards[bitboards_log->actual_size][i] = bitboards[i];
    }
    // incrementing the actual size
    bitboards_log->actual_size++;

}


void remove_last_bitboards_from_log(){
    
    // we don't need to free the memory of the last element, we just need to decrease the actual size
    bitboards_log->actual_size--;

}
