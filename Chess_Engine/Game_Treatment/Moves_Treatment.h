#ifndef __MOVES_TREATMENT_H__
#define __MOVES_TREATMENT_H__


#include "../Useful/Constants.h"
#include "Log.h"
#include "../Useful/Utility.h"


/////////////////////////////////////////////////////////////////////////////////////
// Board summary
// This module is responsible for creating the board of the game, the bitboards, and the captured pieces and the score, as well as treatming how the make_move and undo_function change the different structures
/**
 * A summary of the supported functions is given below:
 * 
 * Arrays that define the precomputed attacks of the pieces from a square
 * 
 * initialize_pawn_attacks : Function to initialize the precomputed attacks for the pawns (to look if a case is threatened by a pawn)
 * initialize_pawn_moves : Function to initialize the precomputed attacks for the pawns (to look where a pawn can go)
 * initialize_knight_attacks : Function to initialize the precomputed attacks for the knights
 * initialize_king_attacks : Function to initialize the precomputed attacks for the kings
 * initialize_rook_attacks : Function to initialize the precomputed attacks for the rooks
 * initialize_bishop_attacks : Function to initialize the precomputed attacks for the bishops
 * initialize_attacks : Function to initialize all the precomputed attacks
 * 
 * calculate_rook_attacks_with_blockers : Function to calculate the rook attacks with the blockers
 * calculate_bishop_attacks_with_blockers : Function to calculate the bishop attacks with the blockers
 * 
 * get_move_value_without_flag : Function to get the move value without the flag
 * get_move_value : Function to get the move value with the flag
 * add_flag_to_move : Function to add a flag to a move value
 * is_move_null : Function to see if a move is null (used in the AI to know if the move is valid)
 * are_same_move : Function to see if two moves are the same
 * get_from_square : Function to get the from square of a move value
 * get_to_square : Function to get the flag of a move value
 * get_flag : Function to get the flag of a move value
 * is_promotion_flag : Function to see if a move is a promotion move
 * get_type_of_promoted_piece : Function to get the type of the promoted piece
 * set_castling_flag : Function to set a specific castling flag
 * is_castling_flag_set : Function to check if a specific castling flag is set
 * 
 * is_legal_move : Function to see if a move is legal for a piece by giving the type of the piece that created the legal move
 * get_king_index : Function to get the index of the king in the bitboard array for a color
 * is_case_threatened : Function to see if a case of a certain color is threatened
 * is_check : Function to see if there is a check for a certain color
 * is_castle_possible : Function to see if a castle move is possible
 * is_promotion_possible : Function to see if a promotion move is possible
 * is_en_passant_possible : Function to see if an en passant move is possible
 * has_pawn_moved_two_squares : Function to see if a pawn has moved two squares during the last move
 * will_capture : Function to see if a move will capture a piece
 * get_type_of_piece : Function to get the type of a piece at a certain index
**/
/////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////
// Arrays that define the precomputed attacks of the pieces from a square
/////////////////////////////////////////////////////////////////////////////////////
extern bit_board** precomputed_pawn_attacks; // [color][square] (color threatened)
extern bit_board** precomputed_pawn_moves; // [color][square] (color moving)
extern bit_board* precomputed_knight_attacks;
extern bit_board* precomputed_king_attacks;
extern bit_board* precomputed_rook_attacks;
extern bit_board* precomputed_bishop_attacks;


/////////////////////////////////////////////////////////////////////////////////////
// Function to initialize the precomputed attacks for the pawns (to look if a case is threatened by a pawn)
/////////////////////////////////////////////////////////////////////////////////////
void initialize_pawn_attacks();


/////////////////////////////////////////////////////////////////////////////////////
// Function to initialize the precomputed attacks for the pawns (to look where a pawn can go)
/////////////////////////////////////////////////////////////////////////////////////
void initialize_pawn_moves();


/////////////////////////////////////////////////////////////////////////////////////
// Function to initialize the precomputed attacks for the knights
/////////////////////////////////////////////////////////////////////////////////////
void initialize_knight_attacks();


/////////////////////////////////////////////////////////////////////////////////////
// Function to initialize the precomputed attacks for the kings
/////////////////////////////////////////////////////////////////////////////////////
void initialize_king_attacks();


/////////////////////////////////////////////////////////////////////////////////////
// Function to initialize the precomputed attacks for the rooks
/////////////////////////////////////////////////////////////////////////////////////
void initialize_rook_attacks();


/////////////////////////////////////////////////////////////////////////////////////
// Function to initialize the precomputed attacks for the bishops
/////////////////////////////////////////////////////////////////////////////////////
void initialize_bishop_attacks();


/////////////////////////////////////////////////////////////////////////////////////
// Function to initialize all the precomputed attacks
/////////////////////////////////////////////////////////////////////////////////////
void initialize_attacks();


/////////////////////////////////////////////////////////////////////////////////////
// Function to calculate the pawn attack with the blockers
// here it's only in the legal move function, but the color for the diagonal capture is dealt with in the is_legal_move function
/** 
 * @param pawn_pos : The position of the pawn
 * @param color_moving : The color of the pawn
 * @param all_pieces : The bitboard of all the pieces
**/
/////////////////////////////////////////////////////////////////////////////////////
bit_board calculate_pawn_moves_with_blockers(int pawn_pos, int color_moving, bit_board all_pieces);


/////////////////////////////////////////////////////////////////////////////////////
// Function to calculate the rook attacked squares considering the pieces that can block the rook 
// it doesn't consider that the color of the last piece it can go to (for the is_legal_move function, not needed for the is_case_threatened function)
/**
 * @param rook_pos : The position of the rook
 * @param all_pieces : The bitboard of all the pieces
 * @return the bitboard of the squares attacked by the rook considering the pieces that can block the rook
**/
/////////////////////////////////////////////////////////////////////////////////////
bit_board calculate_rook_attacks_with_blockers(int rook_pos, bit_board all_pieces);


/////////////////////////////////////////////////////////////////////////////////////
// Function to calculate the bishop attacked squares considering the pieces that can block the bishop
// it doesn't consider that the color of the last piece it can go to (for the is_legal_move function, not needed for the is_case_threatened function)
/**
 * @param bishop_pos : The position of the bishop
 * @param all_pieces : The bitboard of all the pieces
 * @return the bitboard of the squares attacked by the bishop considering the pieces that can block the bishop
**/
/////////////////////////////////////////////////////////////////////////////////////
bit_board calculate_bishop_attacks_with_blockers(int bishop_pos, bit_board all_pieces);


/////////////////////////////////////////////////////////////////////////////////////
// Function to get the move value without the flag
/**
 * @param from : The square from which the piece is moving
 * @param to : The square to which the piece is moving
 * @return the move value without the flag
**/
/////////////////////////////////////////////////////////////////////////////////////
move get_move_value_without_flag(int from, int to);


/////////////////////////////////////////////////////////////////////////////////////
// Function to get the move value with the flag
/**
 * @param from : The square from which the piece is moving
 * @param to : The square to which the piece is moving
 * @param flag : The flag of the move
 * @return the move value with the flag
**/
/////////////////////////////////////////////////////////////////////////////////////
move get_move_value(int from, int to, int flag);


/////////////////////////////////////////////////////////////////////////////////////
// Function to add a flag to a move value
/**
 * @param move_value : The move value
 * @param flag : The flag to add
**/
/////////////////////////////////////////////////////////////////////////////////////
void add_flag_to_move(move* move_value, int flag);


/////////////////////////////////////////////////////////////////////////////////////
// Function see if a move is null (used in the AI to know if the move is valid)
/**
 * @param move_value : The move value
 * @return true if the move is null, false otherwise
**/
/////////////////////////////////////////////////////////////////////////////////////
bool is_move_null(move move_value);


/////////////////////////////////////////////////////////////////////////////////////
// Function to see if two moves are the same
/**
 * @param move_a : The first move
 * @param move_b : The second move
 * @return true if the moves are the same, false otherwise
**/
/////////////////////////////////////////////////////////////////////////////////////
bool are_same_move(move move_a, move move_b);


/////////////////////////////////////////////////////////////////////////////////////
// Function to get the from square of a move value
/**
 * @param move_value : The move value
 * @return the from square of the move
**/
/////////////////////////////////////////////////////////////////////////////////////
int get_from_square(move move_value);


/////////////////////////////////////////////////////////////////////////////////////
// Function to get the flag of a move value
/**
 * @param move_value : The move value
 * @return the flag of the move
**/
/////////////////////////////////////////////////////////////////////////////////////
int get_to_square(move move_value);


/////////////////////////////////////////////////////////////////////////////////////
// Function to get the flag of a move value
/**
 * @param move_value : The move value
 * @return the flag of the move
**/
/////////////////////////////////////////////////////////////////////////////////////
int get_flag(move move_value);


/////////////////////////////////////////////////////////////////////////////////////
// Function to see if a move is a promotion move
/**
 * @param move_flag : The flag of the move
 * @return true if the move is a promotion move, false otherwise
**/
/////////////////////////////////////////////////////////////////////////////////////
bool is_promotion_flag(int move_flag);


/////////////////////////////////////////////////////////////////////////////////////
// Function to get the type of the promoted piece
/**
 * @param move_flag : The flag of the move
 * @param color : The color of the promoted piece
 * @return the type of the promoted piece
**/
/////////////////////////////////////////////////////////////////////////////////////
int get_type_of_promoted_piece(int move_flag, int color);


/////////////////////////////////////////////////////////////////////////////////////
// Function to set a specific castling flag
/**
 * @param castling_rights : The castling rights to modify
 * @param flag : The flag to set
**/
/////////////////////////////////////////////////////////////////////////////////////
void set_castling_flag(castling_rights_flags* castling_rights, castling_rights_flags flag);


/////////////////////////////////////////////////////////////////////////////////////
// Function to check if a specific castling flag is set
/**
 * @param castling_rights : The castling rights to check
 * @param flag : The flag to check
 * @return true if the flag is set, false otherwise
**/
/////////////////////////////////////////////////////////////////////////////////////
bool is_castling_flag_set(castling_rights_flags castling_rights, castling_rights_flags flag);


/////////////////////////////////////////////////////////////////////////////////////
// Function to see if a move is legal for a piece by giving the type of the piece that created the legal move
/**
 * @param attacking_color : The color of the piece that is attacking
 * @param bitboard_array : The array of bitboards
 * @param from : The square from which the piece is moving
 * @param to : The square to which the piece is moving
 * @param flag : The flag of the move
 * @return the type of the piece that is involved in the legal move (NOTHING if it is not a legal move)
**/
/////////////////////////////////////////////////////////////////////////////////////
int is_legal_move(int attacking_color, bit_board* bitboard_array, int from, int to, int flag);


/////////////////////////////////////////////////////////////////////////////////////
// Function to get the index of the king in the bitboard array for a color
/**
 * @param bitboard_array : The array of bitboards
 * @param color : The color of the king
 * @return the index of the king in the bitboard array
**/
/////////////////////////////////////////////////////////////////////////////////////
int get_king_index(bit_board* bitboard_array, int color);


/////////////////////////////////////////////////////////////////////////////////////
// Function to see if a case of a certain color is threatened
/**
 * @param color : The color of the case
 * @param case_index : The index of the case
 * @param bitboard_array : The array of bitboards
 * @param log : The log of the game
 * @return true if the case is threatened, false otherwise
**/
/////////////////////////////////////////////////////////////////////////////////////
bool is_case_threatened(int color, int case_index, bit_board* bitboard_array, Log* log);


/////////////////////////////////////////////////////////////////////////////////////
// Function to see if there is a check for a certain color
/**
 * @param color : The color of the king
 * @param bitboard_array : The array of bitboards
 * @param log : The log of the game
 * @return 1 if there is a check, 0 otherwise
**/
/////////////////////////////////////////////////////////////////////////////////////
int is_check(int color, bit_board* bitboard_array, Log* log);


/////////////////////////////////////////////////////////////////////////////////////
// Function to see if a castle move is possible
/**
 * @param color : The color of the king
 * @param bitboard_array : The array of bitboards
 * @param from : The square from which the king is moving
 * @param to : The square to which the king is moving
 * @param log : The log of the game
 * @return true if the castle is possible, false otherwise
**/
/////////////////////////////////////////////////////////////////////////////////////
bool is_castle_possible(int color, bit_board* bitboard_array, int from, int to, Log* log);


/////////////////////////////////////////////////////////////////////////////////////
// Function to see if a promotion move is possible
/**
 * @param color : The color of the pawn
 * @param bitboard_array : The array of bitboards
 * @param from : The square from which the pawn is moving
 * @param to : The square to which the pawn is moving
 * @return true if the promotion is possible, false otherwise
**/
/////////////////////////////////////////////////////////////////////////////////////
bool is_promotion_possible(int color, bit_board* bitboard_array, int from, int to);


/////////////////////////////////////////////////////////////////////////////////////
// Function to see if an en passant move is possible
/**
 * @param color : The color of the pawn
 * @param bitboard_array : The array of bitboards
 * @param from : The square from which the pawn is moving
 * @param to : The square to which the pawn is moving
 * @param log : The log of the game
 * @return true if the en passant is possible, false otherwise
**/
/////////////////////////////////////////////////////////////////////////////////////
bool is_en_passant_possible(int color, bit_board* bitboard_array, int from, int to, Log* log);


/////////////////////////////////////////////////////////////////////////////////////
// Function to see if a pawn has moved two squares during the last move
/**
 * @param color : The color of the pawn
 * @param bitboard_array : The array of bitboards
 * @param from : The square from which the pawn is moving
 * @param to : The square to which the pawn is moving
 * @return true if the pawn has moved two squares, false otherwise
**/
/////////////////////////////////////////////////////////////////////////////////////
bool has_pawn_moved_two_squares(int color, bit_board* bitboard_array, int from, int to);


/////////////////////////////////////////////////////////////////////////////////////
// Function to know if a capture will be done
/**
 * @param color : the color of the player that is playing
 * @param bitboards : the bitboards of the game
 * @param to : the position where the piece is moving
 * @return true if a capture will be done, false otherwise
**/
/////////////////////////////////////////////////////////////////////////////////////
bool will_capture(int color, bit_board* bitboard_array, int to);


/////////////////////////////////////////////////////////////////////////////////////
// Function to get the type of the piece at this position 
/**
 * @param bitboards : the bitboards of the game
 * @param position_index : the position of the piece
 * @return the type of the piece at this position
**/
/////////////////////////////////////////////////////////////////////////////////////
int get_type_of_piece(bit_board* bitboard_array, int position_index);


#endif /* __MOVES_TREATMENT_H__ */