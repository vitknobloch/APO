#include "font_types.h"

static font_bits_t special_bits[] = {
    /* Character '♥' 0x0001  [ 30x30 ] */
    0x0000, 0x0000, /* |                              | */
    0x0000, 0x0000, /* |                              | */
    0x0000, 0x0000, /* |                              | */
    0x0000, 0x0000, /* |                              | */
    0x0000, 0x0000, /* |                              | */
    0x00F0, 0x1E00, /* |        ****       ****       | */
    0x07F8, 0x3FC0, /* |     ********     ********    | */
    0x07F8, 0x3FC0, /* |     ********     ********    | */
    0x1FFE, 0xFFF0, /* |   ************ ************  | */
    0x1FFE, 0xFFF0, /* |   ************ ************  | */
    0x3FFF, 0xFFF8, /* |  *************************** | */
    0x3FFF, 0xFFF8, /* |  *************************** | */
    0x3FFF, 0xFFF8, /* |  *************************** | */
    0x3FFF, 0xFFF8, /* |  *************************** | */
    0x3FFF, 0xFFF8, /* |  *************************** | */
    0x1FFF, 0xFFF0, /* |   *************************  | */
    0x1FFF, 0xFFF0, /* |   *************************  | */
    0x1FFF, 0xFFF0, /* |   *************************  | */
    0x0FFF, 0xFFE0, /* |    ***********************   | */
    0x0FFF, 0xFFE0, /* |    ***********************   | */
    0x03FF, 0xFF80, /* |      *******************     | */
    0x03FF, 0xFF80, /* |      *******************     | */
    0x007F, 0xFC00, /* |         *************        | */
    0x007F, 0xFC00, /* |         *************        | */
    0x007F, 0xFC00, /* |         *************        | */
    0x000F, 0xC000, /* |            *******           | */
    0x000F, 0xC000, /* |            *******           | */
    0x0003, 0x8000, /* |              ***             | */
    0x0003, 0x8000, /* |              ***             | */
    0x0001, 0x0000, /* |               *              | */
};

static unsigned char special_width[] = {
    30, /*   (0x1) */
};

font_descriptor_t font_special_characters = {
    "SpecialCharactersForAPOsemproj",
    32,
    30,
    10,
    1,
    1,
    special_bits,
    0 /*winFreeSystem14x16_offset*/,
    special_width,
};