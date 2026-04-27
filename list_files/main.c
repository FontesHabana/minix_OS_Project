#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include "common.h"
#include "fs_engine.h"
#include "input_handler.h"
#include "nav_state.h"
#include "ui_core.h"
#include "executor.h"







int main(int argc, char *argv[]) {
    //Secure singleton
    if (getenv("LF_ACTIVE") != NULL) {
        fprintf(stderr, "Error: The explorer is active.\n");
        return 1;
    }
    putenv("LF_ACTIVE=1");



    BrowserState state;
    memset(&state, 0, sizeof(BrowserState));

    char start_path[1024];
    if (argc > 1) strncpy(start_path, argv[1], 1023);
    else getcwd(start_path, 1024);

    if (nav_init(&state, start_path) != 0) return 1;

    input_init();
    ui_init();
    bool running = true;

    while (running) {
        ui_render(&state);
        Command cmd = input_get_command();

        switch (cmd) {
            case CMD_UP:   nav_move_cursor(&state, -1); break;
            case CMD_DOWN: nav_move_cursor(&state, 1);  break;
            case CMD_ENTER: {
                int idx = state.current.selected_index;
                if (state.current.count > 0) {
                    FileEntry *sel = &state.current.entries[idx];
                    if (sel->type == F_DIRECTORY) {
                        nav_enter_directory(&state);
                    } else {
                        char full[1024];
                        snprintf(full, sizeof(full), "%s/%s", state.current.path, sel->name);
                        executor_run(full);
                    }
                }
                break;
            }
            case CMD_BACK:          nav_back(&state);          break;
            case CMD_TOGGLE_HIDDEN: nav_toggle_hidden(&state); break; // AÑADIDO BREAK
            case CMD_QUIT:          running = false;           break;
            default: break;
        }
    }

    ui_shutdown();
    input_restore();
    nav_cleanup(&state);
    return 0;
}