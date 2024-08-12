#include <fsnav/io.h>


extern buffer_t* ctrl_buffer;
sem_t* ctrl_lock = NULL;

bool init_io() {
    ctrl_lock = (sem_t*) malloc(sizeof(sem_t));
}

void destroy_io() {
    free(ctrl_lock);
}

void listen() {
    int fd = open(DEVICE, O_RDONLY);
    if(fd != -1) {
        while(true) {
            struct input_event input;
            ssize_t ret = read(fd, &input, sizeof(struct input_event));
            if(ret > 0) {
                if(input.type == EV_KEY && (input.value == 0 || input.value == 2)) {
                    long code = input.code;
                    enqueue(ctrl_buffer, (void*) code, sizeof(long));
                    sem_post(ctrl_lock);
                }
            }
        }
        close(fd);
    }
}