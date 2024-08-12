/*
    Handles programm state etc.
*/

#ifndef CORE_H
#define CORE_H

#include <stdlib.h>
#include <stdbool.h>
#include <threads.h>
#include <semaphore.h>

#include <fsnav/state.h>
#include <fsnav/buffer.h>
#include <fsnav/term.h>
#include <fsnav/tree.h>
#include <fsnav/io.h>
#include <fsnav/directory.h>

#define ROOT "/"

/*
    Initialize program state etc...
*/
bool init();

void destroy_all();

#endif