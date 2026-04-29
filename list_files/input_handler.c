//
// Created by fontes on 4/25/26.
//
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include "input_handler.h"


static struct termios original_Conf;

void input_init() {
    struct termios newConf;

    if (tcgetattr(STDIN_FILENO,  &original_Conf)==-1) return;

    newConf = original_Conf;


    newConf.c_lflag&=~(ECHO | ICANON);
    newConf.c_cc[VMIN] = 0;
    newConf.c_cc[VTIME] = 1;
    tcsetattr(STDIN_FILENO, TCSANOW, &newConf);

}


void input_restore() {
    tcsetattr(STDIN_FILENO, TCSANOW, &original_Conf);

}


Command input_get_command() {
    unsigned char ch;

    while (read(STDIN_FILENO, &ch, 1) == 0);

    if (ch == 'q' || ch == 'Q') return CMD_QUIT;
    if (ch == '\n' || ch == '\r') return CMD_ENTER;

    //ESC sequency
    if (ch == 27) {
        unsigned char seq[2];


        if (read(STDIN_FILENO, &seq[0], 1) == 0) return CMD_BACK;
        if (read(STDIN_FILENO, &seq[1], 1) == 0) return CMD_BACK;

        if (seq[0] == '[') {
            if (seq[1] == 'A') return CMD_UP;
            if (seq[1] == 'B') return CMD_DOWN;
            if (seq[1] == 'C') return CMD_ENTER;
            if (seq[1] == 'D') return CMD_BACK;
            return CMD_NONE;
        }
        return CMD_BACK;
    }
    if (ch=='h' || ch=='H') return CMD_TOGGLE_HIDDEN;

    return CMD_NONE;
}

