#include "Pre_Computed_Data.h"


// Define the tables
int** Orthogonal_Distance;
int* Centre_Manhattan_Distance;


void initialize_distance_tables() {

    // Allocate memory for the tables
    Orthogonal_Distance = (int**)malloc(NUMBER_SQUARES * sizeof(int*));
    Centre_Manhattan_Distance = (int*)malloc(NUMBER_SQUARES * sizeof(int));
    // looking for malloc errors
    if (Orthogonal_Distance == NULL || Centre_Manhattan_Distance == NULL) {
        printf("Error: malloc failed in initialize_distance_tables\n");
        exit(1);
    }
    for (int i = 0; i < NUMBER_SQUARES; i++) {
        Orthogonal_Distance[i] = (int*)malloc(NUMBER_SQUARES * sizeof(int));
        // looking for malloc errors
        if (Orthogonal_Distance[i] == NULL) {
            printf("Error: malloc failed in initialize_distance_tables\n");
            exit(1);
        }
    }

    for (int squareA = 0; squareA < NUMBER_SQUARES; squareA++) {
        
        // Manhattan distance from the centre of the board
        int file_distance_from_centre = max(3 - get_file(squareA), get_file(squareA) - 4);
        int rank_distance_from_centre = max(3 - get_rank(squareA), get_rank(squareA) - 4);
        Centre_Manhattan_Distance[squareA] = file_distance_from_centre + rank_distance_from_centre;

        for (int squareB = 0; squareB < NUMBER_SQUARES; squareB++) {
            // Orthogonal distance between two squares
            int file_distance = abs(get_file(squareA) - get_file(squareB));
            int rank_distance = abs(get_rank(squareA) - get_rank(squareB));
            Orthogonal_Distance[squareA][squareB] = file_distance + rank_distance;
        }
    }

}


void free_distance_tables() {
    
    for (int i = 0; i < NUMBER_SQUARES; i++) {
        free(Orthogonal_Distance[i]);
    }
    free(Orthogonal_Distance);
    free(Centre_Manhattan_Distance);

}


// Arrays to store the pawn shield squares
int** Pawn_Shield_Squares_White;
int** Pawn_Shield_Squares_Black;


void initialize_precomputed_evaluation_data() {

    // Allocate memory for the tables
    Pawn_Shield_Squares_White = (int**)malloc(NUMBER_SQUARES * sizeof(int*));
    Pawn_Shield_Squares_Black = (int**)malloc(NUMBER_SQUARES * sizeof(int*));
    // looking for malloc errors
    if (Pawn_Shield_Squares_White == NULL || Pawn_Shield_Squares_Black == NULL) {
        printf("Error: malloc failed in initialize_precomputed_evaluation_data\n");
        exit(1);
    }
    for (int i = 0; i < NUMBER_SQUARES; i++) {
        Pawn_Shield_Squares_White[i] = (int*)malloc(6 * sizeof(int));
        Pawn_Shield_Squares_Black[i] = (int*)malloc(6 * sizeof(int));
        // looking for malloc errors
        if (Pawn_Shield_Squares_White[i] == NULL || Pawn_Shield_Squares_Black[i] == NULL) {
            printf("Error: malloc failed in initialize_precomputed_evaluation_data\n");
            exit(1);
        }
    }
    
    // doing the same thing for all the squares
    for (int square_index = 0; square_index < NUMBER_SQUARES; square_index++) {
        create_pawn_shield_square(square_index);
    }

}


void free_precomputed_evaluation_data() {
    
    for (int i = 0; i < NUMBER_SQUARES; i++) {
        free(Pawn_Shield_Squares_White[i]);
        free(Pawn_Shield_Squares_Black[i]);
    }
    free(Pawn_Shield_Squares_White);
    free(Pawn_Shield_Squares_Black);

}


void create_pawn_shield_square(int square_index) {
    
    // initialize the arrays of shield squares (malloc to save memory)
    int* shield_white_indices = (int*)malloc(6 * sizeof(int));
    // looking for malloc errors
    if (shield_white_indices == NULL) {
        printf("Error: malloc failed in create_pawn_shield_square\n");
        exit(1);
    }
    int* shield_black_indices = (int*)malloc(6 * sizeof(int));
    // looking for malloc errors
    if (shield_black_indices == NULL) {
        printf("Error: malloc failed in create_pawn_shield_square\n");
        exit(1);
    }
    // initialize the arrays
    for (int i = 0; i < 6; i++) {
        shield_white_indices[i] = -1;
        shield_black_indices[i] = -1;
    }
    // initialize the size of the arrays
    int white_size = 0;
    int black_size = 0;

    // get the rank and file of the square and clamp the file to be between 1 and 6 because of the offset we will introduce after
    int rank = get_rank(square_index);
    int file = int_clamp(get_file(square_index), 1, 6);

    // add the shield squares for the pawns
    // first shield squares, just one rank away
    for (int file_offset = -1; file_offset <= 1; file_offset++) {
        add_if_valid_shield(file + file_offset, rank + 1, WHITE, shield_white_indices, &white_size);
        add_if_valid_shield(file + file_offset, rank - 1, BLACK, shield_black_indices, &black_size);
    }
    // second shield squares, two ranks away
    for (int file_offset = -1; file_offset <= 1; file_offset++) {
        add_if_valid_shield(file + file_offset, rank + 2, WHITE, shield_white_indices, &white_size);
        add_if_valid_shield(file + file_offset, rank - 2, BLACK, shield_black_indices, &black_size);
    }

    // copy the shield squares to the pre-computed data
    for (int i = 0; i < 6; i++) {
        Pawn_Shield_Squares_White[square_index][i] = shield_white_indices[i];
        Pawn_Shield_Squares_Black[square_index][i] = shield_black_indices[i];
    }

    // free the memory
    free(shield_white_indices);
    free(shield_black_indices);

}


bool is_valid_square_for_shield(int file, int rank, int color) {
    
    // there is no shield for the pawns on the first and last ranks for both colors
    int rank_to_check = (color == WHITE) ? 7 : 0;
    // look if the square is on the board
    return file >= 0 && file < 8 && rank >= 0 && rank < 8 && rank != rank_to_check;

}


void add_if_valid_shield(int file, int rank, int color, int* list, int* size) {
    
    // check if the square is valid, then add it to the list and increment the size
    if (is_valid_square_for_shield(file, rank, color)) {
        list[*size] = file + rank * 8;
        (*size)++;
    }

}


void initialize_pre_computed_data() {
    
    initialize_distance_tables();
    initialize_precomputed_evaluation_data();

}


void free_pre_computed_data() {
    
    free_distance_tables();
    free_precomputed_evaluation_data();
    
}
