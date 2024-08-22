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
        key_listener();
        reset_term();
        exit_msg = EXIT_SUCCESS;
    }
    
    return exit_msg;
}