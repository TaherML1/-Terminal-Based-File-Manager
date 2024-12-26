#ifndef LOGGER_H
#define LOGGER_H

#include <stdio.h>
#include <time.h>

#define RESET "\x1B[0m"
#define RED "\x1B[31m"
#define GREEN "\x1B[32m"
#define YELLOW "\x1B[33m"
#define BLUE "\x1B[34m"

void log_info(const char *message);
void log_error(const char *message);

void log_operation(const char *operation);

#endif

