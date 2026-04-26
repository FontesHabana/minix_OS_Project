#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <ctype.h>
#include "fs_engine.h"

#include "nav_state.h"


static FileType get_basic_type(mode_t m) {
    if (S_ISDIR(m)) return F_DIRECTORY;
    if (S_ISREG(m)) {
        if (m & S_IXUSR) return F_BIN_ELF;
        return F_TEXT;
    }
    return F_UNKNOWN;
}

int fs_get_contents(const char *path, DirectoryLevel *level, bool show_hidden) {
    // 1. Limpieza absoluta
    if (level->entries != NULL) {
        free(level->entries);
        level->entries = NULL;
    }

    level->count = 0;
    level->selected_index = 0;
    level->scroll_offset = 0;

    DIR *dir = opendir(path);
    if (!dir) return -1;

    struct dirent *entry;
    int count = 0;

    // 2. Contar con filtro estricto
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;
        if (!show_hidden && entry->d_name[0] == '.') continue;
        count++;
    }

    level->count = count;
    level->entries = (FileEntry *)calloc(count, sizeof(FileEntry)); // calloc es más seguro
    if (!level->entries && count > 0) {
        closedir(dir);
        return -2;
    }

    // 3. Llenar con el mismo filtro estricto
    rewinddir(dir);
    int i = 0;
    struct stat file_stat;
    char full_path[1024];

    while ((entry = readdir(dir)) != NULL && i < count) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;
        if (!show_hidden && entry->d_name[0] == '.') continue;

        strncpy(level->entries[i].name, entry->d_name, 255);
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        if (stat(full_path, &file_stat) == 0) {
            level->entries[i].size = file_stat.st_size;
            level->entries[i].type = get_basic_type(file_stat.st_mode);
        } else {
            level->entries[i].type = F_UNKNOWN;
        }
        i++;
    }

    closedir(dir);
    strncpy(level->path, path, 1023);
    fs_sort_entries(level);
    return 0;
}

// Asegúrate de que compare_entries use strcasecmp para un orden natural
int compare_entries(const void *a, const void *b) {
    const FileEntry *ea = (const FileEntry *)a;
    const FileEntry *eb = (const FileEntry *)b;
    if (ea->type == F_DIRECTORY && eb->type != F_DIRECTORY) return -1;
    if (ea->type != F_DIRECTORY && eb->type == F_DIRECTORY) return 1;
    return strcasecmp(ea->name, eb->name);
}

void fs_sort_entries(DirectoryLevel *level) {
    if (level->count > 1)
        qsort(level->entries, level->count, sizeof(FileEntry), compare_entries);
}


//Explorar despues
FileType fs_detect_file_type(const char *full_path) {
    // Aquí podrías añadir la lógica de leer los primeros bytes (Magic Numbers)
    // Por ahora usamos stat como base
    struct stat st;
    if (stat(full_path, &st) == 0) {
        return get_basic_type(st.st_mode);
    }
    return F_UNKNOWN;
}
void fs_free_contents(DirectoryLevel *level) {
    if (level->entries) {
        free(level->entries);
        level->entries = NULL;
    }
    level->count = 0;
}