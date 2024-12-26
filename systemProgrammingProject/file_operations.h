#ifndef FILE_OPERATIONS_H
#define FILE_OPERATIONS_H

void copy_file(const char *src, const char *dest);
void create_file(const char *filename);
void write_to_file(const char *filename, const char *data);
void read_from_file(const char *filename);
void open_folder(const char *path);
void read_folder_content(const char *path);
void get_file_info(const char *filename);
void edit_file(const char *filename);
void rename_file_or_folder(const char *oldname, const char *newname);
// Add other function prototypes as needed

#endif // FILE_OPERATIONS_H
