//
// Created by fontes on 4/25/26.
//

#ifndef LIST_FILES_UI_CORE_H
#define LIST_FILES_UI_CORE_H

#include "nav_state.h"

// Limpia la pantalla y posiciona el cursor al inicio
void ui_init();

// Dibuja el estado completo (dos columnas)
void ui_render(BrowserState *state);

// Restaura la terminal (limpia antes de salir)
void ui_shutdown();



#endif //LIST_FILES_UI_CORE_H