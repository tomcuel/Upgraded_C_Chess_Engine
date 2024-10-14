#ifndef __EVALUATION_H___
#define __EVALUATION_H___


#include "../Game_Treatment/Board.h"
#include "../Useful/Constants.h"
#include "../Game_Treatment/Settings.h"
#include "../AI_Data/Transposition_Table.h"
#include "../AI_Data/Pieces_Squares_Tables.h"
#include "../AI_Data/Pre_Computed_Data.h"
#include "../Useful/Utility.h"


/////////////////////////////////////////////////////////////////////////////////////
// Evaluation summary
// This part of the code assemble all the functions that are related to the evaluation of the position, as an heuristic used in our search of tree of possibilities
/** 
 * A summary of the supported function is given below:
 * 
 * evaluate_position_lvl2_lvl3 : Function to evaluate the position of the pieces on the board, simple and easy for the lvl2 (alpha-beta pruning) and lvl3 (alpha-beta pruning with quiescence search)
 * 
 * some arrays to define penalties and bonuses for the different pieces
 * piece_square_tables_evaluation : Function that the score of the piece_square_tables, scoring the positional preferences of the pieces
 * get_pawn_positions : Function to retrieve all indices of set bits in a 64-bit bitboard, returns the indexes of the pawns
 * get_adjacent_file_mask : Function to get the mask of the adjacent files, as described in the get pawn mask function
 * get_pawn_mask : Function to get the mask of the pawns, to see if they are isolated, doubled, blocked, etc.
 * evaluate_pawns : Function that evaluates the positioning of the pawns for a certain color
 * mop_up_score : Function to evaluate depending if the oppenent is in the endgame if we need to push the friendly king to the opponent king
 * king_pawn_shield_score : Function to evaluate the king pawn shield score (look at the opening for queens or rooks to see if the king is safe)
 * evaluate : Function to evaluate the position of the pieces on the board (including material, piece square tables, pawns, mop up, king pawn shield)
**/
/////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////
// Function to evaluate the position of the pieces on the board, simple and easy for the lvl2 (alpha-beta pruning) and lvl3 (alpha-beta pruning with quiescence search)
// it doesn't include the turn of the player, that is to play
/**
 * @return the score of the position
**/
/////////////////////////////////////////////////////////////////////////////////////
int evaluate_position_lvl2_lvl3();


/////////////////////////////////////////////////////////////////////////////////////
// Function that the score of the piece_square_tables, scoring the positional preferences of the pieces
/**
 * @param endgame_white_transition : the endgame score for the white player
 * @param endgame_black_transition : the endgame score for the black player
 * @param white_piece_square_tables_score : the score of the white piece_square_tables (a pointer to the score, incremented by the function)
 * @param black_piece_square_tables_score : the score of the black piece_square_tables (a pointer to the score, incremented by the function)
**/
/////////////////////////////////////////////////////////////////////////////////////
void piece_square_tables_evaluation(float endgame_white_transition, float endgame_black_transition, int* white_piece_square_tables_score, int* black_piece_square_tables_score);


/////////////////////////////////////////////////////////////////////////////////////
// Function to retrieve all indices of set bits in a 64-bit bitboard, returns the indexes of the pawns
/**
 * @param pawn_bitboard : the bitboard to get the indexes of the pawns
 * @param nb_pawns : the number of pawns
 * @return the indexes of the pawns in a tab, or NULL if there is an error
**/
/////////////////////////////////////////////////////////////////////////////////////
int* get_pawn_positions(bit_board pawn_bitboard, int nb_pawns);


/////////////////////////////////////////////////////////////////////////////////////
// Function to get the mask of the adjacent files, as described in the get pawn mask function
/**
 * @param file_index : the index of the file
 * @return the mask of the adjacent files
**/
/////////////////////////////////////////////////////////////////////////////////////
bit_board get_adjacent_file_mask(int file_index);


/////////////////////////////////////////////////////////////////////////////////////
// Function to get the mask of the pawns, to see if they are isolated, doubled, blocked, etc.
// it's a bitboards with only 1 is the squares the pawn can move, squares up and the two left and right files (if not on the edge)
/**
 * @param pawn_position : the position of the pawn
 * @param pawn_bitboard : the bitboard of the pawn
 * @param color : the color of the pawn
 * @return the mask of the pawn
**/
/////////////////////////////////////////////////////////////////////////////////////
bit_board get_pawn_mask(int pawn_position, bit_board pawn_bitboard, int color);


/////////////////////////////////////////////////////////////////////////////////////
// Function that evaluates the positioning of the pawns for a certain color
// It mainly consists of the evaluation of the pawn structure, to see if the pawns are isolated, doubled, blocked, etc.
// here we're only doing the passed pawn and the isolated pawn (blocked is difficukt to evaluate, and double might have need to much calculation)
/**
 * @param color : the color of the pawns to evaluate
 * @param friendly_pawn_bitboard : the friendly pawn bitboard
 * @param opponent_pawn_bitboard : the opponent pawn bitboard
 * @return the score of the pawns for the color
**/
/////////////////////////////////////////////////////////////////////////////////////
int evaluate_pawns(int color, int nb_pawns, bit_board friendly_pawn_bitboard, bit_board opponent_pawn_bitboard);


/////////////////////////////////////////////////////////////////////////////////////
// Function to evaluate depending if the oppenent is in the endgame if we need to push the friendly king to the opponent king
/**
 * @param color : the color of the player
 * @param friendly_material : the material of the player
 * @param opponent_material : the material of the opponent
 * @param opponent_endgame_transition : the endgame transition of the opponent
 * @return the score of the mop up
**/
/////////////////////////////////////////////////////////////////////////////////////
int mop_up_score(int color, int friendly_material, int opponent_material, float opponent_endgame_transition);


/////////////////////////////////////////////////////////////////////////////////////
// Function to evaluate the king pawn shield score (look at the opening for queens or rooks to see if the king is safe)
/**
 * @param color : the color of the player
 * @param opponent_material : the material of the opponent
 * @param opponent_endgame_transition : the endgame transition of the opponent
 * @param nb_opponent_queens : the number of opponent queens
 * @param nb_opponent_rooks : the number of opponent rooks
 * @param opponent_PST_score : the score of the opponent piece square tables
 * @return the score of the king pawn shield
**/
/////////////////////////////////////////////////////////////////////////////////////
int king_pawn_shield_score(int color, int opponent_material, float opponent_endgame_transition, int nb_opponent_queens, int nb_opponent_rooks, int opponent_PST_score);


/////////////////////////////////////////////////////////////////////////////////////
// Function to evaluate the position of the pieces on the board (including material, piece square tables, pawns, mop up, king pawn shield)
/**
 * @return the score of the position
**/
/////////////////////////////////////////////////////////////////////////////////////
int evaluate();


#endif /* __EVALUATION_H__ */