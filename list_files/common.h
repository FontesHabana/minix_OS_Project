//
// Created by fontes on 4/25/26.
//

#ifndef LIST_FILES_COMMON_H
#define LIST_FILES_COMMON_H
#include <sys/types.h>
#include <stdbool.h>

typedef enum {
    F_DIRECTORY,
    F_BIN_ELF,
    F_SCRIPT,
    F_TEXT,
    F_UNKNOWN
} FileType;

typedef struct {
    char name[256];
    FileType type;
    off_t size;


} FileEntry;


typedef struct {
    char path[1024];
    FileEntry *entries;
    int count;
    int selected_index;
    int scroll_offset;
} DirectoryLevel;

#endif //LIST_FILES_COMMON_H