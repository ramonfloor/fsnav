#include <fsnav/tree.h>


tree_node_t* get_node() {
    tree_node_t* node = (tree_node_t*) malloc(sizeof(tree_node_t));
    if(node) {
        memset(node->_children, 0, MAX_SUBDIR);
        node->_num_children = 0;
        node->_p_state = NULL;
        node->_parent = NULL;
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
    if(node) {
        if(node->_num_children > 0) {
            for(int i = 0; i < node->_num_children; i++) {
                empty_tree_helper(node->_children[i]);
            }
        }
        destroy_buffer(node->_p_state->_dir_list);
        destroy_state(node->_p_state);
        destroy_tree_node(node);
    }
}

void empty_tree(state_tree_t* tree) {
    if(tree) {
        tree_node_t* node = tree->_root;
        if(node) {
            empty_tree_helper(node);
        }
    }
}

void destroy_tree(state_tree_t* tree) {
    if(tree) {
        empty_tree(tree);
        free(tree);
    }
}

tree_node_t* append(tree_node_t* prnt, pstate_t* state) {
    tree_node_t* insrt = get_node();
    if(insrt) {
        insrt->_parent = prnt;
        insrt->_p_state = state;
        prnt->_children[prnt->_num_children] = insrt;
        prnt->_num_children++;
    }
    return insrt;
}

void hlp_trv(tree_node_t* node) {
    if(node) {
        if(node->_num_children > 0) {
            for(int i = 0; i < node->_num_children; i++) {
                hlp_trv(node->_children[i]);
            }
        }
        //printf("%p\n", node);
        //operation to be exectuted
    }
}

void pst_ord_trv(state_tree_t* tree) {
    if(tree) {
        hlp_trv(tree->_root);
    }
}

pstate_t* search_state(tree_node_t* node, char* dir) {
    pstate_t* ret = NULL;
    int i = 0;
    while(node->_children[i]) {
        char* tmp = node->_children[i]->_p_state->_cwd_name;
        if(!strcmp(tmp, dir)) {
            ret = node->_children[i]->_p_state;
            break;
        }
        ++i;
    }
    return ret;
}