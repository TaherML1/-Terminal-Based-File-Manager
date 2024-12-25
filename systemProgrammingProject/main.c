#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_operations.h"
#include "directory_ops.h"
#include "permissions.h"
#include "logger.h"

void print_usage() {
    printf("Usage:\n");
    printf("slist <directory>\n");
    printf("scopy <source> <destination>\n");
    printf("sremove <file/directory>\n");
    printf("screate <directory>\n");
    printf("screatefile <filename>\n");
    printf("schmod <file/directory> <permissions>\n");
    // Add more commands as needed
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        print_usage();
        return 1;
    }

    if (strcmp(argv[1], "slist") == 0) {
        if (argc != 3) {
            print_usage();
            return 1;
        }
        list_directory(argv[2]);
    } else if (strcmp(argv[1], "scopy") == 0) {
        if (argc != 4) {
            print_usage();
            return 1;
        }
        copy_file(argv[2], argv[3]);
    } else if (strcmp(argv[1], "sremove") == 0) {
        if (argc != 3) {
            print_usage();
            return 1;
        }
        remove_file_or_directory(argv[2]);
    } else if (strcmp(argv[1], "screate") == 0) {
        if (argc != 3) {
            print_usage();
            return 1;
        }
        create_directory(argv[2]);
    } else if (strcmp(argv[1], "screatefile") == 0) {
        if (argc != 3) {
            print_usage();
            return 1;
        }
        create_file(argv[2]);
    } else if (strcmp(argv[1], "schmod") == 0) {
        if (argc != 4) {
            print_usage();
            return 1;
        }
        change_permissions(argv[2], strtol(argv[3], NULL, 8));
    } else {
        print_usage();
        return 1;
    }

    return 0;
}
