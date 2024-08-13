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

#include <fsnav/state.h>
#include <fsnav/buffer.h>

typedef struct pstate pstate_t;

#define MAX_SUBDIR 65000

typedef struct tree_node {
    struct tree_node* children[MAX_SUBDIR];
    struct tree_node* parent;
    pstate_t* p_state;
    int num_children;
} tree_node_t;

typedef struct state_tree {
    tree_node_t* root;
} state_tree_t;

tree_node_t* get_node();
void destroy_tree_node(tree_node_t* tree_node);

state_tree_t* get_tree();

void empty_tree_helper(tree_node_t* node);

void empty_tree(state_tree_t* tree);

void destroy_tree(state_tree_t* tree);

/*
    Append a program state to the tree by an enqueue to the children buffer.
    CAREFUL: This is not a normal insert operation of a tree. 
*/
tree_node_t* append(tree_node_t* prnt, pstate_t* state);

void hlp_trv(tree_node_t* node);

void pst_ord_trv(state_tree_t* tree);

/*
    Sequentally search through the children of node, if one of the child nodes
    contains pstate with cwd equal to dir, return true, else false. 
*/
pstate_t* search_state(tree_node_t* node, char* dir);

#endif