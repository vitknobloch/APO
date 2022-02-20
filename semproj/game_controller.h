/*******************************************************************
  APO semestral project file.
  Module for calculating changes in ball direction, position and speed,
  implementation of PONG physics and logic

  Vit Knobloch, Adam Loucky
  CTU FEE 2021
  
  license: any combination GPL, LGPL, MPL or BSD licenses

 *******************************************************************/

#ifndef __GAME_CONTROLLER_H__
#define __GAME_CONTROLLER_H__

#include "game_structs.h"

/** 
 * @brief Updates the game with time_mult seconds timespan since last frame 
 * returns 0 if game isn't over, -1 if left player lost and 1 if right player lost. 
 * 
 * @param game game to update
 * @param time_mult time since last update in seconds 
 * @return int - -1 if left player lost, +1 if right player lost, 0 if game continues.
 */
int game_update(game_t *game, double time_mult);

/** 
 * @brief Initializes new game with given properties. 
 * @param width width of game board.
 * @param height height of game board. 
 * @param speed initial speed of the ball
 * @param speed_change change of speed size per second.
 * @param speed_cap maximal speed the ball can reach.
 * @param direction angle of speed direction in radians (zero is straight right)
 * @param x_pos initial x position of the ball.
 * @param y_pos initial y position of the ball.
 * @param left_slider slider on the left side of the board.
 * @param right_slider slider on the right side of the board.
 */
game_t *game_init(int width, int height, double speed, double speed_change,
                  double speed_cap, double direction, double x_pos, double y_pos,
                  slider_t *left_slider, slider_t *right_slider);

/**
 * @brief Frees allocated game struct
 * 
 * @param game game to free
 */
void game_free(game_t *game);

#endif