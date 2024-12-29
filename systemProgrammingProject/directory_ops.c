#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include "logger.h" // Header file for logging

// Function to list all files and subdirectories in a directory
void list_directory(const char* path) {
    // Open the directory
    DIR* dir = opendir(path);
    if (dir == NULL) {
        perror("opendir"); // Print error message to standard error
        log_error("Failed to open directory"); // Log error message
        return;
    }

    struct dirent* entry;
    // Read and print all entries in the directory
    while ((entry = readdir(dir)) != NULL) {
        printf("%s\n", entry->d_name);
    }

    closedir(dir); // Close the directory
    log_info("Directory listed successfully"); // Log success message
}

// Function to create a new directory
void create_directory(const char* path) {
    // Create the directory and set its permissions (0755: rwxr-xr-x)
    if (mkdir(path, 0755) == -1) {
        perror("mkdir"); // Print error message to standard error
        log_error("Failed to create directory"); // Log error message
    }
    else {
        log_info("Directory created successfully"); // Log success message
    }
}

// Function to remove a specified file or directory
void remove_file_or_directory(const char* path) {
    struct stat path_stat;
    stat(path, &path_stat); // Get information about the path

    // If the path is a directory
    if (S_ISDIR(path_stat.st_mode)) {
        // Remove the directory
        if (rmdir(path) == -1) {
            perror("rmdir"); // Print error message to standard error
            log_error("Failed to remove directory"); // Log error message
        }
        else {
            log_info("Directory removed successfully"); // Log success message
        }
    }
    else {
        // If the path is a file, remove the file
        if (unlink(path) == -1) {
            perror("unlink"); // Print error message to standard error
            log_error("Failed to remove file"); // Log error message
        }
        else {
            log_info("File removed successfully"); // Log success message
        }
    }
}

