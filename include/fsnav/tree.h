/*
    Tree that saves program_states. That way travelling through the file system is
    way easier and faster in case a directory is visited multiple times. Also it solves
    the problem of saving the parent_directories name.

    Each node in the tree can have multiple children.
*/

#ifndef TREE_H
#define TREE_H

#include <fsnav/structures.h>


tree_node_t* get_node() {
    tree_node_t* node = (tree_node_t*) malloc(sizeof(tree_node_t));
    if(node != NULL) {

    }
}

state_tree_t* get_tree() {
    state_tree_t* tree = (state_tree_t*) malloc(sizeof(state_tree_t));
    if(tree != NULL) {

    }
    return tree;
}

#endif