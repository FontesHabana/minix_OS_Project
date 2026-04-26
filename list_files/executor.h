//
// Created by fontes on 4/25/26.
//

#ifndef LIST_FILES_EXECUTOR_H
#define LIST_FILES_EXECUTOR_H

#include "common.h"

/*
 * Determina qué aplicación usar y lanza el proceso.
 * @param filepath: Ruta completa al archivo.
 * @param entry: Estructura con metadatos del archivo.
 */
void executor_run(const char *filepath);

#endif //LIST_FILES_EXECUTOR_H