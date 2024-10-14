#ifndef __PIECES_SQUARES_TABLES_H__
#define __PIECES_SQUARES_TABLES_H__


#include "../Useful/Constants.h"


///////////////////////////////////////////////////////////////////////////////////////
// Piece Square Tables (PST) summary
// This module is responsible for creating all the piece square tables that are used in the game, to give the preferencial positions of the different pieces (also depending on the game phase)
///////////////////////////////////////////////////////////////////////////////////////
extern const int whiteKnight_PST[BOARD_SIZE][BOARD_SIZE];
extern const int blackKnight_PST[BOARD_SIZE][BOARD_SIZE];
extern const int whiteBishop_PST[BOARD_SIZE][BOARD_SIZE];
extern const int blackBishop_PST[BOARD_SIZE][BOARD_SIZE];
extern const int whiteRook_PST[BOARD_SIZE][BOARD_SIZE];
extern const int blackRook_PST[BOARD_SIZE][BOARD_SIZE];
extern const int whiteQueen_PST[BOARD_SIZE][BOARD_SIZE];
extern const int blackQueen_PST[BOARD_SIZE][BOARD_SIZE];
extern const int whiteKing_PST[BOARD_SIZE][BOARD_SIZE];
extern const int whiteKing_PST_end[BOARD_SIZE][BOARD_SIZE];
extern const int blackKing_PST[BOARD_SIZE][BOARD_SIZE];
extern const int blackKing_PST_end[BOARD_SIZE][BOARD_SIZE];
extern const int whitePawn_PST[BOARD_SIZE][BOARD_SIZE];
extern const int whitePawn_PST_end[BOARD_SIZE][BOARD_SIZE];
extern const int blackPawn_PST[BOARD_SIZE][BOARD_SIZE];
extern const int blackPawn_PST_end[BOARD_SIZE][BOARD_SIZE];


#endif /* __PIECES_SQUARES_TABLES_H__ */