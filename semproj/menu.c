/*******************************************************************
  APO semestral project file.
  Module for displaying menus, where the user can navigate through and
  select from predefined options.

  Vit Knobloch, Adam Loucky
  CTU FEE 2021
  
  license: any combination GPL, LGPL, MPL or BSD licenses

 *******************************************************************/

#include "menu.h"
#include "font_printer.h"
#include "font_types.h"
#include "terminal_controller.h"

#include <stdio.h>

//color definitions
#define DESELECT_BG 0x0000
#define DESELECT_FG 0xdefb
#define DESELECT_BORDER 0x8410
#define SELECTED_BG 0x0000
#define SELECTED_FG 0xffff
#define SELECTED_BORDER 0xffff
#define HEADER_FG 0xffff

void draw_menu(fb_t *fb, menu_t menu, int selected);

int show_menu(fb_t *fb, menu_t menu)
{
    unsigned int last_pressed_keys = get_pressed_keys();
    unsigned int new_pressed_keys = last_pressed_keys;
    unsigned int pressed_keys = new_pressed_keys & (last_pressed_keys ^ new_pressed_keys);

    int selected = 0;
    while (!(pressed_keys & P_ENTER))
    {
        if (pressed_keys & (P_W | P_ARROW_UP))
            selected = (selected + menu.option_count - 1) % menu.option_count;
        if (pressed_keys & (P_S | P_ARROW_DOWN))
            selected = (selected + 1) % menu.option_count;
        if (pressed_keys & P_ESCAPE)
            return -1;

        draw_menu(fb, menu, selected);
        last_pressed_keys = new_pressed_keys;
        new_pressed_keys = get_pressed_keys();
        pressed_keys = new_pressed_keys & (last_pressed_keys ^ new_pressed_keys);
    }

    return selected;
}

void draw_menu(fb_t *fb, menu_t menu, int selected)
{
    //print header
    set_color(HEADER_FG);
    set_font(&font_wTahoma_28_part0);
    draw_string_centered(fb, menu.header, 35, 2);

    int y = 75 + (fb->height - 75 - 37 * menu.option_count) / 2;
    for (int i = 0; i < menu.option_count; i++)
    {
        //Draw border
        set_color(i == selected ? SELECTED_BORDER : DESELECT_BORDER);
        draw_rounded_rectangle(fb, 40, y, fb->width - 80, 34, 10);
        //Draw background
        set_color(i == selected ? SELECTED_BG : DESELECT_BG);
        draw_rounded_rectangle(fb, 43, y + 3, fb->width - 86, 28, 9);
        //Print text
        set_color(i == selected ? SELECTED_FG : DESELECT_FG);
        draw_string_centered(fb, menu.options[i], y + 3, 1);
        y += 37;
    }
    redraw_display(fb);
}