/*******************************************************************
  APO semestral project file.
  Module for drawing object on graphical display connected to MZ_APO

  Vit Knobloch, Adam Loucky
  CTU FEE 2021
  
  license: any combination GPL, LGPL, MPL or BSD licenses

 *******************************************************************/

#ifndef __FRAME_PRINTER_H__
#define __FRAME_PRINTER_H__

#include <stdint.h>

/**
 * @brief Struct with information about frame, 
 * output peripherals and framebuffer.
 */
typedef struct
{
    int width;                      //display's width
    int height;                     //display's height
    uint16_t *pixels;               //pointer to array of pixels
    unsigned char *display_membase; //memory adress of display controller
    unsigned char *led_membase;     //memory adress of RGB LEDs
} fb_t;

/**
 * @brief Allocates memory for frame buffer, initializes it's values and returns it.
 * 
 * @param width width of the screen
 * @param height height of the screen
 * @param display_membase pointer to parlcd membase
 * @param led_membase pointer to SPILED membase
 * @return fb_t* pointer to the newly created frame buffer
 */
fb_t *frame_buffer_init(int width, int height, unsigned char *display_membase, unsigned char *led_membase);

/** 
 * @brief Sets the whole frame to black.
 * 
 * @param fb frame buffer to reset. */
void frame_buffer_clear(fb_t *fb);

/**
 * @brief Draws a single pixel of current color to given position of frame buffer.
 *          (does nothing if given position is outside of frame)
 * 
 * @param fb frame buffer to draw to.
 * @param x x coordinate of the pixel.
 * @param y y coordinate of the pixel.
 */
void draw_pixel(fb_t *fb, int x, int y);

/**
 * @brief Draws a square of size 'scale x scale' with top left corner on the given position.
 * 
 * @param fb frame buffer to draw to.
 * @param x x coordinate of left of the scaled pixel
 * @param y y coordinate of top of the scaled pixel
 * @param scale size (scale x scale) in pixels of the printed square
 */
void draw_pixel_scaled(fb_t *fb, int x, int y, int scale);

/** 
 * @brief Draws a rectangle of size 'w x h' with top left corner on the given position. 
 * 
 * @param fb frame buffer to draw to.
 * @param x x coordinate of left of the rectangle
 * @param y y coordinate of top of the rectangle
 * @param w width of the rectangle
 * @param h height of the rectangle
 */
void draw_rectangle(fb_t *fb, int x, int y, int w, int h);

/**
 * @brief Draws a rectangle of size 'w x h' with top left corner on the given position
 * and rounded corners of radius r 
 * 
 * @param fb frame buffer to draw to.
 * @param x x coordinate of left of the rectangle
 * @param y y coordinate of top of the rectangle
 * @param w width of the rectangle
 * @param h height of the rectangle
 * @param r radius of the corners' roundness
 */
void draw_rounded_rectangle(fb_t *fb, int x, int y, int w, int h, int r);

/** 
 * @brief Draws circle of radius 'r' with center on the given position
 * 
 * @param fb frame buffer to draw to.
 * @param x x coordinate of the circles center
 * @param y y coordinate of the circles center
 * @param r the coordinates radius
 */
void draw_circle(fb_t *fb, int x, int y, int r);

/** 
 * @brief Sets color to use for graphics printing to given color 
 * 
 * @param color color to set the printer to
 */
void set_color(uint16_t color);

/** 
 * @brief Takes in RGB color and returns it's 16bit form.
 * 
 * @param r red color rgb value
 * @param g green color rgb value
 * @param b blue color rgb value
 */
uint16_t rgb_to_16bit(char r, char g, char b);

/** 
 * @brief Free's memory allocated for given frame buffer.
 * 
 * @param fb Frame buffer to draw to.
 */
void frame_buffer_free(fb_t *fb);

/** 
 * @brief Renews frame - draws the frame buffer on the display. 
 * 
 * @param fb Frame buffer to draw to display.
 */
void redraw_display(fb_t *fb);

/**
 * @brief Sets the RGB leds on the MZ_APO kit to given colors
 * 
 * @param fb Frame buffer with SPILED membase
 * @param left color of left LED
 * @param right color of right LED
 */
void update_leds(fb_t *fb, uint32_t left, uint32_t right);

/**
 * @brief Sets the led stripe on the MZ_APO kit to given value
 * 
 * @param fb Frame buffer with SPILED membase
 * @param strip value to diplay on the LED stripe
 */
void update_led_stripe(fb_t *fb, uint32_t strip);

#endif