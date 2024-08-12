#ifndef IO_H
#define IO_H

#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <linux/input.h>
#include <fcntl.h>
#include <semaphore.h>

#include <fsnav/buffer.h>

#define DEVICE "/dev/input/event6"

/*
    Initialise semaphore
*/
bool init_io();

void destroy_io();

/*
    Reads DEVICE file and pushes key events into a buffer.
    This method can be run in a separate thread.
*/
void listen();

#endif