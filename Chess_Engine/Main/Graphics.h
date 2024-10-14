#ifndef __GRAPHICS_H__
#define __GRAPHICS_H__


#include "SDL2/SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"


#include "../Game_Treatment/Board.h"
#include "../Useful/Constants.h"
#include "../Game_Treatment/Log.h"
#include "../AI_Functions/Move_Generator.h"
#include "../Game_Treatment/Moves_Treatment.h"
#include "../Game_Treatment/Settings.h"
#include "../Useful/Utility.h"


/////////////////////////////////////////////////////////////////////////////////////
// Graphics summary 
// This part of the code is used to show the game graphics depending on which we're in
/**
 * Button is a structure that represents the buttons (the area to click on and the activity state) in the game
 * 
 * A summary of the supported functions is given below:
 * 
 * create_buttons : Function to create the array of buttons and initialize them also, since no special initialization needs to be done
 * reset_buttons_state : Function to reset the buttons state to UNACTIVE
 * destroy_buttons : Function to destroy the array of buttons
 * 
 * show_load_menu : to show the menu rendering (depending on which menu we are)
 * show_chess_board : Function to show the chess board
 * show_trajectory : Function to draw the possible place where a piece can go to
 * show_captured_pieces : Function to show the captured pieces of the players
 * show_score : Function to show the score of the game next to the captured pieces on the winning side
 * show_updated_timer : to show the timer, remaining for each player
 * add_move_in_log_render : to add a move on the render log part of the screen
 * show_log : to show the log of the moves
 * show_move_AI_values : Function to add the move in the AI values part of the screen
 * show_AI_values : to show the AI values (the selected move, the score, if the move is taken from the book, the depth reached)
 * show_menu_button_in_game : to show the menu / parameters button during the game
 * show_confirmation_menu : to show the confirmation menu (only if a buttons is clicked)
 * show_victory_menu : to show the victory menu
**/
/////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////
// Button is a structure that represents the buttons (the area to click on and the activity state) in the game
/////////////////////////////////////////////////////////////////////////////////////
typedef struct Button{
    SDL_Rect rect; // the rectangle of the button
    int state; // the state of the button : UNACTIVE or ACTIVE
    // the type will be given by the position in the enum of buttons
    // for example Buttons[5] correspond to the button "NEXT_BUTTON_GAME_CHOICE" since in the enum NEXT_BUTTON_GAME_CHOICE=5
} Button;


/////////////////////////////////////////////////////////////////////////////////////
// Declares the buttons as extern so they can be accessed in other files
/////////////////////////////////////////////////////////////////////////////////////
extern Button** buttons;


/////////////////////////////////////////////////////////////////////////////////////
// Function to create the array of buttons and initialize them also, since no special initialization needs to be done 
/////////////////////////////////////////////////////////////////////////////////////
void create_buttons();


/////////////////////////////////////////////////////////////////////////////////////
// Function to reset the buttons state to UNACTIVE
/////////////////////////////////////////////////////////////////////////////////////
void reset_buttons_state();


/////////////////////////////////////////////////////////////////////////////////////
// Function to destroy the array of buttons
/////////////////////////////////////////////////////////////////////////////////////
void destroy_buttons();


/////////////////////////////////////////////////////////////////////////////////////
// Function to show the menu rendering (clearing it and showing it)
// not all the buttons will be shown, only the ones that are needed, depending on the menu_type and if the button is used for a menu or for the game
// the state in the button will be used to show the button in a different color if it is active or not (we have different pictures)
/**
 * @param renderer : the renderer to show the menu
 * @param menu_type : the menu_type to show : GAMEMPLAY_CHOICE, DIFFICULTY_CHOICE, TIME_CHOICE
 * @param is_clicked : to know if a click has already been made
 * @param draw_red_boundary_move : the red boundary to draw around a piece when it's selected to make a move
**/
/////////////////////////////////////////////////////////////////////////////////////
void show_load_menu(SDL_Renderer* renderer, int menu_type, bool is_clicked, SDL_Rect draw_red_boundary_move);


/////////////////////////////////////////////////////////////////////////////////////
// Function to show the chess board
/**
 * @param renderer : the renderer to show the chess board
 * @param is_clicked : to know if a click has already been made
 * @param draw_red_boundary_move : the red boundary to draw around a piece when it's selected to make a move (it can and will also be useful for the in game buttons)
 * @param selected_piece_index : the index of the selected piece
 * @param piece_movement_rect : the rectangle of the piece movement
**/
/////////////////////////////////////////////////////////////////////////////////////
void show_chess_board(SDL_Renderer *renderer, bool is_clicked, SDL_Rect draw_red_boundary_move, int selected_piece_index, SDL_Rect piece_movement_rect);


/////////////////////////////////////////////////////////////////////////////////////
// Function to draw the possible place where a piece can go to 
/**
 * @param renderer : the renderer to show the trajectory
 * @param is_clicked : to know if a click has already been made
 * @param is_click_on_board : if the board is clicked
 * @param selected_piece_index : the index of the selected piece
**/
/////////////////////////////////////////////////////////////////////////////////////
void show_trajectory(SDL_Renderer* renderer, bool is_cliked, bool is_click_on_board, int selected_piece_index);


/////////////////////////////////////////////////////////////////////////////////////
// Function to show the captured pieces of the players
// One for the player 1 and one for the player 2, on the top of the screen for the white captured pieces and on the bottom for the black captured pieces
/**
 * @param renderer : the renderer to show the captured pieces
**/
/////////////////////////////////////////////////////////////////////////////////////
void show_captured_pieces(SDL_Renderer* renderer);


/////////////////////////////////////////////////////////////////////////////////////
// Function to show the score of the game next to the captured pieces on the winning side
/**
 * @param renderer : the renderer to show the score
**/
/////////////////////////////////////////////////////////////////////////////////////
void show_score(SDL_Renderer* renderer);


/////////////////////////////////////////////////////////////////////////////////////
// Function to show the timer, remaining for each player
// It will not be inplemented in the first version of the game, but it will be implemented in the second version
// Since we don't have ttf, it might need time to do it (either by showing it pixel by pixel or by using the terminal)
/**
 * @param renderer : the renderer to show the timer
**/
/////////////////////////////////////////////////////////////////////////////////////
void show_updated_timer(SDL_Renderer* renderer);


/////////////////////////////////////////////////////////////////////////////////////
// Function to add a move on the render log part of the screen 
/**
 * @param renderer : the renderer to show the log
 * @param log_index : the index of the log to show
 * @param color_playing : the color of the move
 * @param font_size : the font size of the text
 * @param sdl_color : the color of the text
 * @param middle_x : the middle x of the screen
 * @param middle_y : the middle y of the screen
**/
/////////////////////////////////////////////////////////////////////////////////////
void add_move_in_log_render(SDL_Renderer* renderer, int log_index, int color_playing, int font_size, SDL_Color sdl_color, int middle_x, int middle_y);


/////////////////////////////////////////////////////////////////////////////////////
// Function to show the log of the moves
/**
 * @param renderer : the renderer to show the log
**/
/////////////////////////////////////////////////////////////////////////////////////
void show_log(SDL_Renderer* renderer);


/////////////////////////////////////////////////////////////////////////////////////
// Function to add the move in the AI values part of the screen
/**
 * @param renderer : the renderer to show the AI values
 * @param log_index : the index of the log to show the move from 
 * @param font_size : the font size of the text
 * @param sdl_color : the color of the text
 * @param middle_x : the middle x of the screen
 * @param middle_y : the middle y of the screen
**/
/////////////////////////////////////////////////////////////////////////////////////
void add_move_AI_values(SDL_Renderer* renderer, int log_index, int font_size, SDL_Color sdl_color, int middle_x, int middle_y);


/////////////////////////////////////////////////////////////////////////////////////
// Function to show the AI values (the selected move, the score, if the move is taken from the book, the depth reached)
/**
 * @param renderer : the renderer to show the AI values
 * @param selected_move_lvl7 : the selected move
 * @param selected_score_lvl7 : the score of the selected move
 * @param is_move_taken_from_book_lvl7 : to know if the move is taken from the book
 * @param depth_reached_lvl7 : the depth reached
**/
/////////////////////////////////////////////////////////////////////////////////////
void show_AI_values(SDL_Renderer* renderer, move selected_move_lvl7, int selected_score_lvl7, bool is_move_taken_from_book_lvl7, int depth_reached_lvl7);


/////////////////////////////////////////////////////////////////////////////////////
// Function to show the menu / parameters button during the game 
/**
 * @param renderer : the renderer to show the menu button
**/
/////////////////////////////////////////////////////////////////////////////////////
void show_menu_button_in_game(SDL_Renderer* renderer);


/////////////////////////////////////////////////////////////////////////////////////
// Function to show the confirmation menu (only if a buttons is clicked)
/**
 * @param renderer : the renderer to show the confirmation menu
**/
/////////////////////////////////////////////////////////////////////////////////////
void show_confirmation_menu(SDL_Renderer* renderer);


/////////////////////////////////////////////////////////////////////////////////////
// Function to show the victory menu
/**
 * @param renderer : the renderer to show the victory menu
 * @param is_clicked : to know if a click has already been made
 * @param draw_red_boundary_move : the red boundary to draw around a piece when it's selected to make a move
**/
/////////////////////////////////////////////////////////////////////////////////////
void show_victory_menu(SDL_Renderer* renderer, bool is_clicked, SDL_Rect draw_red_boundary_move);


#endif /* __GRAPHICS_H__ */