/*******************************************************************
  APO semestral project file.
  Module for displaying menus, where the user can navigate through and
  select from predefined options.

  Vit Knobloch, Adam Loucky
  CTU FEE 2021
  
  license: any combination GPL, LGPL, MPL or BSD licenses

 *******************************************************************/

#ifndef __MENU_H__
#define __MENU_H__

#include "frame_printer.h"

/**
 * @brief Struct with information about a menu, it's header and options
 */
typedef struct
{
    int option_count; //number of options in the menu
    char **options;   //array of strings to represent the options
    char *header;     //string to print in the header of the menu
} menu_t;

/**
 * @brief Displays menu with it's options and header and return the persons choice
 * 
 * @param fb frame buffer to display the menu on
 * @param menu menu struct that contains the menu option and header settings
 * @return int the index of choice the person made (or -1 on ESC)
 */
int show_menu(fb_t *fb, menu_t menu);

#endif