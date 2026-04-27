//
// Created by fontes on 4/25/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "executor.h"


#include "input_handler.h"
#include "ui_core.h"





FileType detect_file_type(const char *path) {
    unsigned char magic[4];
    FILE *f = fopen(path, "rb");

    if (f == NULL) return F_TEXT;

    size_t bytes_read = fread(magic, 1, 4, f);
    fclose(f);

    if (bytes_read >= 4) {
        if (magic[0] == 0x7F && magic[1] == 'E' && magic[2] == 'L' && magic[3] == 'F') {
            return F_BIN_ELF;
        }
    }

    return F_TEXT;
}

void executor_run(const char *path) {
    FileType type = detect_file_type(path);



    ui_shutdown();
    input_restore();

    pid_t pid = fork();

    if (pid == -1) {
        perror("Error");
        return;
    }

    //Child process
    if (pid == 0) {

        if (type == F_BIN_ELF) {
            execlp(path, path, (char *)NULL);
        } else {
            execlp("vi", "vi", path, (char *)NULL);
        }

        perror("Error in execution");
        exit(1);
    }
    //Father process
    else {
        wait(NULL);


        sleep(1);

        input_init();
        ui_init();
    }


}

