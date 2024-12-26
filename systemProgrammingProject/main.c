#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "file_operations.h"
#include "directory_ops.h"
#include "permissions.h"
#include "logger.h"

#define RED "\x1B[31m"
#define RESET "\x1B[0m"

void print_usage() {
    printf("Avilable commands:\n");
    printf("tlist <directory>                List the contents of a directory.\n");
    printf("tcopy <source> <destination>     Copy a file from source to destination.\n");
    printf("tremove <file/directory>         Remove a file or directory.\n");
    printf("tcreate <directory>              Create a new directory.\n");
    printf("tcreatefile <filename>          Create a new file.\n");
    printf("tchmod <file/directory> <permissions> Change the permissions of a file or directory.\n");
    printf("twrite <filename> <data>        Write data to a file.\n");
    printf("tread <filename>                Read data from a file.\n");
    printf("topen <directory>               Open a directory (change current working directory).\n");
    printf("tinfo <filename>                Get information about a file.\n");
    printf("tedit <filename>                Open and edit a file.\n");
    printf("trename <oldname> <newname>      Rename a file or directory.\n");
    printf("exit                            Exit the interactive mode.\n");
    // Add more commands as needed
}

void print_welcome_message() {
    printf("Welcome to the File Manager!\n");
    printf("Type 'help' to show available commands.\n");
    printf("Type 'exit' to quit the interactive mode.\n");
}

void handle_command(char *line) {
    char *argv[10];
    int argc = 0;
    char *token = strtok(line, " ");
    while (token != NULL) {
        argv[argc++] = token;
        token = strtok(NULL, " ");
    }

    if (argc < 1) {
        print_usage();
        return;
    }

    if (strcmp(argv[0], "help") == 0) {
        print_usage();
    } else if (strcmp(argv[0], "tlist") == 0) {
        if (argc != 2) {
            printf(RED "Error: Missing directory parameter for 'slist' command.\n" RESET);
            print_usage();
            return;
        }
        list_directory(argv[1]);
    } else if (strcmp(argv[0], "tcopy") == 0) {
        if (argc != 3) {
            printf(RED "Error: Missing source or destination parameter for 'scopy' command.\n" RESET);
            print_usage();
            return;
        }
        copy_file(argv[1], argv[2]);
    } else if (strcmp(argv[0], "tremove") == 0) {
        if (argc != 2) {
            printf(RED "Error: Missing file/directory parameter for 'sremove' command.\n" RESET);
            print_usage();
            return;
        }
        remove_file_or_directory(argv[1]);
    } else if (strcmp(argv[0], "tcreate") == 0) {
        if (argc != 2) {
            printf(RED "Error: Missing directory parameter for 'screate' command.\n" RESET);
            print_usage();
            return;
        }
        create_directory(argv[1]);
    } else if (strcmp(argv[0], "tcreatefile") == 0) {
        if (argc != 2) {
            printf(RED "Error: Missing filename parameter for 'screatefile' command.\n" RESET);
            print_usage();
            return;
        }
        create_file(argv[1]);
    } else if (strcmp(argv[0], "tchmod") == 0) {
        if (argc != 3) {
            printf(RED "Error: Missing file/directory or permissions parameter for 'schmod' command.\n" RESET);
            print_usage();
            return;
        }
        change_permissions(argv[1], strtol(argv[2], NULL, 8));
    } else if (strcmp(argv[0], "twrite") == 0) {
        if (argc != 3) {
            printf(RED "Error: Missing filename or data parameter for 'swrite' command.\n" RESET);
            print_usage();
            return;
        }
        write_to_file(argv[1], argv[2]);
    } else if (strcmp(argv[0], "tread") == 0) {
        if (argc != 2) {
            printf(RED "Error: Missing filename parameter for 'sread' command.\n" RESET);
            print_usage();
            return;
        }
        read_from_file(argv[1]);
    } else if (strcmp(argv[0], "topen") == 0) {
        if (argc != 2) {
            printf(RED "Error: Missing directory parameter for 'sopen' command.\n" RESET);
            print_usage();
            return;
        }
        open_folder(argv[1]);
    } else if (strcmp(argv[0], "tinfo") == 0) {
        if (argc != 2) {
            printf(RED "Error: Missing filename parameter for 'sinfo' command.\n" RESET);
            print_usage();
            return;
        }
        get_file_info(argv[1]);
    } else if (strcmp(argv[0], "tedit") == 0) {
        if (argc != 2) {
            printf(RED "Error: Missing filename parameter for 'sedit' command.\n" RESET);
            print_usage();
            return;
        }
        edit_file(argv[1]);
    } else if (strcmp(argv[0], "trename") == 0) {
        if (argc != 3) {
            printf(RED "Error: Missing oldname or newname parameter for 'srename' command.\n" RESET);
            print_usage();
            return;
        }
        rename_file_or_folder(argv[1], argv[2]);
    } else if (strcmp(argv[0], "exit") == 0) {
        exit(0);
    } else {
        printf(RED "Error: Invalid command. Type 'help' for available commands.\n" RESET);
        print_usage();
    }
}

int main(int argc, char *argv[]) {
    if (argc == 1) {
        // Interactive mode
        char *line;
        using_history();
        print_welcome_message();
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
