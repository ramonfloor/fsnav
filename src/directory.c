#include <fsnav/directory.h>


void list_directories(buffer_t* dir_list, const char* pathname) {
    if(dir_list != NULL) {
        DIR* dir = opendir(pathname);
        if(dir != NULL) {
            struct dirent* ent = readdir(dir);
            while(ent != NULL) {
                enqueue(dir_list, ent->d_name, sizeof(ent->d_name));
                ent = readdir(dir);
            }
            closedir(dir);
        }
    }
}