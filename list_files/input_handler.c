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

    //Asignar conf vieja a nueva
    newConf = original_Conf;
    //Modificar para leer caracter a caracter y no escribir
    newConf.c_lflag&=~(ECHO | ICANON);
    newConf.c_cc[VMIN] = 0;  // No bloquear indefinidamente
    newConf.c_cc[VTIME] = 1; // Esperar 0.1s máximo
    tcsetattr(STDIN_FILENO, TCSANOW, &newConf);

}

/*
 * Restaura la terminal a su estado original.
 * Debe llamarse siempre antes de que el programa termine.
 */
void input_restore() {
    tcsetattr(STDIN_FILENO, TCSANOW, &original_Conf);

}

/*
 * Lee el teclado y traduce las secuencias de escape a comandos.
 * Esta función se bloquea hasta que el usuario presiona una tecla.
 */
Command input_get_command() {
    unsigned char ch;

    while (read(STDIN_FILENO, &ch, 1) == 0);

    if (ch == 'q' || ch == 'Q') return CMD_QUIT;
    if (ch == '\n' || ch == '\r') return CMD_ENTER;

    if (ch == 27) { // Empezó una secuencia de Escape
        unsigned char seq[2];

        // Intentamos leer los siguientes dos bytes con el timeout de 0.1s
        if (read(STDIN_FILENO, &seq[0], 1) == 0) return CMD_BACK; // Era ESC solo
        if (read(STDIN_FILENO, &seq[1], 1) == 0) return CMD_BACK; // Secuencia rota, tratar como ESC

        if (seq[0] == '[') {
            if (seq[1] == 'A') return CMD_UP;
            if (seq[1] == 'B') return CMD_DOWN;
            return CMD_NONE;
        }
        return CMD_BACK;
    }
    if (ch=='h' || ch=='H') return CMD_TOGGLE_HIDDEN;

    return CMD_NONE;
}

