/*******************************************************************
  APO semestral project file.
  Module for printing fonts described by a font_descriptor_t

  Vit Knobloch, Adam Loucky
  CTU FEE 2021
  
  license: any combination GPL, LGPL, MPL or BSD licenses

 *******************************************************************/

#ifndef __FONT_PRINTER_H__
#define __FONR_PRINTER_H__

#include "frame_printer.h"
#include "font_types.h"

/**
 * @brief Draws scaled character with top left corner at (x, y)
 * 
 * @param fb frame buffer to print to
 * @param c character to print
 * @param x x coordinate of left side of the letter
 * @param y y coordinate of top side of the letter
 * @param scale scale of the printout
 * @return int width of the printed sclaed charater
 */
int draw_char(fb_t *fb, char c, int x, int y, int scale);

/**
 * @brief Draws scaled string with top left corner at (x, y)
 * 
 * @param fb frame buffer to print to
 * @param str string to print
 * @param x x coordinate of left side of the firts letter
 * @param y y coordinate of top side of the first letter
 * @param scale scale of the printout
 */
void draw_string(fb_t *fb, char *str, int x, int y, int scale);

/**
 * @brief Draws scaled string horizontally centered with top edge at height y
 * 
 * @param fb frame buffer to print to
 * @param str string to print
 * @param y y coordinate of top side of the first letter
 * @param scale scale of the printout
 */
void draw_string_centered(fb_t *fb, char *str, int y, int scale);

/**
 * @brief Get the width of the scaled string if printed
 * 
 * @param str string to get width of
 * @param scale scale of the printout
 * @return int - pixel width of the printout
 */
int get_string_width(char *str, int scale);

/**
 * @brief Set the active font to the given font
 * 
 * @param font_descriptor font to set
 */
void set_font(font_descriptor_t *font_descriptor);

#endif
