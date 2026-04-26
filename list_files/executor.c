//
// Created by fontes on 4/25/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "executor.h"

#include <sys/stat.h>

#include "input_handler.h"
#include "ui_core.h"





FileType detect_file_type(const char *path) {
    unsigned char magic[4];
    FILE *f = fopen(path, "rb");

    if (f == NULL) return F_TEXT; // Si no podemos abrirlo, intentamos vi igual

    size_t bytes_read = fread(magic, 1, 4, f);
    fclose(f);

    if (bytes_read >= 4) {
        if (magic[0] == 0x7F && magic[1] == 'E' && magic[2] == 'L' && magic[3] == 'F') {
            return F_BIN_ELF;
        }
    }

    // Si no es un binario, que sea texto por defecto
    return F_TEXT;
}

void executor_run(const char *path) {
    FileType type = detect_file_type(path);

    if (type == F_UNKNOWN) {
        // Si no sabemos qué es, no hacemos nada para evitar errores
        return;
    }

    ui_shutdown();
    input_restore();

    pid_t pid = fork();

    if (pid == -1) {
        perror("Error en fork");
        return;
    }

    if (pid == 0) {
        // --- PROCESO HIJO ---
        if (type == F_BIN_ELF) {
            // Intentamos ejecutar el binario
            execlp(path, path, (char *)NULL);
        } else {
            // Intentamos abrir con vi
            // IMPORTANTE: vi necesita el nombre del comando como segundo argumento
            execlp("vim", "vim", path, (char *)NULL);
        }

        // SI LLEGAMOS AQUÍ, ES QUE EXEC FALLÓ
        perror("Error al ejecutar la aplicacion");
        exit(1); // MATAR AL HIJO INMEDIATAMENTE
    }
    else {
        // --- PROCESO PADRE ---
        wait(NULL); // Esperar a que el hijo (vi o el binario) termine

        printf("\n\x1b[32m[Regresando al explorador en 3 segundos...]\x1b[0m\n");
        sleep(3);

        // Volver a tomar el control de la terminal
        input_init();
        ui_init();
    }


}

