/*******************************************************************
  APO semestral project file.
  Module with definitions of menu options and header that are used
  in the program.

  Vit Knobloch, Adam Loucky
  CTU FEE 2021
  
  license: any combination GPL, LGPL, MPL or BSD licenses

 *******************************************************************/

#include "menu.h"

char *main_menu_opts[] = {"PC vs PC", "Player vs PC", "Player vs Player", "Exit game"};
char *pause_menu_opts[] = {"Resume", "Restart", "Return to menu"};
char *game_over_menu_opts[] = {"Play again", "Return to menu"};
char *difficulty_menu_opts[] = {"Easy", "Normal", "Hard", "Return to menu"};

menu_t main_menu = {.option_count = 4, .options = main_menu_opts, .header = "Main menu"};
menu_t pause_menu = {.option_count = 3, .options = pause_menu_opts, .header = "Game paused"};
menu_t game_over_menu = {.option_count = 2, .options = game_over_menu_opts, .header = "Game over"};
menu_t difficulty_menu = {.option_count = 4, .options = difficulty_menu_opts, .header = "Select difficulty"};
