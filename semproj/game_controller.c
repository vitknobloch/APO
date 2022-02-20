/*******************************************************************
  APO semestral project file.
  Module for calculating changes in ball direction, position and speed,
  implementation of PONG physics and logic

  Vit Knobloch, Adam Loucky
  CTU FEE 2021
  
  license: any combination GPL, LGPL, MPL or BSD licenses

 *******************************************************************/

#include "game_controller.h"
#include "slider_controller.h"
#include "my_malloc.h"
#include <stdlib.h>
#include <math.h>

#include <stdio.h>

#define PI 3.14159265358979323846
#define MAX_DEVIATION 0.09 //maximal radian angle change of ball path after bounce

/* Returns 0 if game isn't over, -1 if left player lost and 1 if right player lost. */
int check_game_over(game_t *game);
/* Checks if ball should bounce and bounces it if so. */
void check_borders(game_t *game);
/* Checks if ball should bounce on the sides and bounces it if so. */
void check_borders_x(game_t *game);
/* Checks if ball should bounce on the top/bottom and bounces it if so. */
void check_borders_y(game_t *game);
/* Changes ball direction by random angle in range +-MAX_DEVIATION radians. */
double skew_direction(double direction);
/* Returns true if passed y position is within sliders hit-box. */
int check_slider_hit(double y, double slider_pos, int slider_height);
/* Calculates position of the ball after it hits the wall */
double after_bounce_position(double pos, double max);

game_t *game_init(int width, int height, double speed, double speed_change,
                  double speed_cap, double direction, double x_pos, double y_pos,
                  slider_t *left_slider, slider_t *right_slider)
{
    game_t *game = allocate_memory(sizeof(game_t));

    game->width = width;
    game->height = height;
    game->speed = speed;
    game->direction = direction;
    game->speed_change = speed_change;
    game->x_pos = x_pos;
    game->y_pos = y_pos;
    game->left_slider = left_slider;
    game->right_slider = right_slider;
    game->speed_cap = speed_cap;
    game->speed_init = speed;

    return game;
}

void game_free(game_t *game)
{
    deallocate_memory((void **)&game);
}

double after_bounce_position(double pos, double max)
{
    double pos_mod = fmod(pos, max);
    pos_mod = pos_mod < 0 ? pos_mod + max : pos_mod;
    //set position, according to whether the ball hit bottom or top
    return ((int)floor(pos / max) % 2) ? max - pos_mod : pos_mod;
}

double skew_direction(double direction)
{
    const double rand_dev = ((rand() / (double)RAND_MAX) - 0.5) * 2.0 * MAX_DEVIATION;
    return direction + rand_dev;
}

void check_borders_x(game_t *game)
{
    if (game->x_pos < 0)
    {
        //change direction
        game->direction = fmod(PI - game->direction, 2 * PI);
        game->direction = skew_direction(game->direction);
        //update target positions of sliders
        slider_update_target_pos(game->right_slider, game);
        slider_update_target_pos_after_play(game->left_slider, game);
    }
    else if (game->x_pos > game->width)
    {
        //bounce
        game->direction = fmod(PI - game->direction, 2 * PI);
        game->direction = skew_direction(game->direction);
        //update target positions of sliders
        slider_update_target_pos(game->left_slider, game);
        slider_update_target_pos_after_play(game->right_slider, game);
    }
    //update position according to bounce
    game->x_pos = after_bounce_position(game->x_pos, game->width);
}

void check_borders_y(game_t *game)
{
    //update direction
    if (game->y_pos < 0)
    {
        game->direction = fmod(-game->direction, 2 * PI);
    }
    else if (game->y_pos > game->height)
    {
        game->direction = fmod(-game->direction, 2 * PI);
    }
    //update position
    game->y_pos = after_bounce_position(game->y_pos, game->height);
}

void check_borders(game_t *game)
{
    check_borders_x(game);
    check_borders_y(game);
}

int check_slider_hit(double y, double slider_pos, int slider_height)
{
    const double relative_pos = y - slider_pos;
    return (relative_pos < slider_height / 2.0 + 5 &&
            relative_pos > slider_height / -2.0 - 5);
}

int check_game_over(game_t *game)
{
    //if balls position is within game space no winner
    if (!(game->x_pos < 0 || game->x_pos > game->width))
        return 0;

    //check that player hit the ball when crossing slider x pos if ball is outside game space
    const double x_speed = cos(game->direction) * game->speed;
    const double x_distance = x_speed > 0 ? game->width - game->x_pos : game->x_pos;
    const double time_since_hit = fabs(x_distance / x_speed);

    const double y_full = -sin(game->direction) * game->speed * time_since_hit + game->y_pos;
    double y = after_bounce_position(y_full, game->height);

    if (x_speed < 0)
    {
        if (!check_slider_hit(y, game->left_slider->pos, game->left_slider->height))
        {
            if (--game->left_slider->lifes_count <= 0)
                return -1;
        }
    }
    else
    {
        if (!check_slider_hit(y, game->right_slider->pos, game->right_slider->height))
        {
            if (--game->right_slider->lifes_count <= 0)
                return 1;
        }
    }

    return 0;
}

int game_update(game_t *game, double time_mult)
{
    //update ball position
    game->x_pos += game->speed * cos(game->direction) * time_mult;
    game->y_pos += game->speed * sin(game->direction) * time_mult;

    //check game over
    int winner = check_game_over(game);
    if (winner)
        return winner;

    //update spped
    game->speed += game->speed_change * time_mult;
    if (game->speed > game->speed_cap)
        game->speed = game->speed_cap;
    //check for bounces
    check_borders(game);
    return 0;
}