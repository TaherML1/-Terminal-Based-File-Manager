#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "file_operations.h"
#include "directory_ops.h"
#include "permissions.h"
#include "logger.h"

void print_usage() {
    printf("Usage:\n");
    printf("slist <directory>                List the contents of a directory.\n");
    printf("scopy <source> <destination>     Copy a file from source to destination.\n");
    printf("sremove <file/directory>         Remove a file or directory.\n");
    printf("screate <directory>              Create a new directory.\n");
    printf("screatefile <filename>          Create a new file.\n");
    printf("schmod <file/directory> <permissions> Change the permissions of a file or directory.\n");
    printf("swrite <filename> <data>        Write data to a file.\n");
    printf("sread <filename>                Read data from a file.\n");
    printf("sopen <directory>               Open a directory (change current working directory).\n");
    printf("slistdir <directory>            List the contents of a directory.\n");
    printf("sinfo <filename>                Get information about a file.\n");
    printf("sedit <filename>                Open and edit a file.\n");
    printf("srename <oldname> <newname>      Rename a file or directory.\n");
    printf("exit                            Exit the interactive mode.\n");
    // Add more commands as needed
}

void handle_command(char *line) {
    char *argv[10];
    int argc = 0;
    char *token = strtok(line, " ");

    while (token != NULL) {
        argv[argc++] = token;
        token = strtok(NULL, " ");
    }

    if (argc < 2) {
        print_usage();
        return;
    }

    if (strcmp(argv[0], "slist") == 0) {
        if (argc != 2) {
            print_usage();
            return;
        }
        list_directory(argv[1]);
    } else if (strcmp(argv[0], "scopy") == 0) {
        if (argc != 3) {
            print_usage();
            return;
        }
        copy_file(argv[1], argv[2]);
    } else if (strcmp(argv[0], "sremove") == 0) {
        if (argc != 2) {
            print_usage();
            return;
        }
        remove_file_or_directory(argv[1]);
    } else if (strcmp(argv[0], "screate") == 0) {
        if (argc != 2) {
            print_usage();
            return;
        }
        create_directory(argv[1]);
    } else if (strcmp(argv[0], "screatefile") == 0) {
        if (argc != 2) {
            print_usage();
            return;
        }
        create_file(argv[1]);
    } else if (strcmp(argv[0], "schmod") == 0) {
        if (argc != 3) {
            print_usage();
            return;
        }
        change_permissions(argv[1], strtol(argv[2], NULL, 8));
    } else if (strcmp(argv[0], "swrite") == 0) {
        if (argc != 3) {
            print_usage();
            return;
        }
        write_to_file(argv[1], argv[2]);
    } else if (strcmp(argv[0], "sread") == 0) {
        if (argc != 2) {
            print_usage();
            return;
        }
        read_from_file(argv[1]);
    } else if (strcmp(argv[0], "sopen") == 0) {
        if (argc != 2) {
            print_usage();
            return;
        }
        open_folder(argv[1]);
    } else if (strcmp(argv[0], "slistdir") == 0) {
        if (argc != 2) {
            print_usage();
            return;
        }
        read_folder_content(argv[1]);
    } else if (strcmp(argv[0], "sinfo") == 0) {
        if (argc != 2) {
            print_usage();
            return;
        }
        get_file_info(argv[1]);
    } else if (strcmp(argv[0], "sedit") == 0) {
        if (argc != 2) {
            print_usage();
            return;
        }
        edit_file(argv[1]);
    } else if (strcmp(argv[0], "srename") == 0) {
        if (argc != 3) {
            print_usage();
            return;
        }
        rename_file_or_folder(argv[1], argv[2]);
    } else if (strcmp(argv[0], "exit") == 0) {
        exit(0);
    } else {
        print_usage();
    }
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        // Interactive mode
        char *line;
        using_history();
        while ((line = readline("file_manager> ")) != NULL) {
            if (*line) {
                add_history(line);
                handle_command(line);
            }
            free(line);
        }
    } else {
        // Command-line mode
        handle_command(argv[1]);
    }

    return 0;
}
