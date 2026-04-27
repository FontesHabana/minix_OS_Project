//
// Created by fontes on 4/25/26.
//

#ifndef LIST_FILES_INPUT_HANDLER_H
#define LIST_FILES_INPUT_HANDLER_H

typedef enum {
    CMD_NONE,
    CMD_UP,
    CMD_DOWN,
    CMD_ENTER,
    CMD_BACK,
    CMD_QUIT,
    CMD_TOGGLE_HIDDEN,
} Command;


void input_init();


void input_restore();


Command input_get_command();


#endif //LIST_FILES_INPUT_HANDLER_H