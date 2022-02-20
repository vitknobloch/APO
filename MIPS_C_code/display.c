#include <stdint.h>

#define LCD_FB_START 0xffe00000
#define LCD_FB_END 0xffe4afff
#define COLOR 0x8888

int _start(){

    volatile uint16_t *first_pix = (volatile uint16_t *)LCD_FB_START;

    volatile uint16_t* last_pix = (volatile uint16_t*)LCD_FB_END;

    volatile uint16_t *cur_pix = first_pix;

    for(;cur_pix < last_pix; cur_pix++){
        *cur_pix = COLOR;
    }

    return 0;
}