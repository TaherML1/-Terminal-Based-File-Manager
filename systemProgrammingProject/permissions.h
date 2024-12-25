#ifndef PERMISSIONS_H
#define PERMISSIONS_H

#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>

void change_permissions(const char *path, mode_t mode);
// Add other function prototypes as needed

#endif // PERMISSIONS_H
