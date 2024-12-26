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
    printf("swrite <filename> <data>\n");
    printf("sread <filename>\n");
    printf("sopen <directory>\n");
    printf("slistdir <directory>\n");
    printf("sinfo <filename>\n");
    printf("sedit <filename>\n");
    printf("srename <oldname> <newname>\n");
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
    } else if (strcmp(argv[1], "swrite") == 0) {
        if (argc != 4) {
            print_usage();
            return 1;
        }
        write_to_file(argv[2], argv[3]);
    } else if (strcmp(argv[1], "sread") == 0) {
        if (argc != 3) {
            print_usage();
            return 1;
        }
        read_from_file(argv[2]);
    } else if (strcmp(argv[1], "sopen") == 0) {
        if (argc != 3) {
            print_usage();
            return 1;
        }
        open_folder(argv[2]);
    } else if (strcmp(argv[1], "slistdir") == 0) {
        if (argc != 3) {
            print_usage();
            return 1;
        }
        read_folder_content(argv[2]);
    } else if (strcmp(argv[1], "sinfo") == 0) {
        if (argc != 3) {
            print_usage();
            return 1;
        }
        get_file_info(argv[2]);
    } else if (strcmp(argv[1], "sedit") == 0) {
        if (argc != 3) {
            print_usage();
            return 1;
        }
        edit_file(argv[2]);
    } else if (strcmp(argv[1], "srename") == 0) {
        if (argc != 4) {
            print_usage();
            return 1;
        }
        rename_file_or_folder(argv[2], argv[3]);
    } else {
        print_usage();
        return 1;
    }

    return 0;
}
