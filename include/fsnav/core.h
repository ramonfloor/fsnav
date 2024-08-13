/*
    Handles programm state etc.
*/

#ifndef CORE_H
#define CORE_H

#include <stdlib.h>
#include <stdbool.h>
#include <pthread.h>
#include <semaphore.h>

#include <fsnav/state.h>
#include <fsnav/buffer.h>
#include <fsnav/term.h>
#include <fsnav/tree.h>
#include <fsnav/io.h>
#include <fsnav/directory.h>
#include <fsnav/enum.h>

#define ROOT "/"

/*
    Initialize program state etc...
*/
bool init();

void destroy_all();

bool update_state(enum KEY key);

#endif