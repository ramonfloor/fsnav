#include <fsnav/tree.h>


tree_node_t* get_node() {
    tree_node_t* node = (tree_node_t*) malloc(sizeof(tree_node_t));
    if(node != NULL) {
        memset(node->children, 0, MAX_SUBDIR);
        node->num_children = 0;
        node->p_state = NULL;
        node->parent = NULL;
    }
    return node;
}

void destroy_tree_node(tree_node_t* tree_node) {
    free(tree_node);
}

state_tree_t* get_tree() {
    state_tree_t* tree = (state_tree_t*) malloc(sizeof(state_tree_t));
    return tree;
}

void empty_tree_helper(tree_node_t* node) {
    if(node != NULL) {
        if(node->num_children > 0) {
            for(int i = 0; i < node->num_children; i++) {
                empty_tree_helper(node->children[i]);
            }
        }
        destroy_buffer(node->p_state->dir_list);
        destroy_state(node->p_state);
        destroy_tree_node(node);
    }
}

void empty_tree(state_tree_t* tree) {
    if(tree != NULL) {
        tree_node_t* node = tree->root;
        if(node != NULL) {
            empty_tree_helper(node);
        }
    }
}

void destroy_tree(state_tree_t* tree) {
    if(tree != NULL) {
        empty_tree(tree);
        free(tree);
    }
}

bool append(tree_node_t* prnt, pstate_t* state) {
    bool success = false;
    tree_node_t* insrt = get_node();
    if(insrt != NULL) {
        insrt->parent = prnt;
        insrt->p_state = state;
        prnt->children[prnt->num_children] = insrt;
        prnt->num_children++;
        success = true;
    }
    return success;
}

void hlp_trv(tree_node_t* node) {
    if(node != NULL) {
        if(node->num_children > 0) {
            for(int i = 0; i < node->num_children; i++) {
                hlp_trv(node->children[i]);
            }
        }
        //printf("%p\n", node);
        //operation to be exectuted
    }
}

void pst_ord_trv(state_tree_t* tree) {
    if(tree != NULL) {
        hlp_trv(tree->root);
    }
}

bool search_state(tree_node_t* node, char* dir) {
    int ret = -1;
    for(int i = 0; i < MAX_SUBDIR; i++) {
        char* tmp = node->children[i]->p_state->cwd_name;
        if(!strcmp(tmp, dir)) {
            ret = i;
            break;
        }
    }
    return ret;
}