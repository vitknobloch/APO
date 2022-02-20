/*******************************************************************
  APO semestral project file.
  Module for printing fonts described by a font_descriptor_t

  Vit Knobloch, Adam Loucky
  CTU FEE 2021
  
  license: any combination GPL, LGPL, MPL or BSD licenses

 *******************************************************************/

#include "font_printer.h"
#include "frame_printer.h"
#include "font_types.h"

int get_char_width(char c);
const font_bits_t *get_char_bitmap_ptr(char c);

font_descriptor_t *font = &font_winFreeSystem14x16;

int get_char_width(char c)
{
    if (font->width)
    {
        int pos = c - font->firstchar;
        if (pos >= 0 && pos < font->size)
        {
            return font->width[pos];
        }
    }
    return font->maxwidth;
}

const font_bits_t *get_char_bitmap_ptr(char c)
{
    int pos = c - font->firstchar;
    if (pos >= 0 && pos < font->size)
    {
        if (font->offset)
        {
            return &(font->bits[font->offset[pos]]);
        }
        else
        {
            const int width = (font->maxwidth + 15) / (sizeof(font_bits_t) * 8);
            const int height = font->height;
            return &font->bits[width * height * pos];
        }
    }
    return font->bits;
}

int draw_char(fb_t *fb, char c, int x, int y, int scale)
{
    const int width = get_char_width(c);
    //number of font_bits_t that describe single line of the letter
    const int font_bits_width = (width + 8 * sizeof(font_bits_t) - 1) / (sizeof(font_bits_t) * 8);
    const int height = font->height;
    const font_bits_t *bits = get_char_bitmap_ptr(c);

    for (int v = 0; v < height; v++) //for each  line of pixels in letter
    {
        for (int b = 0; b < font_bits_width; b++)
        {
            int points_in_bits = width - b * 8 * sizeof(font_bits_t);
            if (points_in_bits > sizeof(font_bits_t) * 8)
                points_in_bits = sizeof(font_bits_t) * 8;
            //how many bits are used from this font_bits_t descriptor
            for (int h = 0; h < points_in_bits; h++)
            {
                if ((*bits << h) & 0x8000)
                {
                    const int h_pos = h + b * sizeof(font_bits_t) * 8;
                    draw_pixel_scaled(fb, x + h_pos * scale, y + v * scale, scale);
                }
            }
            ++bits;
        }
    }

    return width * scale;
}

void draw_string(fb_t *fb, char *str, int x, int y, int scale)
{
    int cur_x = x;
    while (*str != '\0' && cur_x < fb->width)
    {
        cur_x += draw_char(fb, *str, cur_x, y, scale);
        ++str;
    }
}

int get_string_width(char *str, int scale)
{
    int width = 0;
    while (*str != '\0')
    {
        width += get_char_width(*str);
        str++;
    }
    return width * scale;
}

void draw_string_centered(fb_t *fb, char *str, int y, int scale)
{
    int width = get_string_width(str, scale);
    int x = (fb->width / 2) - (width / 2);
    draw_string(fb, str, x, y, scale);
}

void set_font(font_descriptor_t *font_descriptor)
{
    font = font_descriptor;
}
