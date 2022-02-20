/*******************************************************************
  APO semestral project file.
  Module for getting pressed keys for controlling the program and for
  setting the terminal to raw mode and reseting it to default mode.

  Vit Knobloch, Adam Loucky
  CTU FEE 2021
  
  license: any combination GPL, LGPL, MPL or BSD licenses

 *******************************************************************/

#ifndef __TERMINAL_CONTROLLER_H__
#define __TERMINAL_CONTROLLER_H__

#define P_ESCAPE 0x1
#define P_ENTER 0x2
#define P_ARROW_UP 0x4
#define P_ARROW_DOWN 0x8
#define P_W 0x10
#define P_S 0x20

/**
 * @brief Sets the terminal to raw mode and stores the original settings to restore them at exit
 */
void init_raw_mode();

/**
 * @brief Get the pressed keys
 * 
 * @return unsigned int - int with flags defined in this header (starting with 'P_')
 * which indicate the pressed and unpressed keys.
 */
unsigned int get_pressed_keys();

/**
 * @brief Restores the original terminal settings (is set to be called at exit)
 */
void end_raw_mode();

#endif