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

## Folders 
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


## To run this project
In the root of the project folder : 
* do the command `make` to create all the .o and .x file
* do the command `make realclean` to clean all the .x and .o file everywhere in the project
* launch the game with `./Chess_Engine/Chess_Game.x`


## To play the game 

#### How to use the keyboard keys and the clicks on screen
* After launching it, you have to **click on the different texts or rectangle buttons** to perfom the task you want 
* They **are shortcuts** not to lose time waiting for the menus to work _(these are in the **Chess_Game.c** file at the **SDL_KEYDOWN** part during the main loop of the game)_
    * 
    *
    *
    *
* You need to click on the **start button** to be able **to launch the timer** and then play the game and your moves
* To move the piece, you need to **click and slide** the piece to their destination 
* There is a result at the end with a **victory menu** where you **still can undo the ending move** to change the game outcome
* You can see the **last 10 complete moves of the log** of the game _(Move like Nbd2 aren't represented here, only Nd2 will be shown, every thing else is the formal chess game log)_
* When playing against an AI, it will show the **search depth reached**, the **move made** _(evaluated as best)_ and the **evaluation** of the move _(the score or the fact that it was taken from the opening book)_

#### Gameplay choice menu
<img src="./Game_Exemples/Gameplay_Choice_Screenshot.png" alt="Gameplay_Choice_Screenshot" width="350" height="225"/>

#### Color choice menu
<img src="./Game_Exemples/Color_Choice_Screenshot.png" alt="Color_Choice_Screenshot" width="350" height="225"/>

#### AI difficulty choice menu
<img src="./Game_Exemples/AI_Choice_Screenshot.png" alt="AI_Choice_Screenshot" width="350" height="225"/>

#### Time choice menu
<img src="./Game_Exemples/Time_Choice_Screenshot.png" alt="Time_Choice_Screenshot" width="350" height="225"/>

#### Start of the game
<img src="./Game_Exemples/Start_Game_Screenshot.png" alt="Start_Game_Screenshot" width="350" height="225"/>

#### Opening Book used by AI
<img src="./Game_Exemples/Opening_Book_Move_Screenshot.png" alt="Opening_Book_Move_Screenshot" width="350" height="225"/>

#### In game screenshot
<img src="./Game_Exemples/In_Game_Screenshot.png" alt="In_Game_Screenshot" width="350" height="225"/>

#### Victory menu choice
<img src="./Game_Exemples/Victory_Menu_Screenshot.png" alt="Victory_Menu_Screenshot" width="350" height="225"/>

#### Undoing the victory menu
<img src="./Game_Exemples/Coming_Back_From_Victory_Menu_Screenshot.png" alt="Coming_Back_From_Victory_Menu_Screenshot" width="350" height="225"/>



## Concerning the tests
* everything has been test after its implementation to make sure it does what it was supposed to do


## Structure of each file

#### .h file
* will have the explications concerning the description of the function and what I will used for 
* will also give the parameters the function is taking 
* code structure : 

```c
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
```

#### .c file 
* will not include the header, but it will be commented to know what are the things done inside the different functions
* code structure : (spacing and commenting the code to make it easy to copy and to understand)

```c
#include "filename.h"


function_1


function_2


…
…


function_n
```
