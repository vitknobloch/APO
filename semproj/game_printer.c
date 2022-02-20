/*******************************************************************
  APO semestral project file.
  Module for graphical printing od game in progress on graphical display
  of MZ_APO.

  Vit Knobloch, Adam Loucky
  CTU FEE 2021
  
  license: any combination GPL, LGPL, MPL or BSD licenses

 *******************************************************************/

#include "game_printer.h"

#define BALL_RADIUS 10
#define BOARD_WIDTH 10

void print_background(fb_t *fb, game_t *game, int x, int y);
void print_speed(fb_t *fb, game_t *game);
void print_header_lifes(fb_t *fb, int lifes_left, char lifes_rights);
void int_to_string(char *str, int num);
void print_header_center(fb_t *fb, char left_AI, char right_ai);

void print_game(fb_t *fb, game_t *game, int x, int y)
{
    print_speed(fb, game);            //update led strip
    print_background(fb, game, x, y); //print PONG in bg
    set_color(0xffff);
    //draw sliders
    draw_rectangle(
        fb,
        x - BOARD_WIDTH - BALL_RADIUS,
        y + game->left_slider->pos - game->left_slider->height / 2,
        BOARD_WIDTH,
        game->left_slider->height);
    draw_rectangle(
        fb,
        x + game->width + BALL_RADIUS,
        y + game->right_slider->pos - game->right_slider->height / 2,
        BOARD_WIDTH,
        game->right_slider->height);
    //draw ball
    draw_circle(fb, (int)game->x_pos + x, (int)game->y_pos + y, BALL_RADIUS);
}

void print_background(fb_t *fb, game_t *game, int x, int y)
{
    set_font(&font_winFreeSystem14x16);
    set_color(rgb_to_16bit(100, 100, 100));
    int text_x = x + (game->width / 2) - (get_string_width("PONG", 10) / 2);
    draw_string(fb, "PONG", text_x, y + 30, 10);
}

void print_speed(fb_t *fb, game_t *game)
{
    double speed_range = game->speed_cap - game->speed_init;
    double speed_up = game->speed - game->speed_init;
    int shift = 32 - (int)(0.2 + (32 * speed_up) / speed_range);
    uint32_t stripe = (0xffffffff << shift);
    update_led_stripe(fb, stripe);
}

void print_header(fb_t *fb, int lifes_left, int lifes_rights, char left_AI, char right_AI)
{
    //draw lines above and under game space
    draw_rectangle(fb, 0, 30, fb->width, 2);
    draw_rectangle(fb, 0, fb->height - 2, fb->width, 2);
    //print score and who is playing in header
    print_header_lifes(fb, lifes_left, lifes_rights);
    print_header_center(fb, left_AI, right_AI);
}

void print_header_lifes(fb_t *fb, int lifes_left, char lifes_rights)
{
    char left_str[5];
    char right_str[5];
    int_to_string(left_str, lifes_left);
    int_to_string(right_str, lifes_rights);
    //draw left side
    set_font(&font_special_characters);
    draw_char(fb, 1, 5, 0, 1);
    set_font(&font_rom8x16);
    draw_string(fb, left_str, 37, 2, 2);

    int right_x = fb->width - 37 - get_string_width(right_str, 2);
    set_font(&font_rom8x16);
    draw_string(fb, right_str, right_x, 2, 2);
    set_font(&font_special_characters);
    draw_char(fb, 1, fb->width - 35, 0, 1);
}

void print_header_center(fb_t *fb, char left_ai, char right_ai)
{
    char *player_str = "Player";
    char *ai_str = "Computer";
    char *separator_str = " vs ";
    set_font(&font_wTahoma_28_part0);
    draw_string_centered(fb, separator_str, 2, 1);
    int left_x = fb->width / 2 - 20 - get_string_width(left_ai ? ai_str : player_str, 1);
    draw_string(fb, left_ai ? ai_str : player_str, left_x, 2, 1);
    int right_x = fb->width / 2 + 20;
    draw_string(fb, right_ai ? ai_str : player_str, right_x, 2, 1);
}

void int_to_string(char *str, int num)
{
    //print '-' in front of negative numbers
    if (num < 0)
    {
        num *= -1;
        *(str++) = '-';
    }
    //special case for zero
    else if (num == 0)
    {
        *(str++) = '0';
        *str = '\0';
        return;
    }
    //print digit by digit
    int num_rest = num;
    for (int i = 10000; i > 0; i /= 10)
    {
        if (num / i)
        {
            *(str++) = '0' + num_rest / i;
        }
        num_rest %= i;
    }
    *str = '\0';
}