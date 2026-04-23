#include <stdio.h>
#include "tree.h"


void print_indent(int level, int is_last, struct tree_config *config) {
   int i;
    for (i = 0; i < level; i++) {
        if (config->active_levels[i]) {
            printf("│   ");
        } else {
            printf("    ");
        }
    }

    if (is_last) {
        printf("└── ");
    } else {
        printf("├── ");
    }
}