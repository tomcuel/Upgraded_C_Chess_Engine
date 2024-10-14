#ifndef __OPENINGS_H__
#define __OPENINGS_H__


#include "../Game_Treatment/Board.h"
#include "../Useful/Constants.h"
#include "../Game_Treatment/Log.h"
#include "../AI_Functions/Move_Generator.h"
#include "../Game_Treatment/Settings.h"


/////////////////////////////////////////////////////////////////////////////////////
// Openings summary
// This module is responsible for the generation and management of the opening book
/**
 * A summary of the supported functions is given below:
 * 
 * load_opening_book : Function to load the opening book of all the games, it created the opening book not with values but with move_value structures
 * copy_file_into_file : Function to copy a file into another file
 * get_move_in_opening_book_line_at_index : Function to get the move in the opening book at a certain index in a line
 * update_opening_book : Function to update the opening book after a move has been played from the opening book
 * is_move_in_move_array : Function to check if a move is in an array of moves
 * get_move_from_book : Function to get the move from the opening book
**/
/////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////
// Function to load the opening book of all the games, it created the opening book not with values but with move_value structures
/////////////////////////////////////////////////////////////////////////////////////
void load_opening_book();


/////////////////////////////////////////////////////////////////////////////////////
// Function to copy a file into another file
/**
 * @param copy_from : the file from which we copy
 * @param copy_into : the file into which we copy
**/
/////////////////////////////////////////////////////////////////////////////////////
void copy_file_into_file(const char* copy_from, const char* copy_into);


/////////////////////////////////////////////////////////////////////////////////////
// Function to get the move in the opening book at a certain index in a line
/**
 * @param index : the index of the move in the opening book
 * @param line : the line of the opening book
 * @return the move in the opening book at a certain index
**/
/////////////////////////////////////////////////////////////////////////////////////
move get_move_in_opening_book_line_at_index(int index, char* line);


/////////////////////////////////////////////////////////////////////////////////////
// Function to update the opening book considering the current game position
// will be used before and after a level 7 AI play, and well as in different buttons functions of the GUI
/////////////////////////////////////////////////////////////////////////////////////
void update_opening_book();


/////////////////////////////////////////////////////////////////////////////////////
// Function to check if a move is in an array of moves
/**
 * @param move_value : the move to check
 * @param moves_array : the array of moves
 * @param nb_moves : the number of moves in the array
 * @return true if the move is in the array, false otherwise
**/
/////////////////////////////////////////////////////////////////////////////////////
bool is_move_in_move_array(move move_value, move* moves_array, int nb_moves);


/////////////////////////////////////////////////////////////////////////////////////
// Function to get the move from the opening book
/**
 * @return the move from the opening book if it's in the book, else 0
**/
/////////////////////////////////////////////////////////////////////////////////////
move get_move_from_book();


#endif /* __OPENINGS_H__ */