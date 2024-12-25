#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include "logger.h"

void list_directory(const char *path) {
    DIR *dir = opendir(path);
    if (dir == NULL) {
        perror("opendir");
        log_error("Failed to open directory");
        return;
    }

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    closedir(dir);
    log_info("Directory listed successfully");
}

void create_directory(const char *path) {
    if (mkdir(path, 0755) == -1) {
        perror("mkdir");
        log_error("Failed to create directory");
    } else {
        log_info("Directory created successfully");
    }
}

void remove_file_or_directory(const char *path) {
    struct stat path_stat;
    stat(path, &path_stat);

    if (S_ISDIR(path_stat.st_mode)) {
        if (rmdir(path) == -1) {
            perror("rmdir");
            log_error("Failed to remove directory");
        } else {
            log_info("Directory removed successfully");
        }
    } else {
        if (unlink(path) == -1) {
            perror("unlink");
            log_error("Failed to remove file");
        } else {
            log_info("File removed successfully");
        }
    }
}
