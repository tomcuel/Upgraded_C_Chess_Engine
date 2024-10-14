#ifndef __TRANSPOSITION_TABLE_H__
#define __TRANSPOSITION_TABLE_H__


#include "../Useful/Constants.h"
#include "../Game_Treatment/Board.h"
#include "../Game_Treatment/Log.h"


/////////////////////////////////////////////////////////////////////////////////
// Transposition Table summary
// This module is responsible for creating the transposition table of the game, to store the different positions and their values to avoid recomputing them
/**
 * A summary of the supported functions is given below:
 * 
 * Two Structures are defined in this module:
 * TT_entry : Represents an element of the transposition table during the search
 * TT : Represents the transposition tables array
 * 
 * A summary of the supported functions is given below:
 * 
 * defining the different values for the zobrist hashing
 * defining the Transposition Tables
 * 
 * generate_random_uint64 : Function to generate a random 64-bit number
 * initialize_random_transposition_tables : Function to initialize the transposition tables
 * free_random_transposition_tables : Function to free the transposition tables
 * 
 * initialize_transposition_tables : Function
 * reset_transposition_tables : Function to reset the transposition
 * free_transposition_tables : Function to free the transposition tables
 * 
 * get_zobrist_key : Function to get the zobrist key of a position
 * get_index_zobrist_in_TT : Function to get the index of the zobrist key in the transposition tables
 * 
 * lookup_for_evaluation_in_TT : Function to lookup for an evaluation in the transposition tables (of if not found)
 * store_evaluation_in_TT : Function to store an evaluation in the transposition tables
 * get_stored_move_in_TT : Function to get the stored move in the transposition tables at a given index
**/
/////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////
// Structure to define an element of the transposition table during the search
/////////////////////////////////////////////////////////////////////////////////
typedef struct TT_entry {
    bit_board zobrist_key; // the zobrist key of the position (to be able to identify the position)
    int depth; // the depth we searched this position
    int value; // the value of the position
    int cut_flag; // the type of cut in the alpha-beta pruning has been made (EXACT, ALPHA_CUT, BETA_CUT)
    move move; // the move that is going to have this value, this cut, etc.
} TT_entry;


/////////////////////////////////////////////////////////////////////////////////
// Structure to define the transposition tables array 
/////////////////////////////////////////////////////////////////////////////////
typedef struct TT {
    TT_entry* entries; // the entries of the transposition table
    int size; // the size of the transposition table (in MB in entry)
} TT;


/////////////////////////////////////////////////////////////////////////////////////
// Declare the transposition tables and values for the zobrist hashing as extern so they can be accessed in other files
/////////////////////////////////////////////////////////////////////////////////////
extern bit_board** Generate_Random_Transposition_Tables;
extern bit_board side_to_move_white;
extern bit_board side_to_move_black;
extern bit_board* castling_rights_hash;
extern bit_board* en_passant_file_hash; // the file where the opposition pawn moved two squares for the en passant capture


/////////////////////////////////////////////////////////////////////////////////
// Declares the Transposition Tables as extern so they can be accessed in other files
/////////////////////////////////////////////////////////////////////////////////
extern TT* transposition_tables;


/////////////////////////////////////////////////////////////////////////////////
// Function to generate a random 64-bit number
/**
 * @return a random 64-bit number
**/
/////////////////////////////////////////////////////////////////////////////////
bit_board generate_random_uint64();


/////////////////////////////////////////////////////////////////////////////////////
// Function to initialize the transposition tables
/////////////////////////////////////////////////////////////////////////////////////
void initialize_random_transposition_tables();


/////////////////////////////////////////////////////////////////////////////////////
// Function to free the transposition tables
/////////////////////////////////////////////////////////////////////////////////////
void free_random_transposition_tables();


/////////////////////////////////////////////////////////////////////////////////////
// Function to initialize the transposition tables
/////////////////////////////////////////////////////////////////////////////////////
void initialize_transposition_tables(int MB_size);


/////////////////////////////////////////////////////////////////////////////////////
// Function to reset the transposition tables
/////////////////////////////////////////////////////////////////////////////////////
void reset_transposition_tables();


/////////////////////////////////////////////////////////////////////////////////////
// Function to free the transposition tables
/////////////////////////////////////////////////////////////////////////////////////
void free_transposition_tables();


/////////////////////////////////////////////////////////////////////////////////////
// Function to get the zobrist key of a position
/**
 * @return the zobrist key of the position
**/
/////////////////////////////////////////////////////////////////////////////////////
bit_board get_zobrist_key();


/////////////////////////////////////////////////////////////////////////////////////
// Function to get the index of the zobrist key in the transposition tables
/**
 * @param zobrist_key the zobrist key of the position
 * @return the index of the zobrist key in the transposition tables
**/
/////////////////////////////////////////////////////////////////////////////////////
int get_index_zobrist_in_TT(bit_board zobrist_key);


/////////////////////////////////////////////////////////////////////////////////////
// Function to lookup for an evaluation in the transposition tables (of if not found)
/**
 * @param index_in_TT the index of the
 * @param zobrist_key the zobrist key of the position
 * @param ply_remaining the remaining ply to search
 * @param ply_from_root the ply from the root
 * @param alpha the alpha value
 * @param beta the beta value
 * @return the value of the position if found, FAILED_LOOKUP otherwise
**/
/////////////////////////////////////////////////////////////////////////////////////
int lookup_for_evaluation_in_TT(int index_in_TT, bit_board zobrist_key, int ply_remaining, int ply_from_root, int alpha, int beta);


/////////////////////////////////////////////////////////////////////////////////////
// Function to store an evaluation in the transposition tables
/**
 * @param index_in_TT the index of the zobrist key in the transposition tables
 * @param zobrist_key the zobrist key of the position
 * @param ply_remaining the remaining ply to search
 * @param ply_from_root the ply from the root
 * @param value the value of the position
 * @param cut_flag the type of cut in the alpha-beta pruning has been made (EXACT, ALPHA_CUT, BETA_CUT)
 * @param best_move the best move to play
**/
/////////////////////////////////////////////////////////////////////////////////////
void store_evaluation_in_TT(int index_in_TT, bit_board zobrist_key, int ply_remaining, int value, int cut_flag, move best_move);


/////////////////////////////////////////////////////////////////////////////////////
// Function to get the stored move in the transposition tables at a given index
/**
 * @param index_in_TT the index of the zobrist key in the transposition tables
 * @return the move
**/
/////////////////////////////////////////////////////////////////////////////////////
move get_stored_move_in_TT(int index_in_TT);


#endif /* __TRANSPOSITION_TABLE_H__ */