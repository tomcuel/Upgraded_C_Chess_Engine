#ifndef __MOVE_ORDERING_H__
#define __MOVE_ORDERING_H__


#include "../Game_Treatment/Board.h"
#include "../Useful/Constants.h"
#include "../Game_Treatment/Log.h"
#include "../Game_Treatment/Moves_Treatment.h"
#include "../Game_Treatment/Settings.h"
#include "../Useful/Utility.h"


/////////////////////////////////////////////////////////////////////////////////////
// Move_Ordering summary
// This part of the code is responsible for ordering the moves to improve the alpha-beta pruning, by ordering the moves that are most likely to be the best moves first.
/**
 * A summary of the supported function is given below:
 * 
 * order_moves : Function to order the moves
 * is_square_attacked_by_opponent_pawn : Function to check if a square is attacked by an opponent pawn
 * quick_sort : Function to sort the moves by their value
 * partition : Function that return the pivot index of the partition and sort the moves by their value in that part of the pivot
**/
/////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////
// Function to order the moves
/**
 * @param is_captures_only : if we want to order only the captures (less time consuming)
 * @param valid_moves : the valid moves to order
 * @param nb_moves : the number of valid moves
**/
/////////////////////////////////////////////////////////////////////////////////////
void order_moves(bool is_captures_only, move* valid_moves, int nb_moves);


/////////////////////////////////////////////////////////////////////////////////////
// Function to check if a square is attacked by an opponent pawn
/**
 * @param square : the square to check
**/
/////////////////////////////////////////////////////////////////////////////////////
bool is_square_attacked_by_opponent_pawn(int square);


/////////////////////////////////////////////////////////////////////////////////////
// Function to sort the moves by their value (quick sort in O(n log n))
/**
 * @param values : the values of the moves
 * @param valid_moves : the valid moves to order
 * @param nb_moves : the number of valid moves
**/
/////////////////////////////////////////////////////////////////////////////////////
void quick_sort(move* valid_moves, int* scores, int low, int high);


/////////////////////////////////////////////////////////////////////////////////////
// Function that return the pivot index of the partition and sort the moves by their value in that part of the pivot 
/////////////////////////////////////////////////////////////////////////////////////
int partition(move* valid_moves, int* scores, int low, int high);


#endif /* __MOVE_ORDERING_H__ */