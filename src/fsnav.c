#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <threads.h>
#include <semaphore.h>

#include <fsnav/buffer.h>
#include <fsnav/directory.h>
#include <fsnav/io.h>
#include <fsnav/term.h>
#include <fsnav/state.h>
#include <fsnav/core.h>


int main() {
    init();
    destroy_all();
    return EXIT_SUCCESS;
}