#ifndef IO_H
#define IO_H

#include <string.h>
#include <stdio.h>
#include <linux/input.h>
#include <fcntl.h>

#include <fsnav/buffer.h>
#include <fsnav/directory.h>


buffer_t* ctrl_buffer;
extern sem_t buffer_lock;

bool init_io() {
    ctrl_buffer = (buffer_t*) malloc(sizeof(buffer_t));
}


#define DEVICE ""

/*
    Reads DEVICE file and pushes key events into a buffer.
    This method can be run in a separate thread.
*/
void listen() {
    int fd = open(DEVICE, O_RDONLY);
    if(fd != -1) {
        while(true) {
            struct input_event input;
            ssize_t ret = read(fd, &input, sizeof(struct input_event));
            if(ret > 0) {
                if(input.type == EV_KEY && (input.value == 0 || input.value == 2)) {
                    long code = input.code;
                    enqueue(ctrl_buffer, (void*) code);
                    sem_post(&buffer_lock);
                }
            }
        }
        close(fd);
    }
}

#endif