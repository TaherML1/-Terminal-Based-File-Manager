#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include "logger.h"


void log_info(const char *message);
void log_error(const char *message);



void open_folder(const char *path) {
    if (chdir(path) == -1) {
        perror("chdir");
        log_error("Failed to change directory");
    } else {
        log_info("Directory changed successfully");
    }
}

void read_folder_content(const char *path) {
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
    log_info("Directory contents listed successfully");
}

void get_file_info(const char *filename) {
    struct stat file_stat;
    if (stat(filename, &file_stat) == -1) {
        perror("stat");
        log_error("Failed to get file information");
        return;
    }

    printf("File: %s\n", filename);
    printf("Size: \t%ld bytes\n", file_stat.st_size);
    printf("Type: \t");
    if (S_ISDIR(file_stat.st_mode)) {
        printf("Directory\n");
    } else if (S_ISREG(file_stat.st_mode)) {
        printf("Regular File\n");
    } else {
        printf("Other\n");
    }
    printf("Permissions: \t%o\n", file_stat.st_mode & 0777);
    log_info("File information retrieved successfully");
}

void edit_file(const char *filename) {
    // For simplicity, we'll use `nano` to edit the file.
    // You can replace this with any text editor of your choice.
    char command[256];
    snprintf(command, sizeof(command), "nano %s", filename);
    system(command);
    log_info("File opened for editing");
}

void rename_file_or_folder(const char *oldname, const char *newname) {
    if (rename(oldname, newname) == -1) {
        perror("rename");
        log_error("Failed to rename file or folder");
    } else {
        log_info("File or folder renamed successfully");
    }
}