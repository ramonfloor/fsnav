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

sem_t exit_sem;
//pthread_mutex_t exit_mut;

int main() {
    atexit(destroy_all);
    atexit(reset_term);
    sem_init(&exit_sem, 0, 1);
    //pthread_mutex_init(&exit_mut, NULL);
    //pthread_mutex_lock(&exit_mut);
    
    init();

    pthread_create(&t1, NULL, (void*)(void*)listen, NULL);
    pthread_create(&t2, NULL, (void*)(void*)key_handler, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    return EXIT_SUCCESS;
}