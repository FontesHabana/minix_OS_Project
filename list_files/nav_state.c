//
// Created by fontes on 4/25/26.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "nav_state.h"
#include "fs_engine.h"

int nav_init(BrowserState *state, const char *start_path) {
    // 1. Cargar la carpeta actual
    state->current.count = 0;
    state->previous.count = 0;
    state->has_previous = false;
    fs_get_contents(start_path, &state->current,state->show_hidden);

    // 2. Cargar el padre para la columna izquierda
    char parent_path[1024];
    snprintf(parent_path, sizeof(parent_path), "%s/..", start_path);

    if (fs_get_contents(parent_path, &state->previous,state->show_hidden) == 0) {
        state->has_previous = true;

        // TRUCO DE INGENIERÍA:
        // Para que la columna izquierda marque dónde estamos,
        // debemos buscar en qué índice de 'previous' está 'current'.
        const char* current_folder_name = strrchr(start_path, '/');
        if (current_folder_name) {
            current_folder_name++; // saltar el /
            for (int i = 0; i < state->previous.count; i++) {
                if (strcmp(state->previous.entries[i].name, current_folder_name) == 0) {
                    state->previous.selected_index = i;
                    break;
                }
            }
        }
    } else {
        state->has_previous = false;
    }
    return 0;
}

void nav_move_cursor(BrowserState *state, int direction) {
    DirectoryLevel *cur = &state->current;
    int max_visible = 20; // Lo que cabe en tu pantalla

    cur->selected_index += direction;

    // Validar límites
    if (cur->selected_index < 0) cur->selected_index = 0;
    if (cur->selected_index >= cur->count) cur->selected_index = cur->count - 1;

    // Lógica de Scroll
    if (cur->selected_index < cur->scroll_offset) {
        // Si el cursor sube más allá de lo visible
        cur->scroll_offset = cur->selected_index;
    }
    else if (cur->selected_index >= cur->scroll_offset + max_visible) {
        // Si el cursor baja más allá de lo visible
        cur->scroll_offset = cur->selected_index - max_visible + 1;
    }
}



int nav_enter_directory(BrowserState *state) {
    int idx = state->current.selected_index;
    if (state->current.count == 0) return -1;

    FileEntry *selected = &state->current.entries[idx];
    if (selected->type != F_DIRECTORY) return -1;

    // 1. Construir la ruta nueva ANTES de mover nada
    char new_path[1024];
    snprintf(new_path, sizeof(new_path), "%s/%s", state->current.path, selected->name);

    // 2. Liberar la columna izquierda vieja
    fs_free_contents(&state->previous);

    // 3. TRANSFERENCIA DE PROPIEDAD:
    // Movemos los datos de 'current' a 'previous'
    state->previous = state->current;
    state->has_previous = true;

    // 4. MUY IMPORTANTE: "Desconectar" el puntero de current
    // Así, cuando fs_get_contents llame a free(), no borrará lo que ahora es 'previous'
    state->current.entries = NULL;
    state->current.count = 0;

    // 5. Cargar la nueva carpeta en current
    return fs_get_contents(new_path, &state->current, state->show_hidden);
}


int nav_back(BrowserState *state) {
    if (strcmp(state->current.path, "/") == 0) return -1;

    // 1. Guardamos la ruta a la que queremos ir (el padre de la actual)
    char target_path[1024];
    strncpy(target_path, state->previous.path, 1023);

    // 2. Liberamos TODA la memoria actual para empezar de cero
    // Esto evita punteros duplicados o "fantasmas"
    nav_cleanup(state);

    // 3. Re-inicializamos el estado desde la ruta destino
    // Llamar a nav_init es la forma más limpia de reconstruir las dos columnas
    return nav_init(state, target_path);
}


void nav_cleanup(BrowserState *state) {
    fs_free_contents(&state->current);
    fs_free_contents(&state->previous);
}

void nav_toggle_hidden(BrowserState *state) {
    state->show_hidden = !state->show_hidden;

    fs_free_contents(&state->current);
    fs_get_contents(state->current.path, &state->current,state->show_hidden);

    if (state->has_previous) {
        fs_free_contents(&state->previous);
        fs_get_contents(state->previous.path, &state->previous,state->show_hidden);

    }
}