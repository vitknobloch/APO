/*******************************************************************
  APO semestral project file.
  Module for graphical printing od game in progress on graphical display
  of MZ_APO.

  Vit Knobloch, Adam Loucky
  CTU FEE 2021
  
  license: any combination GPL, LGPL, MPL or BSD licenses

 *******************************************************************/

#ifndef __GAME_PRINTER_H__
#define __GAME_PRITNER_H__

#include "game_structs.h"
#include "frame_printer.h"
#include "font_printer.h"

/**
 * @brief Prints game with top-left corner of the playing are at x, y
 * 
 * @param fb frame buffer to print to
 * @param game game to print
 * @param x x coordinate of the games top-left corner (left slider exclusive)
 * @param y y coordinate of the games top-left corner (where the ball center can be)
 */
void print_game(fb_t *fb, game_t *game, int x, int y);

/**
 * @brief Prints header to the game in progress - player names and scores
 * 
 * @param fb frame buffer to print to
 * @param lifes_left remaining lifes of left player
 * @param lifes_right remaining lifes of right player
 * @param left_AI true if left player is AI controlled, otherwise false
 * @param right_AI true if right player is AI controlled, otherwise false
 */
void print_header(fb_t *fb, int lifes_left, int lifes_right, char left_AI, char right_AI);

#endif