#ifndef __PRE_COMPUTED_DATA_H__
#define __PRE_COMPUTED_DATA_H__


#include "../Useful/Constants.h"
#include "../Useful/Utility.h"


///////////////////////////////////////////////////////////////////////////////////////
// Pre-computed data summary
// This module is responsible for creating all the pre-computed data that are used in the game, without having to recompute them each time
/**
 * A summary of the supported functions is given below:
 * 
 * defining the distance tables
 * initialize_distance_tables: Function to initialize the distance tables pre-computed data
 * free_distance_tables: Function to free the distance tables pre-computed data
 * 
 * defining the pawn shield squares
 * initialize_precomputed_evaluation_data: Function to initialize the pawn shield squares pre-computed data, that goes through all the squares
 * free_precomputed_evaluation_data: Function to free the pawn shield squares pre-computed data
 * create_pawn_shield_square: Function to create the pawn shield square for a given square index
 * is_valid_square_for_shield: Function to check if a square is valid for a pawn shield (not on the first or last rank)
 * add_if_valid_shield: Function to add a square to the pawn shield square list if it is valid (increment the size)
 * 
 * initialize_pre_computed_data: Function to initialize all the pre-computed data
 * free_pre_computed_data: Function to free all the pre-computed data
**/
///////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////
// Declare the distance tables as extern so they can be accessed in other files
/////////////////////////////////////////////////////////////////////////////////////
extern int** Orthogonal_Distance;
extern int* Centre_Manhattan_Distance;


/////////////////////////////////////////////////////////////////////////////////////
// Function to initialize the distance tables pre-computed data
/////////////////////////////////////////////////////////////////////////////////////
void initialize_distance_tables();


/////////////////////////////////////////////////////////////////////////////////////
// Function to free the distance tables pre-computed data
/////////////////////////////////////////////////////////////////////////////////////
void free_distance_tables();


/////////////////////////////////////////////////////////////////////////////////////
// Arrays to store the pawn shield squares linked to each position of the king for each color
/////////////////////////////////////////////////////////////////////////////////////
extern int** Pawn_Shield_Squares_White;
extern int** Pawn_Shield_Squares_Black;


/////////////////////////////////////////////////////////////////////////////////////
// Function to initialize the pawn shield squares pre-computed data, that goes through all the squares
/////////////////////////////////////////////////////////////////////////////////////
void initialize_precomputed_evaluation_data();


/////////////////////////////////////////////////////////////////////////////////////
// Function to free the pawn shield squares pre-computed data
/////////////////////////////////////////////////////////////////////////////////////
void free_precomputed_evaluation_data();


/////////////////////////////////////////////////////////////////////////////////////
// Function to create the pawn shield square for a given square index
/**
 * @param square_index: The index of the square for which we want to create the pawn shield square
**/
/////////////////////////////////////////////////////////////////////////////////////
void create_pawn_shield_square(int square_index);


/////////////////////////////////////////////////////////////////////////////////////
// Function to check if a square is valid for a pawn shield (not on the first or last rank)
/**
 * @param file: The file of the square
 * @param rank: The rank of the square
 * @param color: The color of the king for which we want to create the pawn shield square
 * @return: True if the square is valid for a pawn shield, false otherwise
**/
/////////////////////////////////////////////////////////////////////////////////////
bool is_valid_square_for_shield(int file, int rank, int color);


/////////////////////////////////////////////////////////////////////////////////////
// Function to add a square to the pawn shield square list if it is valid (increment the size)
/**
 * @param file: The file of the square
 * @param rank: The rank of the square
 * @param color: The color of the king for which we want to create the pawn shield square
 * @param list: The list of pawn shield squares
 * @param size: The size of the list
**/
/////////////////////////////////////////////////////////////////////////////////////
void add_if_valid_shield(int file, int rank, int color, int* list, int* size);


/////////////////////////////////////////////////////////////////////////////////////
// Function to initialize all the pre-computed data
/////////////////////////////////////////////////////////////////////////////////////
void initialize_pre_computed_data();


/////////////////////////////////////////////////////////////////////////////////////
// Function to free all the pre-computed data
/////////////////////////////////////////////////////////////////////////////////////
void free_pre_computed_data();


#endif /* __PRE_COMPUTED_DATA_H__ */