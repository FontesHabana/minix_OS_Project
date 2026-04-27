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


int nav_init(BrowserState *state, const char *start_path);


void nav_move_cursor(BrowserState *state, int direction);


int nav_enter_directory(BrowserState *state);


int nav_back(BrowserState *state);


void nav_cleanup(BrowserState *state);

void nav_toggle_hidden(BrowserState *state);




#endif //LIST_FILES_NAV_STATE_H