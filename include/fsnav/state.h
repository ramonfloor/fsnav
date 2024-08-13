#ifndef STATE_H
#define STATE_H

#include <stdlib.h>
#include <string.h>

#include <fsnav/buffer.h>
#include <fsnav/tree.h>

#define MAX_PATH_SIZE 4096
#define MAX_NAME_SIZE 256

typedef struct tree_node tree_node_t;

typedef struct pstate {
    char cwd_path[MAX_PATH_SIZE];
    char cwd_name[MAX_NAME_SIZE];
    buffer_t* dir_list;
    buffer_node_t* cursor; //saves the currently selected directory, when changing directory this must be set to tail node of buffer
    tree_node_t* tree_cursor; //allows us to easily load the parent
    int term_curs;
} pstate_t;

pstate_t* mk_state();

void destroy_state(pstate_t* s);

void set_name(pstate_t* state, char* cwd, size_t size);

void set_path(pstate_t* state, char* parent, char* cwd);

#endif