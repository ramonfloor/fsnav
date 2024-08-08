#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <linux/input.h>

#define MAX_CHILDREN 250


typedef struct buffer_node {
    struct buffer_node* next;
    struct buffer_node* prev;
    void* data;
} buffer_node_t;

typedef struct buffer {
    buffer_node_t* head;
    buffer_node_t* tail;
} buffer_t;

typedef struct iterator {
    buffer_node_t* next;
} iterator;

enum KEY {
    UP = KEY_UP,
    DOWN = KEY_DOWN,
    LEFT = KEY_LEFT,
    RIGHT = KEY_RIGHT,
    NO_KEY
};

typedef struct state {
    char* cwd_name;
    char cwd_path[4096];
    char* parent_dir;
    char parent_dir_path[4096];
    buffer_t* dir_list;
    buffer_node_t* cursor;
    enum KEY last_key;
} state_t;

typedef struct tree_node {
    buffer_t* children;
    struct tree_node* parent;
    state_t* p_state;
} tree_node_t;

typedef struct state_tree {
    tree_node_t* root;
} state_tree_t;

#endif