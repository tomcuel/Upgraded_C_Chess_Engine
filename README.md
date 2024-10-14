# Chess Engine in C 
> Here is the continuation of the chess game programming project. It's an upgrade compared to the previous chess engine where lany things related to the game has been changed.
The graphic interface has been modified a bit. To make it faster and have a better AI, I changed a lot of the way to calculate things. The AI also uses an opening book. I also added some keyboard shortcuts to easily proceed the tests.

#### Tables of contents
* [Folders](#folders)  
* [About SDL](#about-SDL)  
* [Concerning the tests](#concerning-the-tests)
* [To run this project](#to-run-this-project)
* [To play the game](#to-play-the-game)
* [Structure of each file](#structure-of-each-file)

## Folders : 
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


## About SDL
Here's the website to find out more about this library (which allows us to make graphics and play on them, for example): 
* [SDL website](https://www.libsdl.org) / [SDL library](https://wiki.libsdl.org/SDL2/FrontPage) for everything, with installation setup or link to the code of the SDL 
* the wiki_lib is very useful to be able to easily search function, things that can be done and how to implement, to gain time by searching : 
1. The type of category of functions that act on differents parts ([Search by Category](https://wiki.libsdl.org/SDL2/APIByCategory))
2. The name of the function , but it requires to know well the library and what it can do ([Search by Name](https://wiki.libsdl.org/SDL2/CategoryAPI))
* I've succeeded this time to download the sdl_ttf and sdl_image extensions, thus the graphics were way easier to implement


## Concerning the tests
* everything has been test after its implementation to make sure it does what it was supposed to do


## To run this project : 
In the root of the project folder
* do the command **make** to create all the .o and .x file
* do the command **make realclean** to clean all the .x and .o file everywhere in the project
* launch the game with **./Chess_Engine/Chess_Game.x**


## To play the game 
- after launching it, you have to click on the different texts linked to the choices to make 
- they are shortcuts not to lose time waiting for the menus to work (these are in the Chess_Game.c file at the SDL_KEYDOWN part during the main loop of the game)
- you need to click on the start button to be able to move a piece and to launch the timer
- to move the piece, you need to click and slide the piece to their destination 
- it's better to use the "p" touch while playing a match against the AI, to avoid losing time and moves made of the AI to be made during this time, because we need the game to be on pause to undo moves (with "u" or with the in-game button)
- there is a result at the end with a victory menu where you still can undo the ending move to change the game outcome



## Structure of each file : 

### .h file : 
- - will have the explications concerning the description of the function and what I will used for 
- - will also give the parameters the function is taking 
- - code structure : 

```C
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


#endif /* __FILENAME_H__ */```


### .c file : 
- - will not include the header, but it will be commented to know what are the things done inside the different functions
- - code structure : (spacing the code to make it easy to copy and to understand)

```C
#include "filename.h"


function_1


function_2


…
…


function_n```
