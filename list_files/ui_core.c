#include <stdio.h>
#include <string.h>
#include "ui_core.h"
#include "common.h"

#define COL_WIDTH 36
#define MAX_VISIBLE_ROWS 20

// --- COLORES ANSI ---
#define RESET     "\x1b[0m"
#define BOLD      "\x1b[1m"
#define DIM       "\x1b[2m"
#define BLUE      "\x1b[34m"
#define GREEN     "\x1b[32m"
#define CYAN      "\x1b[36m"
#define YELLOW    "\x1b[33m"
#define MAGENTA   "\x1b[35m"
#define INVERT    "\x1b[7m"
#define CLEAR_LN  "\033[K"

// Helper: Corta nombres largos y añade "..."
static const char* format_name(const char* name, int max_width) {
    static char buffer[128];
    int len = strlen(name);
    if (len <= max_width) return name;

    strncpy(buffer, name, max_width - 3);
    strcpy(buffer + (max_width - 3), "...");
    return buffer;
}

// Helper: Extrae solo el nombre de la carpeta de una ruta completa
static const char* get_folder_name(const char* path) {
    if (strcmp(path, "/") == 0) return "/";
    const char* last_slash = strrchr(path, '/');
    return (last_slash) ? last_slash + 1 : path;
}

// Helper: Determina el color según el tipo y si es oculto
static void apply_file_color(FileEntry *entry) {
    // 1. Si es oculto (empieza con punto), usamos DIM (gris/tenue)
    if (entry->name[0] == '.') {
        printf("%s", DIM);
    }
    // 2. Si no es oculto, color por tipo
    else {
        switch (entry->type) {
            case F_DIRECTORY: printf("%s", BLUE); break;
            case F_BIN_ELF: printf("%s", GREEN); break;
            case F_SCRIPT:    printf("%s", MAGENTA); break;
            default:          printf("%s", RESET); break;
        }
    }
}

void ui_init() {
    printf("\033[H\033[J"); // Limpiar pantalla completa
}

void ui_render(BrowserState *state) {
    // 1. Resetear cursor al inicio (evita parpadeo)
    printf("\033[H");

    // 2. ENCABEZADO
    printf(" %s%s%-36s%s | %s%s%-36s%s\n",
           BOLD, CYAN, state->has_previous ? get_folder_name(state->previous.path) : "---", RESET,
           BOLD, YELLOW, get_folder_name(state->current.path), RESET);
    printf("-------------------------------------+--------------------------------------%s\n", CLEAR_LN);

    // 3. RENDER DE FILAS
    for (int i = 0; i < MAX_VISIBLE_ROWS; i++) {

        // --- COLUMNA IZQUIERDA (Padre) ---
        if (state->has_previous && i < state->previous.count) {
            FileEntry *pe = &state->previous.entries[i];


            // Indicador de rastro
            if (i == state->previous.selected_index) printf("%s%s> %s", BOLD, GREEN, RESET);
            else printf("  ");

            apply_file_color(pe);
           printf("%-34s%s", format_name(pe->name, 34), RESET);







        } else {
            printf("%-36s", "");
        }

        printf(" | ");

        // --- COLUMNA DERECHA (Actual / Selección) ---
        int idx = state->current.scroll_offset + i;
        if (idx < state->current.count) {
            FileEntry *ce = &state->current.entries[idx];

            if (idx == state->current.selected_index) {
                // --- ARCHIVO SELECCIONADO ---
                // Usamos Invertido + Negrita, pero SIN color de archivo para legibilidad
                printf("%s%s %-35s %s", INVERT, BOLD, format_name(ce->name, 35), RESET);
            }
            else {
                // --- ARCHIVO NORMAL ---
                apply_file_color(ce);
                printf(" %-35s%s", format_name(ce->name, 35), RESET);
            }
        } else {
            printf("%-36s", "");
        }

        printf("%s\n", CLEAR_LN); // Limpia cualquier residuo de color al final de la línea
    }
    // 4. PIE DE PÁGINA (Barra de comandos y estado)
    printf("-------------------------------------+--------------------------------------%s\n", CLEAR_LN);
    printf("%s PATH: %-70s%s%s\n", DIM, format_name(state->current.path, 70), RESET, CLEAR_LN);

    printf("%s[FLECHAS]%s Nav %s[ENT]%s Abrir %s[ESC]%s Volver %s[H]%s Ocultos(%s) %s[Q]%s Salir%s",
           BOLD, RESET, BOLD, RESET, BOLD, RESET, BOLD, RESET,
           state->show_hidden ? "ON" : "OFF", BOLD, RESET, CLEAR_LN);

    fflush(stdout);
}

void ui_shutdown() {
    printf("\033[H\033[J"); // Limpiar al salir
}