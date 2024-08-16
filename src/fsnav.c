#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#include <fsnav/buffer.h>
#include <fsnav/directory.h>
#include <fsnav/io.h>
#include <fsnav/term.h>
#include <fsnav/state.h>
#include <fsnav/core.h>

pthread_t t1;
pthread_t t2;

int main() {
    atexit(destroy_all);
    
    int exit_msg = EXIT_FAILURE;
    if(init()) {
        pthread_create(&t1, NULL, (void*)(void*)listen, NULL);
        pthread_create(&t2, NULL, (void*)(void*)key_handler, NULL);

        pthread_join(t1, NULL);
        pthread_join(t2, NULL);
        reset_term();
        exit_msg = EXIT_SUCCESS;
    }
    
    return exit_msg;
}