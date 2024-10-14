#ifndef __UTILITY_H__
#define __UTILITY_H__


#include "SDL2/SDL.h"
#include "SDL_image.h"
#include "SDL_ttf.h"


#include "Constants.h"


/////////////////////////////////////////////////////////////////////////////////////
// Useful summary
// This module is responsible for creating all the useful function that are used in the game but not part of the game
// Mainly, it contains the functions to apply a Gaussian blur on an image, add an image to the renderer and add a text to the renderer
/**
 * A summary of the supported functions is given below:
 * 
 * play_sound: Play a sound 
 * (The audio will be used to play a sound when a piece is taken, when a piece is moved, when the game is won, or when the game is lost)
 * (It will be useful to give a better experience to the player, and to make the game more enjoyable)
 * 
 * createGaussianKernel: Create a 1D Gaussian kernel
 * applyHorizontalBlur: Apply a 1D Gaussian blur horizontally
 * applyVerticalBlur: Apply a 1D Gaussian blur vertically
 * applyBlur: Optimized function to apply Gaussian blur
 * add_image_to_render: Add an image to the renderer
 * Draw_the_red_boundary_move_Rect: Draw the rectangle that is around a selected button by making it larger
 * Draw_Filled_Circle: Draw a filled circle of a given radius, at a given center
 * add_font_to_render: Add a text to the renderer
 * 
 * is_point_in_rect: Function to know if a point (x,y) is in a rectangle
 * 
 * min: Function that returns the minimum of two integers
 * max: Function that returns the maximum of two integers
 * 
 * set_seed: Function to set a custom seed based on current time
 * custom_rand: Function to generate a random number (LCG)
 * random_int: Function to generate a random number within a given range
 * 
 * int_clamp: Function to clamp a value between a minimum and a maximum (for integers)
 * float_clamp: Function to clamp a value between a minimum and a maximum (for floats)
 * get_rank: Function to get the rank of a square of the chess board
 * get_file: Function to get the file of a square of the chess board
 * get_index: Function to get the index of a square of the chess board
 * divide_by_two: Function to divide a number by two
**/
/////////////////////////////////////////////////////////////////////////////////////


/////////////////////////////////////////////////////////////////////////////////////
// Play a sound
/**
 * @param filename - the name of the file to play
 **/
/////////////////////////////////////////////////////////////////////////////////////
void play_sound(const char* filename);


/////////////////////////////////////////////////////////////////////////////////////
// Helper function to create a 1D Gaussian kernel
/**
 * @param kernel : the kernel to be created
 * @param radius : the radius of the kernel
**/
/////////////////////////////////////////////////////////////////////////////////////
void createGaussianKernel(float* kernel, int radius);


/////////////////////////////////////////////////////////////////////////////////////
// Function to apply a 1D Gaussian blur horizontally
/**
 * @param pixels : the pixels to apply the blur to
 * @param tempPixels : the temporary pixels to store the blurred image
 * @param width : the width of the image
 * @param height : the height of the image
 * @param kernel : the kernel to apply the blur with
**/
/////////////////////////////////////////////////////////////////////////////////////
void applyHorizontalBlur(Uint32* pixels, Uint32* tempPixels, int width, int height, float* kernel, int radius);


/////////////////////////////////////////////////////////////////////////////////////
// Function to apply a 1D Gaussian blur vertically
/**
 * @param tempPixels : the temporary pixels to apply the blur to
 * @param pixels : the pixels to store the blurred image
 * @param width : the width of the image
 * @param height : the height of the image
 * @param kernel : the kernel to apply the blur with
**/
/////////////////////////////////////////////////////////////////////////////////////
void applyVerticalBlur(Uint32* tempPixels, Uint32* pixels, int width, int height, float* kernel, int radius);


/////////////////////////////////////////////////////////////////////////////////////
// Optimized function to apply Gaussian blur
/**
 * @param renderer : the renderer to apply the blur on
 * @param width : the width of the texture
 * @param height : the height of the texture
 * @param radius : the radius of the blur, how much to blur the image
**/
/////////////////////////////////////////////////////////////////////////////////////
void applyBlur(SDL_Renderer* renderer, int width, int height, int radius);


/////////////////////////////////////////////////////////////////////////////////////
// Function to add an image to the renderer
/**
 * @param filename : the path to the image file
 * @param renderer : it's modified to include the image
 * @param destRect : the destination rectangle for the image
**/
/////////////////////////////////////////////////////////////////////////////////////
void add_image_to_render(const char* filename, SDL_Renderer* renderer, SDL_Rect destRect);


/////////////////////////////////////////////////////////////////////////////////////
// Function to draw the rectangle that is around a selected button by making it larger 
/**
 * @param renderer - the renderer to show the menu
 * @param draw_red_boundary_move - the red boundary to draw around a piece when it's selected to make a move
**/
/////////////////////////////////////////////////////////////////////////////////////
void Draw_the_red_boundary_move_Rect(SDL_Renderer* renderer, SDL_Rect draw_red_boundary_move);


/////////////////////////////////////////////////////////////////////////////////////
// Function to draw a filled circle of a given radius, at a given center
/**
 * @param renderer : the renderer to draw the circle on
 * @param center_col : the center of the circle on the x axis
 * @param center_row : the center of the circle on the y axis
 * @param radius : the radius of the circle
**/
/////////////////////////////////////////////////////////////////////////////////////
void Draw_Filled_Circle(SDL_Renderer *renderer, int center_col, int center_row, int radius);


/////////////////////////////////////////////////////////////////////////////////////
//
/**
 * @param renderer : the renderer to add the text to 
 * @param text : the text to add
 * @param font_size : the size of the font
 * @param textColor : the color of the text
 * @param width_of_middle_of_text : the position of the middle of the text on the x axis
 * @param heigth_of_middle_of_text : the position of the middle of the text on the y axis
**/
/////////////////////////////////////////////////////////////////////////////////////
void add_font_to_render(SDL_Renderer* renderer, const char* text, int font_size, SDL_Color textColor, int width_of_middle_of_text, int heigth_of_middle_of_text);


/////////////////////////////////////////////////////////////////////////////////////
// Function to know if a point (x,y) is in a rectangle  
/**
 * @param x : the x coordinate of the point
 * @param y : the y coordinate of the point
 * @param rect : the rectangle to check
 * @return bool : true if the point is in the rectangle, false otherwise
**/
/////////////////////////////////////////////////////////////////////////////////////
bool is_point_in_rect(int x, int y, SDL_Rect rect);


/////////////////////////////////////////////////////////////////////////////////////
// Function that returns the minimum of two integers
/**
 * @param a : the first integer
 * @param b : the second integer
 * @return the minimum of the two integers
**/
/////////////////////////////////////////////////////////////////////////////////////
int min (int a, int b);


/////////////////////////////////////////////////////////////////////////////////////
// Function that returns the maximum of two integers
/**
 * @param a : the first integer
 * @param b : the second integer
 * @return the maximum of the two integers
**/
/////////////////////////////////////////////////////////////////////////////////////
int max (int a, int b);


/////////////////////////////////////////////////////////////////////////////////////
// Function to set a custom seed based on current time
/////////////////////////////////////////////////////////////////////////////////////
void set_seed();


/////////////////////////////////////////////////////////////////////////////////////
// Function to generate a random number (LCG)
/**
 * @return the random number
**/
/////////////////////////////////////////////////////////////////////////////////////
unsigned int custom_rand();


/////////////////////////////////////////////////////////////////////////////////////
// Function to generate a random integer between min and max
/**
 * @param min : the minimum value
 * @param max : the maximum value
**/
/////////////////////////////////////////////////////////////////////////////////////
int random_int(int min, int max);


/////////////////////////////////////////////////////////////////////////////////////
// Function to clamp a value between a minimum and a maximum (for integers)
/**
 * @param value : the value to clamp
 * @param min : the minimum value
 * @param max : the maximum value
 * @return the clamped value
**/
/////////////////////////////////////////////////////////////////////////////////////
int int_clamp(int value, int min, int max);


/////////////////////////////////////////////////////////////////////////////////////
// Function to clamp a value between a minimum and a maximum (for floats)
/**
 * @param value : the value to clamp
 * @param min : the minimum value
 * @param max : the maximum value
 * @return the clamped value
**/
/////////////////////////////////////////////////////////////////////////////////////
float float_clamp(float value, float min, float max);


/////////////////////////////////////////////////////////////////////////////////////
// Function to get the rank of a square of the chess board
// to fast things in the AI search part
/**
 * @param square : the square to get the rank of
 * @return the rank of the square
**/
/////////////////////////////////////////////////////////////////////////////////////
int get_rank(int square);


/////////////////////////////////////////////////////////////////////////////////////
// Function to get the file of a square of the chess board
// to fast things in the AI search part
/**
 * @param square : the square to get the file of
 * @return the file of the square
**/
/////////////////////////////////////////////////////////////////////////////////////
int get_file(int square);


/////////////////////////////////////////////////////////////////////////////////////
// Function to get the index of a square of the chess board
// to fast things in the AI search part
/**
 * @param rank : the rank of the square
 * @param file : the file of the square
 * @return the index of the square
**/
/////////////////////////////////////////////////////////////////////////////////////
int get_index(int rank, int file);


/////////////////////////////////////////////////////////////////////////////////////
// Function to divide a number by two
// to fast things in the graphics printing part
/**
 * @param number : the number to divide by two
 * @return the number divided by two
**/
/////////////////////////////////////////////////////////////////////////////////////
int divide_by_two(int number);


#endif /* __UTILITY_H__ */