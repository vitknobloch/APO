/*******************************************************************
  APO semestral project file.
  Module for controlling sliders movement and implementation of AI.

  Vit Knobloch, Adam Loucky
  CTU FEE 2021
  
  license: any combination GPL, LGPL, MPL or BSD licenses

 *******************************************************************/

#include "slider_controller.h"
#include "my_malloc.h"

#include <stdlib.h>

#include <math.h>

/**
 * @brief moves slider in given direction 
 * 
 * @param slider slider to move
 * @param move -1 if slider should move up +1 if slider should move down
 * @param height height of game board
 * @param time_mult time in seconds since last update
 */
void slider_move(slider_t *slider, double move, double height, double time_mult);

void slider_move(slider_t *slider, double move, double height, double time_mult)
{
    //update sliders position
    slider->pos += move * time_mult * slider->speed;
    //stop sliders at frame border
    if (slider->pos < slider->height / 2 - 10)
    {
        slider->pos = slider->height / 2 - 10;
    }
    else if (slider->pos > height - slider->height / 2 + 10)
    {
        slider->pos = height - slider->height / 2 + 10;
    }
}

void sliders_move(game_t *game, double left_move, double right_move, double time_mult)
{
    slider_move(game->left_slider, left_move, game->height, time_mult);
    slider_move(game->right_slider, right_move, game->height, time_mult);
}

double slider_generate_move(slider_t *slider)
{
    //treshold close to target position where the slider wont move
    if (fabs(slider->pos - slider->target_pos) < (slider->height / 10.0))
        return 0;
    else if (slider->pos < slider->target_pos)
        return 1;
    else
        return -1;
}

slider_t *slider_init(int height, double pos, double speed, int ai_level, int life_count)
{
    slider_t *slider = allocate_memory(sizeof(slider_t));
    slider->height = height;
    slider->pos = pos;
    slider->speed = speed;
    slider->target_pos = pos;
    slider->ai_lvl = ai_level;
    slider->lifes_count = life_count;

    return slider;
}

void slider_update_target_pos(slider_t *slider, game_t *game)
{
    if (slider->ai_lvl == 0)
        return;
    //get how long it will take for ball to get to slider
    const double x_speed = cos(game->direction) * game->speed;
    const double x_distance = x_speed > 0 ? game->width - game->x_pos : game->x_pos;
    const double time_to_hit = fabs(x_distance / x_speed);

    //calculate where the ball will be at that moment
    const double y_full = sin(game->direction) * game->speed * time_to_hit + game->y_pos;
    double y_mod = fmod(y_full, game->height);
    y_mod = y_mod < 0 ? y_mod + game->height : y_mod;

    if ((int)floor(y_full / game->height) % 2)
    {
        slider->target_pos = game->height - y_mod;
    }
    else
    {
        slider->target_pos = y_mod;
    }
}

void slider_update_target_pos_after_play(slider_t *slider, game_t *game)
{
    if (slider->ai_lvl == 1 || slider->ai_lvl == 0) //no AI or easy, don't move
    {
        return;
    }
    if (slider->ai_lvl == 2) //normal, return to center
    {
        slider->target_pos = game->height / 2;
        return;
    }

    //hard, predict hit area after opponents play
    //get how long it will take for ball to get to slider
    const double x_speed = cos(game->direction) * game->speed;
    const double x_distance = x_speed > 0 ? 2 * game->width - game->x_pos : game->x_pos + game->width;
    const double time_to_hit = fabs(x_distance / x_speed);

    //calculate where the ball will be at that moment
    const double y_full = sin(game->direction) * game->speed * time_to_hit + game->y_pos;
    double y_mod = fmod(y_full, game->height);
    y_mod = y_mod < 0 ? y_mod + game->height : y_mod;

    if ((int)floor(y_full / game->height) % 2)
    {
        slider->target_pos = game->height - y_mod;
    }
    else
    {
        slider->target_pos = y_mod;
    }
}

void slider_free(slider_t *slider)
{
    deallocate_memory((void **)&slider);
}