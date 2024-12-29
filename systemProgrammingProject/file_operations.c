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

void copy_file(const char* src, const char* dest) {
    int src_fd = open(src, O_RDONLY);
    if (src_fd == -1) {
        perror("open");
        log_error("Failed to open source file");
        return;
    }



    int dest_fd = open(dest, O_WRONLY | O_CREAT, 0644);
    if (dest_fd == -1) {
        perror("open");
        log_error("Failed to open destination file");
        close(src_fd);
        return;
    }

    char buffer[1024];
    ssize_t bytes_read;
    while ((bytes_read = read(src_fd, buffer, sizeof(buffer))) > 0) {
        write(dest_fd, buffer, bytes_read);
    }

    close(src_fd);
    close(dest_fd);
    log_info("File copied successfully");
}
void create_file(const char* filename) {
    int fd = open(filename, O_WRONLY | O_CREAT, 0644);
    if (fd == -1) {
        perror("open");
        log_error("Failed to create file");
    }
    else {
        close(fd);
        log_info("File created successfully");
    }
}

void write_to_file(const char* filename, const char* data) {
    int fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        log_error("Failed to open file for writing");
        return;
    }

    ssize_t bytes_written = write(fd, data, strlen(data));
    if (bytes_written == -1) {
        perror("write");
        log_error("Failed to write to file");
    }
    else {
        log_info("Data written to file successfully");
    }

    close(fd);
}

void read_from_file(const char* filename) {
    int fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open");
        log_error("Failed to open file for reading");
        return;
    }

    char buffer[1024];
    ssize_t bytes_read;
    while ((bytes_read = read(fd, buffer, sizeof(buffer))) > 0) {
        write(STDOUT_FILENO, buffer, bytes_read);
    }

    if (bytes_read == -1) {
        perror("read");
        log_error("Failed to read from file");
    }
    else {
        log_info("Data read from file successfully");
    }

    close(fd);
}

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