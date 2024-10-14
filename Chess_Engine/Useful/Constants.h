#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__


#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h> 


/////////////////////////////////////////////////////////////////////////////////////
// Constants for the window graphics
/////////////////////////////////////////////////////////////////////////////////////
#define WINDOW_WIDTH 1400 // total width of the window
#define WINDOW_LEFT_MARGIN 50 // marge on the left of the chessboard
#define WINDOW_RIGHT_MARGIN 450 // marge on the right of the chessboard to print things 
#define WINDOW_HEIGHT 900 // height of the window
#define WINDOW_TOP_MARGIN 50 // marge on the top of the chessboard
#define WINDOW_BOTTOM_MARGIN 50 // marge on the bottom of the chessboard
#define SQUARE_SIZE 100 // size of a square on the chessboard
#define WINDOW_BOARD_SIZE 800 // size of the chessboard in the window
#define BOARD_SIZE 8 // size of the chessboard (8x8)
#define NUMBER_SQUARES 64 // number of squares on the chessboard
#define OUTSIDE_BOARD -200 // value to represent a square outside the board (to avoid to print moving pieces on the board when we don't want to)


/////////////////////////////////////////////////////////////////////////////////////
// Game Settings
/////////////////////////////////////////////////////////////////////////////////////
// Enum that represents the different menus screens
enum {GAMEPLAY_CHOICE, COLOR_CHOICE, DIFFICULTY_CHOICE, DIFFICULTY_CHOICE_WHITE_AI, DIFFICULTY_CHOICE_BLACK_AI, TIME_CHOICE, CHESSBOARD_RENDER, VICTORY_MENU}; 
// Defining if a player is an AI or not
enum {HUMAN, AI};
// Defining the game mode
enum {PLAYER_VS_PLAYER, PLAYER_VS_AI, AI_VS_AI};
// Defining the difficulty of the AI 
enum {NONE, LVL1, LVL2, LVL3, LVL4, LVL5, LVL6, LVL7, LVL8};
// Defining the time mode of the game
enum {SHORT_BLITZ, LONG_BLITZ, SHORT, MODERATE, LONG};
// Defining which player is loosing
enum {White_Player, Black_Player, Undetermined, Draw_by_stalemate, Draw_by_3_rules, Draw_by_50_rules, Draw_by_insufficient_material};


/////////////////////////////////////////////////////////////////////////////////////
// Memory related constants
/////////////////////////////////////////////////////////////////////////////////////
// Define the size of the log array
#define max_size_log_array 250 // 250 moves maximum should be well enough for a game (could be raised if needed), we can cut more the log if we want to save memory
// Define the size of the valid moves array
#define max_size_valid_moves_array 100
#define max_size_valid_moves_array_extended 218
// 1024 (16x64) moves maximum should the maximum number of moves possible in a game for a color without obstacles and rules
// 218 is the theoretical maximum number of moves possible in a game for a color
// 100 is most of the time a number of moves never reached in a game for a color, so it should be enough and fast things up
// we can allocate more memory if needed with the 218 if we encouter this situation, or one with more than 100 moves


/////////////////////////////////////////////////////////////////////////////////////
// Bitboards related constants
/////////////////////////////////////////////////////////////////////////////////////
// Enum that represents the type of the pieces (to be able to go through the bitboard array)
#define NUMBER_OF_BIBOARD 14
#define number_of_pieces_bitboards_per_color 6
#define number_of_bitboards_per_color 7
// Define the number of piece of each color that can be captured for each color
#define NUMBER_OF_PIECES_TAKENABLE_PER_COLOR 15
// Enum that represents the two colors of the pieces 
enum {WHITE, BLACK, NO_COLOR};
enum {
    PAWN_WHITE /* 0 */,
    KNIGHT_WHITE /* 1 */, 
    BISHOP_WHITE, /* 2 */
    ROOK_WHITE, /* 3 */
    QUEEN_WHITE, /* 4 */
    KING_WHITE, /* 5 */
    WHITE_PIECES, /* 6 */
    PAWN_BLACK, /* 7 */
    KNIGHT_BLACK, /* 8 */
    BISHOP_BLACK, /* 9 */
    ROOK_BLACK, /* 10 */
    QUEEN_BLACK, /* 11 */
    KING_BLACK, /* 12 */
    BLACK_PIECES, /* 13 */
    NOTHING /* 14 */
};
// Define what a board is (a 64bit integer)
typedef uint64_t bit_board;
// Define what a move is (a 16bit integer) -> bits 0-5 : start square, bits 6-11 : target square, bits 12-15 : flags
typedef uint16_t move;
// Define what a castling rights is (a 8bit integer) -> bit 0 : white king moved, bit 1 : white rook A moved, bit 2 : white rook H moved, bit 3 : black king moved, bit 4 : black rook A moved, bit 5 : black rook H moved
typedef uint8_t castling_rights_flags;
// Enum that represents the check state 
enum {NO_CHECK, CHECK, WHITE_CHECK, BLACK_CHECK, CHECK_MATE, NO_DRAW, STALEMATE, DRAW_BY_3_RULES, DRAW_BY_50_RULES, DRAW_BY_INSUFFICIENT_MATERIAL};


/////////////////////////////////////////////////////////////////////////////////////
// Flags and masks constants
/////////////////////////////////////////////////////////////////////////////////////
// Masks (declaration but no initialization)
#define start_square_mask 0b0000000000111111
#define target_square_mask 0b0000111111000000
#define flag_mask 0b1111000000000000
#define File_A_mask 0x0101010101010101ULL
#define File_H_mask 0x8080808080808080ULL
#define Rank_1_mask 0x00000000000000FFULL
#define Rank_8_mask 0xFF00000000000000ULL
#define Full_Bitboard_mask 0xFFFFFFFFFFFFFFFFULL
#define Empty_Bitboard_mask 0x0000000000000000ULL
// Flags (declaration but no initialization)
#define No_Flag 0b0000
#define En_Passant_Flag 0b0001
#define Castle_Flag 0b0010
#define Pawn_Two_Up_Flag 0b0011
#define Promote_To_Queen_Flag 0b0100
#define Promote_To_Knight_Flag 0b0101
#define Promote_To_Rook_Flag 0b0110
#define Promote_To_Bishop_Flag 0b0111
// Castling rights flags (declaration but no initialization)
#define All_Castling_Rights 0b000000
#define White_King_Moved_Flag 0b000001
#define White_Rook_A_Moved_Flag 0b000010
#define White_Rook_H_Moved_Flag 0b000100
#define Black_King_Moved_Flag 0b001000
#define Black_Rook_A_Moved_Flag 0b010000
#define Black_Rook_H_Moved_Flag 0b100000


/////////////////////////////////////////////////////////////////////////////////////
// Constants for the AI related part
/////////////////////////////////////////////////////////////////////////////////////
// Constants to define the value of each piece
#define PAWN_VALUE 100
#define KNIGHT_VALUE 300
#define BISHOP_VALUE 320
#define ROOK_VALUE 500
#define QUEEN_VALUE 900
#define KING_VALUE 1200
// Constants to define the maximum score of the IA (or the minimum score of the IA depending on the case)(for easier levels)
#define MAX_IA_SCORE 100000
// Constants to define the max score of the AI for the more advanced levels
#define IMMEDIATE_MATE_SCORE 100000
#define POSITIVE_INFINITY 9999999
#define NEGATIVE_INFINITY -9999999
// Constants to define the flags linked to the type of cut in the alpha-beta pruning has been made (for the transposition tables)
enum{EXACT, ALPHA_CUT, BETA_CUT};
// Constant to define the value for a failed lookup in the transposition tables
#define FAILED_LOOKUP -1
// Constants to define the maximum number of extensions for the depth of the search of the IA
#define MAX_NUMBER_OF_EXTENSIONS 16
// Constants to define the maximum depth in the iterative deepening search
#define MAX_DEPTH_ITERATIVE_DEEPENING 100
// Constants to define the number of pre computed moves for the opening book (10 means 5 complete moves) (can be changed to have more or less opening moves)
#define NUMBER_OF_OPENING_MOVES 12
// define the size of the line to read the opening book
#define SIZE_LINE_OPENING_BOOK 100

/////////////////////////////////////////////////////////////////////////////////////
// Enum that represents the type the name of the different buttons in the menu, next to the chessboard
// there are 21 buttons in total, there will do an array of buttons to get their state
/////////////////////////////////////////////////////////////////////////////////////
#define NUMBER_OF_BUTTONS 55
enum {
    // during gameplay choice 
    PLAYER_VS_PLAYER_BUTTON,
    PLAYER_VS_AI_BUTTON, 
    AI_VS_AI_BUTTON,
    OPEN_GAME_LOG_BUTTON,

    QUIT_BUTTON_GAME_CHOICE,
    NEXT_BUTTON_GAME_CHOICE,
    NOT_NEXT_BUTTON_GAME_CHOICE,

    // during the choices concerning the color we want to have to play against the AI
    BLACK_COLOR_BUTTON,
    WHITE_COLOR_BUTTON,

    QUIT_BUTTON_COLOR_CHOICE,
    MAIN_MENU_BUTTON_COLOR_CHOICE,
    BACK_BUTTON_COLOR_CHOICE,
    NEXT_BUTTON_COLOR_CHOICE,
    NOT_NEXT_BUTTON_COLOR_CHOICE,
    
    // choosing the difficulty of the AI
    LVL1_DIFFICULTY_BUTTON,
    LVL2_DIFFICULTY_BUTTON,
    LVL4_DIFFICULTY_BUTTON,
    LVL7_DIFFICULTY_BUTTON,

    QUIT_BUTTON_AI_CHOICE,
    MAIN_MENU_BUTTON_AI_CHOICE,
    BACK_BUTTON_AI_CHOICE,
    NEXT_BUTTON_AI_CHOICE,
    NOT_NEXT_BUTTON_AI_CHOICE,

    // choosing the time mode menu
    SHORT_BLITZ_BUTTON,
    LONG_BLITZ_BUTTON,
    SHORT_BUTTON,
    MODERATE_BUTTON,
    LONG_BUTTON,

    QUIT_BUTTON_TIME_CHOICE,
    MAIN_MENU_BUTTON_TIME_CHOICE,
    BACK_BUTTON_TIME_CHOICE,
    LOAD_BUTTON, 
    NOT_LOAD_BUTTON,

    // in game buttons
    START_BUTTON_IN_GAME, 
    RESTART_BUTTON_IN_GAME,
    NEW_GAME_BUTTON_IN_GAME,
    QUIT_BUTTON_IN_GAME,
    UNDO_BUTTON_IN_GAME,
    PAUSE_BUTTON,
    QUEEN_BUTTON,
    ROOK_BUTTON,
    BISHOP_BUTTON,
    KNIGHT_BUTTON,
    PAWN_PROMOTION_BUTTON,
    DL_LOG_IN_GAME_BUTTON,
    NEXT_BUTTON_IN_GAME,
    NOT_NEXT_BUTTON_IN_GAME,

    // in the victory menu
    NEW_GAME_BUTTON_VICTORY_MENU,
    RESTART_BUTTON_VICTORY_MENU,
    PAUSE_BUTTON_VICTORY_MENU,
    QUIT_BUTTON_VICTORY_MENU, 
    UNDO_ENDING_MOVE_BUTTON,
    DL_LOG_VICTORY_MENU_BUTTON, 
    NEXT_BUTTON_VICTORY_MENU,
    NOT_NEXT_BUTTON_VICTORY_MENU
};
// Enum that represents the state of each buttons 
// UNACTIVE : the button is not active, it's not been clicked
// ACTIVE : the button is active, it's been clicked
enum {UNACTIVE, ACTIVE};


#endif /* __CONSTANTS_H__ */