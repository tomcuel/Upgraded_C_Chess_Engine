# Introduction 
Here is the continuation of the chess game programming project completed in class. It's an upgrade where everything related to the game has been changed.
The graphic interface has been modified. To make it faster and have a better AI, I'm using bitboards (64bits integer), it did change almost every function. I also added some keyboard shortcuts to easily proceed the tests.

download_log + show log : blc de regarder si on a deux cavaliers qui peuvent manger une pièce et donc on note la colonne ou le rang de celui qui attaque, dans les moves values c'est présent 
--> book opening avec ça 
--> book opening avec 12 openings de profondeur (18 déjà tester), des problèmes de chargement du fichier et de méthode de calculs des values des moves m'ont restreint, j'aurais du essayer de tout changer pour arriver à aller chercher plus loin sans qu'il n'y ai d'abération (toujours possible de jouer comme ça mais parfois ça va crasher ou faire n'importe quoi ce qui peut être frustrant)
le lancement va faire crasher sur la mémoire, de temps en temps sur l'ouverture de fichiers depuis l'ajout de l'openning book, sinon ça ne crashera pas normalement

# About SDL
Here's the website to find out more about this library (which allows us to make graphics and play on them, for example): 
- https://www.libsdl.org / https://wiki.libsdl.org/SDL2/FrontPage for everything, with installation setup or link to the code of the SDL 
- the wiki_lib is very useful to be able to easily search function, things that can be done and how to implement, it's making us gain time
- --> one way to do it is by searching from the type of category of functions that act on differents parts : https://wiki.libsdl.org/SDL2/APIByCategory
- --> the other way is by searching the name, but it requires to know well the library and what it can do : https://wiki.libsdl.org/SDL2/CategoryAPI
- I've succeeded this time to download the sdl_ttf and sdl_image extensions, thus the graphics were way easier to implement


# Concerning the tests
- everything has been test after its implementation to make sure it does what it was supposed to do


# To run this project : 
In the root of the project folder
- do the command "make" to create all the .o and .x file
- do the command "make realclean" to clean all the .x and .o file everywhere in the project
- launch the game with "./Chess_Engine/Chess_Game.x"


# To play the game 
- after launching it, you have to click on the different texts linked to the choices to make 
- they are shortcuts not to lose time waiting for the menus to work (these are in the Chess_Game.c file at the SDL_KEYDOWN part during the main loop of the game)
- you need to click on the start button to be able to move a piece and to launch the timer
- to move the piece, you need to click and slide the piece to their destination 
- it's better to use the "p" touch while playing a match against the AI, to avoid losing time and moves made of the AI to be made during this time, because we need the game to be on pause to undo moves (with "u" or with the in-game button)
- there is a result at the end with a victory menu where you still can undo the ending move to change the game outcome


# What has been implemented 

## what has been done : 
- Using Images and Sounds folder for the render and the chess sounds
- AI.c + Evaluation.c + Move_Ordering.c + Pieces_Squares_Tables.c + Pre_Computed_Data + Search.c + Transposition_Table.c : implementation of the AI part described later in this README
- Board.c : creating the bitboards, and the captured pieces and the score, as well as treating how the make_move and undo_function change the different structures for a human player
- Chess_Game.c : main function that launch the graphics part and treat the input of the user during the game, while managing the timer and the AI play 
- Constants.c : definition of the differents constants used 
- Download_log.c : functions that are related to download the game status in a file, and open a game depending on the file
- Graphics.c : show the game graphics depending on which we're in
- Log.c : creating the log of the game, whats happening after each move, and the log of the bitboards of the game
- Move_Generator.c : generating all the possible moves, the state of the game and the IA making and undoing moves function
- Settings.c : structure that represents the game settings
- Utility.c : creating all the useful functions that are used in the game but not part of the game

## limitations : 
- I haven't fully implemented the insufficient material rules, but in a simple and basic way
- the AI will only promote pawn to queen 
- opening and charging the game through the log will only make queens out of the promoted pawn
- the download_log function will erase the file "game_log.txt" and its data. To keep a game, you need to change the filename so it's not erased 
- the file to download the log isn't only the classic game log, since it would have required a lot more to extract the moves and set up the game 

# AI levels

## LVL1 :
- a random AI but that will eat pieces when it can maximising the score difference between the eaten piece and the one that take it 

## LVL2 :
- the first implementation of the Alpha_Beta_Pruning method (with a depth of 2 (modifiable)) with a simple evaluation function of the position, we also order the moves depending whether they are good or not, so the best move are searched earlier and it reduces the time of the search

## LVL3 :
- a second Alpha_Beta_Pruning algorithm (with a depth of 2 (modifiable), so it doesn't take too long) but with an extended search to consider only captures after we have searched at the demanded depth, so that we don't make a shocking move, there is no depth restriction for the quiescience_search

## LVL4 :
- this third occurence of the Alpha_Beta_Pruning algorithm with the extended search for the capture moves (still in depth 2 to be reactiv) focus on an amelioration of the evaluation function that include 
- - the count of the material
- - the piece square tables that give the preferencial position of the different pieces depending on the state of the game
- - the mop_up_score to put the opponent king in a corner or to push our king forward to face the oppenent king if we're in a positiv endgame situation 
- - an evaluation of the pawn to see if they are isolated, no threatened by any opponent pawn (passed pawns)
- - an evaluation of the pawn shield structure to protect the king using precomputed data, but also looking if a file is open for a queen to threaten the king that is shielded behind pawn after a castle (there are penalty point to encourage castle to be done)

## LVL5 :
- implementation of the iterative deepening : we search at depth 1, then 2, etc until we run out of time (it's currently setup at 5sec), with the same Alpha_Beta_Pruning algorithm as in the level 4

## LVL6 :
- transpositions tables are added to the code, so when a position of the board has always been evaluated (and stored), we can get it without having to calculate it again

## LVL7 :
- we have the same thing as the level 6 but now in the Alpha_Beta_Pruning algorithm we search at different depth depending if the move is ranked highly in the move ordering or if it's an important one that needs more investigation (depth extensions)


# Structure of the code

## .h file : 
- - will have the explications concerning the description of the function and what I will used for 
- - will also give the parameters the function is taking 
- - code structure : 

#ifndef __FILENAME_H__
#define __FILENAME_H__


#include <…>
…
…
#include <…>


/////////////////////////////////////////////////////////////////////////////////////
// Filename Summary : (+ Resume of this file)
/**
 * 
 … 
 Resume of the different functions we can find on this file
 …
 *
**/
/////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////
// Description of what the function is doing 
/**
 * @param parameter1 - description of parameter_1
 * @param parameter1 - description of parameter_2
 * …
 * …
 * @param parameter1 - description of parameter_n
**/ 
/////////////////////////////////////////////////////////////////////////////////////
header of the function 


…
make other function
…


/////////////////////////////////////////////////////////////////////////////////////
// Description of what the function is doing 
/**
 * @param parameter1 - description of parameter_1
 * @param parameter1 - description of parameter_2
 * …
 * …
 * @param parameter1 - description of parameter_n
**/ 
/////////////////////////////////////////////////////////////////////////////////////
header of the function 


#endif /* __FILENAME_H__ */


## .c file  : 
- - will not include the header, but it will be commented to know what are the things done inside the different functions
- - code structure : (spacing the code to make it easy to copy and to understand)

#include "filename.h"


function_1


function_2


…
…


function_n
