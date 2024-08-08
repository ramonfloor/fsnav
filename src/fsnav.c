#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <threads.h>
#include <semaphore.h>

#include <fsnav/buffer.h>
#include <fsnav/directory.h>
#include <fsnav/io.h>
#include <fsnav/structures.h>

sem_t buffer_lock;

int main() {
    initialize();
    sem_init(&buffer_lock, 0, 1);

    thrd_t t1;
    thrd_t t2;

    thrd_create(&t1, (void*)listen, NULL);
    thrd_create(&t2, (void*)input_handler, NULL);

    thrd_join(t1, NULL);
    thrd_join(t2, NULL);

    destroy();
    return EXIT_SUCCESS;
}