#ifndef STATE_H
#define STATE_H

#include <stdlib.h>
#include <string.h>

#include <fsnav/buffer.h>
#include <fsnav/tree.h>


#define MAX_PATH_SIZE 4096
#define MAX_NAME_SIZE 256

typedef struct pstate {
    char cwd_path[MAX_PATH_SIZE];
    char cwd_name[MAX_NAME_SIZE];
    buffer_t* dir_list;
    buffer_node_t* cursor; //saves the currently selected directory, when changing directory this must be set to tail node of buffer
} pstate_t;

pstate_t* mk_state() {
    pstate_t* s = (pstate_t*) malloc(sizeof(pstate_t));
    if(s != NULL) {
        buffer_t* b = get_buffer();
        if(b != NULL) {
            s->dir_list = b;
        } else {
            free(s);
            s = NULL;
        }
    }
    return s;
}

void destroy_state(pstate_t* s) {
    destroy_buffer(s->dir_list);
    free(s);
}

void set_name(pstate_t* state, char* cwd) {
    //memset(state->cwd_name, 0, MAX_NAME_SIZE);
    memcpy(state->cwd_name, cwd, MAX_NAME_SIZE - 1); //last character has to be '\0'
}

void set_path(pstate_t* state, char* parent, char* cwd) {

}

#endif