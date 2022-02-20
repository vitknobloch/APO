/*******************************************************************
  APO semestral project file.
  Module for getting pressed keys for controlling the program and for
  setting the terminal to raw mode and reseting it to default mode.

  Vit Knobloch, Adam Loucky
  CTU FEE 2021
  
  license: any combination GPL, LGPL, MPL or BSD licenses

 *******************************************************************/

#include "terminal_controller.h"
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <linux/keyboard.h>
#include <linux/kd.h>
#include <fcntl.h>
#include <sys/ioctl.h>

#include <stdio.h>

/** original terminal properties to restore */
struct termios original_terminal;

/** returnes pressed key from terminal or 0 if there is no key pressed. */
char get_pressed_key();

void init_raw_mode()
{
    //store original terminal attributes
    tcgetattr(STDIN_FILENO, &original_terminal);
    atexit(end_raw_mode);

    //copy them and modify
    struct termios raw_terminal = original_terminal;
    raw_terminal.c_lflag &= ~(ECHO | ICANON); //disable echo and buffering
    raw_terminal.c_cc[VMIN] = 0;
    raw_terminal.c_cc[VTIME] = 0;
    raw_terminal.c_ispeed = B3000000;

    //set modified attributes to the terminal
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw_terminal);
}

char get_pressed_key()
{
    char c;
    int read_count = read(STDIN_FILENO, &c, 1);
    if (read_count == 1)
    {
        return c;
    }
    return 0;
}

unsigned int get_pressed_keys()
{
    unsigned int ret = 0;
    char key;

    int escape_seq = 0;
    while ((key = get_pressed_key()))
    {
        switch (key)
        {
        case 'w':
        case 'W':
            ret |= P_W;
            break;
        case 's':
        case 'S':
            ret |= P_S;
            break;
        case 10: //ENTER
            ret |= P_ENTER;
            break;
        case 27: //ESCAPE
            escape_seq = 1;
            break;
        case 91: //ESCAPE SEQUENCE CHAR
            if (escape_seq == 1)
                escape_seq = 2;
            break;
        case 65: //ARROW UP
            if (escape_seq == 2)
            {
                ret |= P_ARROW_UP;
                escape_seq = 0;
            }
            break;
        case 66: //ARROW DOWN
            if (escape_seq == 2)
            {
                ret |= P_ARROW_DOWN;
                escape_seq = 0;
            }
            break;
        }

        if (key != 91 && key != 27 && escape_seq == 1)
        {
            escape_seq = 0;
            ret |= P_ESCAPE;
        }
    }
    if (escape_seq == 1)
    {
        ret |= P_ESCAPE;
    }
    return ret;
}

void end_raw_mode()
{
    //restore original terminal attributes on the terminal
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &original_terminal);
}