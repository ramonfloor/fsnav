#include <fsnav/core.h>

/*==================*/
/* Global variables */
/*==================*/

pstate_t* init_glob_state = NULL;
pstate_t* glob_state = NULL;
state_tree_t* tree = NULL;
buffer_t* ctrl_buffer = NULL;

extern sem_t* ctrl_lock;

void destroy_all() {
    destroy_buffer(ctrl_buffer);
    destroy_io();
    destroy_tree(tree);
    
}

bool init() {
    glob_state = mk_state();
    buffer_t* dir_list = get_buffer();
    init_io();
    ctrl_buffer = get_buffer();
    tree = get_tree();

    if(!glob_state || !dir_list || !ctrl_lock || !ctrl_buffer || !tree) {
        fprintf(stderr, "Init failed. No memory.\n");
        return false;
    }

    // setting starting directory to root, init glob_state
    set_name(glob_state, ROOT, 1);
    set_path(glob_state, ROOT, NULL);
    glob_state->dir_list = dir_list;
    if(!list_directories(glob_state->dir_list, ROOT)) {
        return false;
    }
    glob_state->cursor = glob_state->dir_list->tail;
    glob_state->term_curs = 2;

    // setting up the tree
    tree_node_t* root_nd = get_node();
    if(!root_nd) {
        return false;
    }

    root_nd->p_state = glob_state;
    root_nd->parent = NULL;

    tree->root = root_nd;
    glob_state->tree_cursor = root_nd;

    init_glob_state = glob_state;
    
    // init semaphores
    sem_init(ctrl_lock, 0, 0);

    init_scr();

    return true;
}

bool update_state(enum KEY key) {
    bool u = false;
    switch(key) {
        case UP:
            if(glob_state->cursor != glob_state->dir_list->tail) {
                glob_state->cursor = glob_state->cursor->next;
                glob_state->term_curs--;
                u = true;
            }
            break;
        case DOWN:
            if(glob_state->cursor != glob_state->dir_list->head) {
                glob_state->cursor = glob_state->cursor->prev;
                glob_state->term_curs++;
                u = true;
            }
            break;
        case LEFT:
            if(glob_state != init_glob_state) {
                glob_state = glob_state->tree_cursor->parent->p_state;
                u = true;
            }
            break;
        
        case RIGHT:
            pstate_t* new_state = search_state(glob_state->tree_cursor, glob_state->cursor->data);
            if(new_state == NULL) {
                new_state = mk_state();
                buffer_t* new_dir_list = get_buffer();
                
                if(!new_dir_list || !new_state) {
                    destroy_state(new_state);
                    destroy_buffer(new_dir_list);
                    return false;
                }

                char* cwd = glob_state->cursor->data;
                size_t size = glob_state->cursor->size;
                set_name(new_state, cwd, size);
                set_path(new_state, glob_state->cwd_path, new_state->cwd_name);

                new_state->dir_list = new_dir_list;
                if(!list_directories(new_state->dir_list, new_state->cwd_path)) {
                    // maybe add some sound here!
                    destroy_state(new_state);
                    destroy_buffer(new_dir_list);
                    return false;
                }
                new_state->cursor = new_state->dir_list->tail;
                new_state->tree_cursor = append(glob_state->tree_cursor, new_state);

                if(!new_state->tree_cursor) {
                    destroy_state(new_state);
                    destroy_buffer(new_dir_list);
                    return false;
                }
            }
            glob_state = new_state;
            u = true;
            break;
    }
    return u;
}