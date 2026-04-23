#define _DEFAULT_SOURCE  // O #define _XOPEN_SOURCE 500

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include "tree.h"







void walk_dir(const char *path, int level, struct tree_config *config) {
    DIR *dir;
    struct dirent *entry;
    struct stat st;
    char full_path[PATH_MAX_LEN];
	int total_entries =0;
	int current_count = 0;

    if (!(dir = opendir(path))) return;

	while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            total_entries++;
        }
    }

	rewinddir(dir);

    while ((entry = readdir(dir)) != NULL) {


        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

		current_count++;
		int is_latest=(current_count==total_entries);


		config->active_levels[level] = is_latest ? 0 : 1;


        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);
        if (lstat(full_path, &st) == -1) continue;


        print_indent(level, is_latest,config);
        printf("%s\n", entry->d_name);

		if(S_ISLNK(st.st_mode)) {
		printf(" -> (link)\n");
		}
        if (S_ISDIR(st.st_mode)) {
    	    walk_dir(full_path, level + 1, config);
        }

    }
    closedir(dir);
}