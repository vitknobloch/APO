/*******************************************************************
  APO semestral project main file base on project main function 
  template for MicroZed based MZ_APO board designed by Petr Porazil 
  at PiKRON

  main.c      - main file of the PONG game, includes main method

  Vit Knobloch, Adam Loucky
  CTU FEE 2021

  license: any combination GPL, LGPL, MPL or BSD licenses

 *******************************************************************/

#define _POSIX_C_SOURCE 200112L

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>

#include "mzapo_parlcd.h"
#include "mzapo_phys.h"
#include "mzapo_regs.h"

#include "frame_printer.h"
#include "terminal_controller.h"
#include "menu.h"
#include "game_runner.h"

//width and height  of display
#define WIDTH 480
#define HEIGHT 320

//menu definitions
extern menu_t main_menu;
extern menu_t difficulty_menu;

int main(int argc, char *argv[])
{
    printf("Application started\n");
    init_raw_mode(); //raw keyboard input

    //map physical memory for output
    unsigned char *display_membase = map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);
    unsigned char *rgb_led_membase = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
    parlcd_hx8357_init(display_membase);

    //create frame buffer
    fb_t *fb = frame_buffer_init(WIDTH, HEIGHT, display_membase, rgb_led_membase);
    int menu_res = 0;
    //run game
    while (menu_res != 3) //until choice is Exit game
    {
        frame_buffer_clear(fb);
        update_leds(fb, 0x0, 0x0);
        update_led_stripe(fb, 0x0);
        //show main menu and get choice
        menu_res = show_menu(fb, main_menu);
        //PC vs PC
        if (menu_res == 0)
        {
            run_games(fb, 3, 1, 1);
        }
        //Player vs PC
        else if (menu_res == 1)
        {
            frame_buffer_clear(fb);
            int difficulty = show_menu(fb, difficulty_menu); //difficulty choice
            if (difficulty < 3 && difficulty >= 0)
                run_games(fb, difficulty + 1, 0, 1);
        }
        //Player vs Player
        else if (menu_res == 2)
        {
            frame_buffer_clear(fb);
            int difficulty = show_menu(fb, difficulty_menu); //difficulty choice
            if (difficulty < 3 && difficulty >= 0)
                run_games(fb, difficulty + 1, 0, 0);
        }
    }

    frame_buffer_clear(fb);
    redraw_display(fb);
    update_leds(fb, 0x0, 0x0);
    frame_buffer_free(fb);

    printf("Application ended\n");

    return 0;
}
