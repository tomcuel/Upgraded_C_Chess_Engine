#ifndef __DOWNLOAD_LOG_H__
#define __DOWNLOAD_LOG_H__


#include "../Game_Treatment/Board.h"
#include "../Useful/Constants.h"
#include "../Game_Treatment/Log.h"
#include "../AI_Functions/Move_Generator.h"
#include "../Game_Treatment/Moves_Treatment.h"
#include "../AI_Data/Openings.h"


/////////////////////////////////////////////////////////////////////////////////////
// Download Log summary
// This part of the code assemble all the functions that are related to download the game status in a file, and open a game depending on the file
/**
 * A summary of the supported function is given below:
 * 
 * download_log : Function to download the log and the game settings in a file
 * open_file_and_setup_chess_game : Function to open the file and update the chessboard to the state of the log and the game settings
**/
/////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////
// Function to download the log and the game settings in a file
/**
 * save in a file named "game_log.txt"
**/
/////////////////////////////////////////////////////////////////////////////////////
void download_log();


/////////////////////////////////////////////////////////////////////////////////////
// Function to open the file and update the chessboard to the state of the log and the game settings
/**
 * @param has_opened : boolean to know if the file has been opened
 * open the file named "game_log.txt"
**/
/////////////////////////////////////////////////////////////////////////////////////
void open_file_and_setup_chess_game(bool* has_opened);


#endif /* __DOWNLOAD_LOG_H__ */