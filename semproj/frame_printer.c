/*******************************************************************
  APO semestral project file.
  Module for drawing object on graphical display connected to MZ_APO

  Vit Knobloch, Adam Loucky
  CTU FEE 2021
  
  license: any combination GPL, LGPL, MPL or BSD licenses

 *******************************************************************/

#include "frame_printer.h"
#include "mzapo_parlcd.h"
#include "mzapo_regs.h"
#include "my_malloc.h"

#include <stdint.h>
#include <string.h>

uint16_t current_color = 0x0000;

fb_t *frame_buffer_init(int width, int height, unsigned char *display_membase, unsigned char *led_membase)
{
    fb_t *ret = allocate_memory(sizeof(fb_t));
    if (!ret)
    {
        return NULL;
    }

    ret->pixels = allocate_memory_calloc(width * height, sizeof(uint16_t));

    ret->height = height;
    ret->width = width;
    ret->display_membase = display_membase;
    ret->led_membase = led_membase;

    return ret;
}

void frame_buffer_free(fb_t *fb)
{
    deallocate_memory((void **)&fb->pixels);
    deallocate_memory((void **)&fb);
}

void frame_buffer_clear(fb_t *fb)
{
    memset(fb->pixels, 0, fb->height * fb->width * sizeof(uint16_t));
}

void draw_pixel(fb_t *fb, int x, int y)
{
    if (x < 0 || y < 0 || x >= fb->width || y >= fb->height)
        return;

    fb->pixels[y * fb->width + x] = current_color;
}

void draw_pixel_scaled(fb_t *fb, int x, int y, int scale)
{
    for (int i = 0; i < scale; i++)
    {
        for (int j = 0; j < scale; j++)
        {
            draw_pixel(fb, x + i, y + j);
        }
    }
}

void draw_rectangle(fb_t *fb, int x, int y, int w, int h)
{
    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < h; j++)
        {
            draw_pixel(fb, x + i, y + j);
        }
    }
}

void draw_rounded_rectangle(fb_t *fb, int x, int y, int w, int h, int r)
{
    draw_rectangle(fb, x + r, y, w - 2 * r, h);
    draw_rectangle(fb, x, y + r, r, h - 2 * r);
    draw_rectangle(fb, x + w - r, y + r, r, h - 2 * r);

    draw_circle(fb, x + r, y + r, r);
    draw_circle(fb, x + r, y + h - r, r);
    draw_circle(fb, x + w - r, y + r, r);
    draw_circle(fb, x + w - r, y + h - r, r);
}

void draw_circle(fb_t *fb, int x, int y, int r)
{
    for (int i = -r; i <= r; i++)
    {
        for (int j = -r; j <= r; j++)
        {
            if (i * i + j * j <= r * r)
            {
                draw_pixel(fb, x + i, y + j);
            }
        }
    }
}

void set_color(uint16_t color)
{
    current_color = color;
}

uint16_t rgb_to_16bit(char r, char g, char b)
{
    r = r >> 3;
    g = g >> 2;
    b = b >> 3;
    uint16_t ret = (r << 11) | (g << 5) | (b);
    return ret;
}

void redraw_display(fb_t *fb)
{
    parlcd_write_cmd(fb->display_membase, 0x2c);

    for (int i = 0; i < fb->height * fb->width; i++)
    {
        parlcd_write_data(fb->display_membase, fb->pixels[i]);
    }
}

void update_leds(fb_t *fb, uint32_t left, uint32_t right)
{
    *(volatile uint32_t *)(fb->led_membase + SPILED_REG_LED_RGB1_o) = left;
    *(volatile uint32_t *)(fb->led_membase + SPILED_REG_LED_RGB2_o) = right;
}

void update_led_stripe(fb_t *fb, uint32_t strip)
{
    *(volatile uint32_t *)(fb->led_membase + SPILED_REG_LED_LINE_o) = strip;
}
