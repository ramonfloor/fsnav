#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <dirent.h>
#include <string.h>

#include <fsnav/buffer.h>

void list_directories(buffer_t* dir_list, const char* pathname);

#endif