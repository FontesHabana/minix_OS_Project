//
// Created by fontes on 4/25/26.
//

#ifndef LIST_FILES_FS_ENGINE_H
#define LIST_FILES_FS_ENGINE_H

#include "common.h"




int fs_get_contents(const char *path, DirectoryLevel *level,bool show_hidden);



void fs_free_contents(DirectoryLevel *level);


void fs_sort_entries(DirectoryLevel *level);

#endif //LIST_FILES_FS_ENGINE_H