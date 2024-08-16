#include <fsnav/io.h>

extern buffer_t* ctrl_buffer;
sem_t* ctrl_lock = NULL;
//extern pthread_mutex_t exit_mut;

bool init_io() {
    ctrl_lock = (sem_t*) malloc(sizeof(sem_t));
    return ctrl_lock != NULL;
}

void destroy_io() {
    if(ctrl_lock) {
        free(ctrl_lock);
    }
}

void listen() {
    int fd = open(DEVICE, O_RDONLY);
    if(fd != -1) {
        // TODO: sem_t or mutex to ensure thread termination when escape key is pressed (not hard coded)
        while(true) {
            struct input_event input;
            ssize_t ret = read(fd, &input, sizeof(struct input_event));
            if(ret > 0) {
                if(input.type == EV_KEY && (input.value == 0 || input.value == 2)) {
                    long code = input.code;

                    enqueue(ctrl_buffer, &code, sizeof(long));
                    sem_post(ctrl_lock);

                    if(code == KEY_ESC) break; // at the moment simplest way of ending this thread, not robust though
                }
            }
        }
        close(fd);
    }
}