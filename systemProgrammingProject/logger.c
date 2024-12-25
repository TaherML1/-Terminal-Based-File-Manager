#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void log_info(const char *message) {
    FILE *log_file = fopen("log.txt", "a");
    if (log_file == NULL) {
        perror("fopen");
        return;
    }

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    fprintf(log_file, "[INFO] %s %s\n", asctime(t), message);
    fclose(log_file);
}

void log_error(const char *message) {
    FILE *log_file = fopen("log.txt", "a");
    if (log_file == NULL) {
        perror("fopen");
        return;
    }

    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    fprintf(log_file, "[ERROR] %s %s\n", asctime(t), message);
    fclose(log_file);
}
