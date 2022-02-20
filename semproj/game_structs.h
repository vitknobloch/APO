/*******************************************************************
  APO semestral project file.
  Header file with definitions of struct used by game_controller and
  slider controller (and other modules)

  Vit Knobloch, Adam Loucky
  CTU FEE 2021
  
  license: any combination GPL, LGPL, MPL or BSD licenses

 *******************************************************************/

#ifndef __GAME_STRUCTS_H__
#define __GAME_STRUCTS_H__

#include <time.h>

/**
 * @brief Struct with information about slider
 */
typedef struct
{
    int height;        //height of the slider in pixels
    double pos;        //vertical position of center of the slider in pixel (relative to game)
    double speed;      //speed in pixels per second of the sliders movement
    double target_pos; //position the slider wants to move to if AI_controlled
    int ai_lvl;        //intelligence level of the AI (0 - no AI, 1 - easy, 2 - normal, 3 - hard)
    int lifes_count;   //number of misses the slider can have before game ends
} slider_t;

/**
 * @brief Struct with information about game
 */
typedef struct
{
    int width;              //width of the game space
    int height;             // height of the game space
    double speed;           //speed of the ball in pixels per second
    double direction;       //direction of the balls movement <0, 2pi)
    double speed_change;    //speed up per second of the ball
    double speed_cap;       //maximal speed of the ball
    double speed_init;      //initial speed of the ball
    double x_pos;           //x position of the ball
    double y_pos;           //y position of the ball
    slider_t *left_slider;  //left slider in the game
    slider_t *right_slider; //right slider in the game
} game_t;

#endif