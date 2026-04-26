//
// Created by fontes on 4/25/26.
//

#ifndef LIST_FILES_INPUT_HANDLER_H
#define LIST_FILES_INPUT_HANDLER_H

// Definimos comandos abstractos para que el resto del programa no sepa de teclados
typedef enum {
    CMD_NONE,
    CMD_UP,
    CMD_DOWN,
    CMD_ENTER,
    CMD_BACK, // Para la tecla ESC
    CMD_QUIT,  // Para una tecla de salida, ej. 'q'
    CMD_TOGGLE_HIDDEN,
} Command;

/*
 * Prepara la terminal para leer teclas una a una (Modo Raw).
 * Desactiva el buffering de línea y el eco en pantalla.
 */
void input_init();

/*
 * Restaura la terminal a su estado original.
 * Debe llamarse siempre antes de que el programa termine.
 */
void input_restore();

/*
 * Lee el teclado y traduce las secuencias de escape a comandos.
 * Esta función se bloquea hasta que el usuario presiona una tecla.
 */
Command input_get_command();


#endif //LIST_FILES_INPUT_HANDLER_H