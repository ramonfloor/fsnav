#ifndef DIRECTORY_H
#define DIRECTORY_H

#include <dirent.h>
#include <fsnav/buffer.h>

buffer_t* list_directories(buffer_t* dir_list, const char* pathname) {
    if(dir_list != NULL) {
        DIR* dir = opendir(pathname);
        if(dir != NULL) {
            struct dirent* ent = readdir(dir);
            while(ent != NULL) {
                enqueue(dir_list, ent->d_name);
                ent = readdir(dir);
            }
            closedir(dir);
        }
    }
    return dir_list;
} 

#endif