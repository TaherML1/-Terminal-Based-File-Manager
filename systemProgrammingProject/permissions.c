#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "logger.h"
#include <fcntl.h>

void change_permissions(const char *path, mode_t mode) {
    if (chmod(path, mode) == -1) {
        perror("chmod");
        log_error("Failed to change permissions");
    } else {
        log_info("Permissions changed successfully");
    }
}
