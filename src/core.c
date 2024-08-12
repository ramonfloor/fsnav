#include <fsnav/core.h>


/*==================*/
/* Global variables */
/*==================*/

pstate_t* glob_state = NULL;
state_tree_t* tree = NULL;
buffer_t* ctrl_buffer = NULL;

extern sem_t* ctrl_lock;

void destroy_all() {
    if(ctrl_buffer != NULL) {
        destroy_buffer(ctrl_buffer);
    }
    if(ctrl_lock != NULL) {
        destroy_io();
    }
    if(tree != NULL) {
        destroy_tree(tree);
    }
}

bool init() {
    glob_state = mk_state();
    if(glob_state == NULL) {
        return false;
    }
    buffer_t* dir_list = get_buffer();
    if(dir_list == NULL) {
        destroy_state(glob_state);
        return false;
    }

    init_io();
    if(ctrl_lock == NULL) {
        destroy_buffer(glob_state->dir_list);
        destroy_state(glob_state);
        return false;
    }
        
    ctrl_buffer = get_buffer();
    if(ctrl_buffer == NULL) {
        destroy_buffer(glob_state->dir_list);
        destroy_io();
        destroy_state(glob_state);
        return false;
    }

    tree = get_tree();
    if(tree == NULL) {
        destroy_buffer(glob_state->dir_list);
        destroy_buffer(ctrl_buffer);
        destroy_io();
        destroy_state(glob_state);
        return false;
    }

    // setting starting directory to root
    set_name(glob_state, ROOT);
    set_path(glob_state, ROOT, NULL);
    glob_state->dir_list = dir_list;
    list_directories(glob_state->dir_list, ROOT);
    glob_state->cursor = glob_state->dir_list->tail;
    glob_state->tree_cursor = NULL;

    // setting up the tree
    tree_node_t* root_nd = get_node();
    if(root_nd == NULL) {
        destroy_all();
        return false;
    }

    root_nd->p_state = glob_state;
    root_nd->parent = NULL;

    tree->root = root_nd;
    
    // init semaphores
    sem_init(ctrl_lock, 0, 1);

    init_scr(glob_state);

    return true;
}