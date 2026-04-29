

#ifndef TREE_TREE_H
#define TREE_TREE_H


#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>

#define MAX_DEPTH 1024
#define PATH_MAX_LEN 4096


struct visited_dir {
    ino_t inode;
    dev_t device;
};

struct tree_config {
    int show_all; //Flag: Show hidden files (0 or 1)
    int dir_only; //FLag: Show only directories (0 or 1)
	int active_levels[MAX_DEPTH];
};

void walk_dir(const char *path, int level, struct tree_config *config);

void print_indent(int level, int is_last, struct tree_config *config);

int is_already_visited(ino_t inode, dev_t device);


#endif //TREE_TREE_H