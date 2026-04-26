//
// Created by fontes on 4/25/26.
//

#ifndef LIST_FILES_NAV_STATE_H
#define LIST_FILES_NAV_STATE_H



#include "common.h"


typedef struct {
    DirectoryLevel current;
    DirectoryLevel previous;
    bool has_previous;
    bool show_hidden;
} BrowserState;

// Inicializa el navegador en una ruta dada
int nav_init(BrowserState *state, const char *start_path);

// Mueve el cursor arriba/abajo
void nav_move_cursor(BrowserState *state, int direction); // -1 arriba, 1 abajo

// Entra en el directorio seleccionado actualmente
int nav_enter_directory(BrowserState *state);

// Vuelve al directorio anterior (Esc)
int nav_back(BrowserState *state);

// Limpia toda la memoria al salir
void nav_cleanup(BrowserState *state);

void nav_toggle_hidden(BrowserState *state);




#endif //LIST_FILES_NAV_STATE_H