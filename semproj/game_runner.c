/*******************************************************************
  APO semestral project file.
  Module for controlling game difficulty and running series of matches,
  with score.

  Vit Knobloch, Adam Loucky
  CTU FEE 2021
  
  license: any combination GPL, LGPL, MPL or BSD licenses

 *******************************************************************/

#include <stdlib.h>
#include <time.h>

#include "frame_printer.h"
#include "terminal_controller.h"
#include "game_controller.h"
#include "game_printer.h"
#include "slider_controller.h"
#include "game_structs.h"
#include "menu.h"

//menu definitions
extern menu_t pause_menu;
extern menu_t game_over_menu;

//private methods declatrations
slider_t *create_slider(int difficulty, char AI_controlled);
game_t *create_game(int difficulty, slider_t *left_s, slider_t *right_s);
double generate_move_left(unsigned int keys_pressed, slider_t *slider, char AI_controlled);
double generate_move_right(unsigned int keys_pressed, slider_t *slider, char AI_controlled);
int run_game(fb_t *fb, int difficulty, char left_AI, char right_AI, int score_left, int score_right);

void run_games(fb_t *fb, int difficulty, char left_AI, char right_AI)
{
    int score_left = 0;
    int score_right = 0;

    int run = 0;
    while (run != -2)
    {
        run = run_game(fb, difficulty, left_AI, right_AI, score_left, score_right);
        if (run == 1)
        {
            score_left++;
        }
        else if (run == -1)
        {
            score_right++;
        }
    }
}

int run_game(fb_t *fb, int difficulty, char left_AI, char right_AI, int score_left, int score_right)
{
    //create sliders
    slider_t *left_s = create_slider(difficulty, left_AI);
    slider_t *right_s = create_slider(difficulty, right_AI);

    //create game
    game_t *game = create_game(difficulty, left_s, right_s);

    //update leds according to control
    uint32_t left_led = left_AI ? 0x88 : 0x8800;
    uint32_t right_led = right_AI ? 0x88 : 0x8800;
    update_leds(fb, left_led, right_led);

    int winner = 0;
    clock_t prev = clock(); //time of previous frame
    while (!winner)
    {
        unsigned int keys_pressed = get_pressed_keys();
        //check for pause
        if (keys_pressed & P_ESCAPE)
        {
            int pause_ret = show_menu(fb, pause_menu);
            if (pause_ret == -1 || pause_ret == 0) //ESC or resume
            {
                prev = clock();
                continue;
            }
            else if (pause_ret == 1) //restart game
            {
                winner = 0;
                break;
            }
            else if (pause_ret == 2) //return to menu
            {
                winner = -2;
                break;
            }
        }

        clock_t cur = clock();
        //how many seconds since last frame
        double time_mult = (cur - prev) / (double)CLOCKS_PER_SEC;
        prev = cur;

        //get sliders movement according to user input or AI target
        double left_move = generate_move_left(keys_pressed, left_s, left_AI);
        double right_move = generate_move_right(keys_pressed, right_s, right_AI);
        sliders_move(game, left_move, right_move, time_mult);

        //update game stat (position, speed, bounces, etc.)
        winner = game_update(game, time_mult);

        //redraw display
        frame_buffer_clear(fb);
        print_header(fb, left_s->lifes_count, right_s->lifes_count, left_AI, right_AI);
        print_game(fb, game, 25, 40);
        redraw_display(fb);
    }

    slider_free(left_s);
    slider_free(right_s);
    game_free(game);

    if (winner == 0 || winner == -2)
        return winner;
    //color leds according to who won
    if (winner == -1)
    {
        left_led = 0x880000;
        score_right++;
    }
    else if (winner == 1)
    {
        right_led = 0x880000;
        score_left++;
    }
    update_leds(fb, left_led, right_led);

    //show game over menu
    int menu_ret = show_menu(fb, game_over_menu);
    if (menu_ret == -1 || menu_ret == 1)
    {
        return -2;
    }

    return winner;
}

double generate_move_left(unsigned int keys_pressed, slider_t *slider, char AI_controlled)
{
    if (AI_controlled) //return automated move based on target position
        return slider_generate_move(slider);

    double move = 0.0; //-1 if player wants to go up 1 if down
    if (keys_pressed & P_W)
        move -= 1.0;
    if (keys_pressed & P_S)
        move += 1.0;

    return move;
}

double generate_move_right(unsigned int keys_pressed, slider_t *slider, char AI_controlled)
{
    if (AI_controlled) //return automated move based on target position
        return slider_generate_move(slider);

    double move = 0.0; //-1 if player wants to go up 1 if down
    if (keys_pressed & P_ARROW_UP)
        move -= 1.0;
    if (keys_pressed & P_ARROW_DOWN)
        move += 1.0;

    return move;
}

slider_t *create_slider(int difficulty, char AI_controlled)
{
    int init_pos = 160;
    int height = 60;
    double speed = 85;
    int life_count = 0;

    switch (difficulty)
    {
    case 1: //easy
        height = 75;
        speed = AI_controlled ? 50 : 160;
        life_count = AI_controlled ? 1 : 5;
        break;
    default:
    case 2: //normal
        height = 60;
        speed = AI_controlled ? 75 : 160;
        life_count = AI_controlled ? 1 : 3;
        break;
    case 3: //hard
        height = 50;
        speed = AI_controlled ? 150 : 160;
        life_count = AI_controlled ? 1 : 2;
        break;
    }

    return slider_init(height, init_pos, speed, AI_controlled * difficulty, life_count);
}

game_t *create_game(int difficulty, slider_t *left_s, slider_t *right_s)
{
    double speed;
    double speed_change;
    double speed_cap;
    //random direction in range (-45°; +45°)
    double direction = ((double)rand() / (double)RAND_MAX) * 1.5708 - 0.7854;

    switch (difficulty)
    {
    case 1: //easy
        speed = 150;
        speed_change = 2;
        speed_cap = 300;
        break;

    default:
    case 2: //normal
        speed = 200;
        speed_change = 5;
        speed_cap = 400;
        break;
    case 3: //hard
        speed = 250;
        speed_change = 5;
        speed_cap = 800;
        break;
    }

    game_t *game = game_init(430, 268, speed, speed_change, speed_cap,
                             direction, 35, 150, left_s, right_s);
    //update sliders positions for AI controlled sliders
    slider_update_target_pos(right_s, game);
    slider_update_target_pos_after_play(left_s, game);
    return game;
}
