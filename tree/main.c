#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

int main(int argc, char *argv[]) {
    char *start_dir=(argc > 1 ? argv[1] : "");
    struct tree_config config={0,0};





    printf("%s\n", start_dir);
    walk_dir(start_dir, 0, &config);

    return 0;
}