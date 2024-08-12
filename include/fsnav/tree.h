/*
    Tree that saves program_states. That way travelling through the file system is
    way easier and faster in case a directory is visited multiple times. Also it solves
    the problem of saving the parent_directories name.

    Each node in the tree can have multiple children.
*/

#ifndef TREE_H
#define TREE_H

#include <stdlib.h>
#include <stdbool.h>

#include <fsnav/buffer.h>
#include <fsnav/state.h>


typedef struct tree_node {
    buffer_t* children;
    struct tree_node* parent;
    pstate_t* p_state;
} tree_node_t;

typedef struct state_tree {
    tree_node_t* root;
} state_tree_t;

tree_node_t* get_node() {
    tree_node_t* node = (tree_node_t*) malloc(sizeof(tree_node_t));
    if(node != NULL) {
        node->parent = NULL;
        node->p_state = NULL;
        node->children = get_buffer();
        if(node->children == NULL) {
            free(node);
            node = NULL;
        }
    }
    return node;
}

void destroy_tree_node(tree_node_t* tree_node) {
    destroy_state(tree_node->p_state);
    destroy_buffer(tree_node->children);
    free(tree_node);
}

state_tree_t* get_tree() {
    state_tree_t* tree = (state_tree_t*) malloc(sizeof(state_tree_t));
    return tree;
}

void empty_tree_helper(tree_node_t* node) {
    if(node != NULL) {
        if(!empty(node->children)) {
            iterator iter = {node->children->tail};
            while(iter.next != NULL) {
                empty_tree_helper(next(&iter)->data);
            }
        }
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

/*
    Append a program state to the tree by an enqueue to the children buffer.
    CAREFUL: This is not a normal insert operation of a tree. 
*/
bool append(tree_node_t* prnt, pstate_t* p_state) {
    bool success = false;
    tree_node_t* insrt = get_node();
    if(insrt != NULL) {
        insrt->parent = prnt;
        insrt->p_state = p_state;
        enqueue(prnt->children, insrt);
        success = true;
    }
    return success;
}

void hlp_trv(tree_node_t* node) {
    if(node != NULL) {
        if(!empty(node->children)) {
            iterator iter = {node->children->tail};
            while(iter.next != NULL) {
                hlp_trv(next(&iter)->data);
            }
        }
        printf("%p\n", node);
    }
}

void pst_ord_trv(state_tree_t* tree) {
    if(tree != NULL) {
        hlp_trv(tree->root);
    }
}

/*
    Sequentally search through the children of node, if one of the child nodes
    contains pstate with cwd equal to dir, return true, else false. 
*/
bool search_state(tree_node_t* node, char* dir) {
    iterator iter = {node->children->tail};
    bool ret = false;
    while(iter.next != NULL) {
        char* tmp = ((tree_node_t*)(next(&iter)->data))->p_state->cwd_name;
        if(!strcmp(tmp, dir)) {
            ret = true;
            break;
        }
    }
    return ret;
}

#endif