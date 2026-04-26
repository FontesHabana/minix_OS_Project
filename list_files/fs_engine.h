//
// Created by fontes on 4/25/26.
//

#ifndef LIST_FILES_FS_ENGINE_H
#define LIST_FILES_FS_ENGINE_H

#include "common.h"



/*
 * Llena una estructura DirectoryLevel a partir de una ruta dada.
 * Esta es la función principal que usará el Gestor de Navegación.
 *
 * @param path: La ruta absoluta o relativa a leer.
 * @param level: Puntero a la estructura donde se guardarán los resultados.
 * @return: 0 si tuvo éxito, un código de error negativo si falló (ej. carpeta no existe).
 */
int fs_get_contents(const char *path, DirectoryLevel *level,bool show_hidden);


/*
 * Libera la memoria dinámica (malloc) utilizada por las entradas de un nivel.
 * Debe llamarse cada vez que cerremos una carpeta o salgamos del programa.
 */
void fs_free_contents(DirectoryLevel *level);

/*
 * Determina el tipo de archivo analizando sus metadatos y, si es necesario, sus bits (Magic Numbers).
 * Se separa de fs_get_contents para poder usarla de forma independiente al intentar abrir un archivo.
 *
 * @param full_path: Ruta completa al archivo.
 * @return: El FileType detectado (DIRECTORY, REGULAR, EXECUTABLE, etc).
 */
FileType fs_detect_file_type(const char *full_path);

/*
 * Función opcional: Ordena las entradas dentro de un DirectoryLevel.
 * Útil para asegurar que las carpetas aparezcan primero o por orden alfabético.
 */
void fs_sort_entries(DirectoryLevel *level);

#endif //LIST_FILES_FS_ENGINE_H