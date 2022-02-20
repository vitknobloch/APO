/*******************************************************************
  APO semestral project file.
  Module for controlling game difficulty and running series of matches,
  with score.

  Vit Knobloch, Adam Loucky
  CTU FEE 2021
  
  license: any combination GPL, LGPL, MPL or BSD licenses

 *******************************************************************/

#ifndef __GAME_RUNNER_H__
#define __GAME_RUNNER_H__

/**
 * @brief Starts series of games with given settings and keeps score
 * 
 * @param fb Frame buffer to output the game to
 * @param difficulty difficulty level (1-easy, 2-normal, 3-hard)
 * @param left_AI true if left slider is AI_controlled, false otherwise
 * @param right_AI true if right slider is AI_cotrolled, false otherwise
 */
void run_games(fb_t *fb, int difficulty, char left_AI, char right_AI);

#endif