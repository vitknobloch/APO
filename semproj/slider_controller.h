/*******************************************************************
  APO semestral project file.
  Module for controlling sliders movement and implementation of AI.

  Vit Knobloch, Adam Loucky
  CTU FEE 2021
  
  license: any combination GPL, LGPL, MPL or BSD licenses

 *******************************************************************/

#ifndef __SLIDER_CONTROLLER_H__
#define __SLIDER_CONTROLLER_H__

#include "game_structs.h"

/**
 * @brief initializes slider with passed parameters (has to be freed later)
 * 
 * @param height height of slider
 * @param pos initial position of the sliders middle point
 * @param speed inital speed of the sliders movement (in pixel per second)
 * @param ai_level the level of intelligence of auto control (0 - no AI, 1 - easy, 2 - normal, 3 - hard)
 * @param life_count Number of lifes the player has before game is over
 * @return slider_t* new slider struct
 */
slider_t *slider_init(int height, double pos, double speed, int ai_level, int life_count);

/**
 * @brief Frees the sliders allocated memory
 * 
 * @param slider slider to free
 */
void slider_free(slider_t *slider);

/**
 * @brief move both sliders with given moves
 * 
 * @param game game_t whoose sliders should move
 * @param left_move left slider move (-1 if slider should move up +1 if slider should move down)
 * @param right_move right slider move(-1 if slider should move up +1 if slider should move down)
 * @param time_mult time in seconds since last update
 */
void sliders_move(game_t *game, double left_move, double right_move, double time_mult);

/**
 * @brief Generates move of slider to move it closer to it's targer position.
 * 
 * @param slider slider to generate move for
 * @return double - -1 if slider should move up, +1 if slider should move up
 */
double slider_generate_move(slider_t *slider);

/**
 * @brief calculates new target position for the slider so that it hits the ball.
 * 
 * @param slider slider to update target position for
 * @param game game to calculate target position from
 */
void slider_update_target_pos(slider_t *slider, game_t *game);

/**
 * @brief calculates new target position for the slider after it hits the ball
 * according to it's intelligence level
 * 
 * @param slider slider to generate the target position for.
 * @param game the game to calculate the target position for.
 */
void slider_update_target_pos_after_play(slider_t *slider, game_t *game);

#endif