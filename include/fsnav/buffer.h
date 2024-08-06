#ifndef BUFFER_H
#define BUFFER_H

#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>

typedef struct node {
    struct node* next;
    struct node* prev;
    void* data;
} node_t;

typedef struct buffer {
    struct node* head;
    struct node* tail;
} buffer_t;

bool empty(buffer_t* buffer) {
    return buffer->head == NULL;
} 

bool enqueue(buffer_t* buffer, void* data) {
    bool return_value = false;
    node_t* node = (node_t*) malloc(sizeof(node_t));
    if(!(node == NULL)) {
        node->prev = NULL;
        node->data = data;
        if(empty(buffer)) {
            node->next = NULL;
            buffer->head = node;
            buffer->tail = node;
        } else {
            node->next = buffer->head;
            buffer->head->prev = node;
            buffer->head = node;
        }
        return_value = true;
    }
    return return_value;
}

//returns empty character \0 in case buffer is empty
void* dequeue(buffer_t* buffer) {
    void* return_value = NULL;
    if(!empty(buffer)) {
        return_value = buffer->tail->data;
        if(buffer->tail->prev != NULL) {
            node_t* tmp = buffer->tail->prev;
            free(buffer->tail);
            buffer->tail = tmp;
            buffer->tail->next = NULL;
        } else {
            free(buffer->tail);
            buffer->tail = NULL;
            buffer->head = NULL;
        }
    }
    return return_value;
}

buffer_t* get_buffer() {
    buffer_t* buffer = (buffer_t*) malloc(sizeof(buffer_t));
    return buffer;
}

void empty_buffer(buffer_t* buffer) {
    if(!empty(buffer)) {
        node_t* node = buffer->head;
        while(node->next != NULL) {
            node_t* tmp = node->next;
            free(node);
            node = tmp;
        }
        free(node);
    }
    buffer->head = NULL;
    buffer->tail = NULL;
}

void destroy_buffer(buffer_t* buffer) {
    empty_buffer(buffer);
    free(buffer);
}

#endif