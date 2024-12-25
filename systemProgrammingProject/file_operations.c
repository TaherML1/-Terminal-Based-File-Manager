#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "logger.h"

void log_info(const char *message);
void log_error(const char *message);

void copy_file(const char *src, const char *dest) {
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
void create_file(const char *filename) {
    int fd = open(filename, O_WRONLY | O_CREAT, 0644);
    if (fd == -1) {
        perror("open");
        log_error("Failed to create file");
    } else {
        close(fd);
        log_info("File created successfully");
    }
}