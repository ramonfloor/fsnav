#ifndef BUFFER_H
#define BUFFER_H

#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>


typedef struct buffer_node {
    struct buffer_node* next;
    struct buffer_node* prev;
    void* data;
    size_t size;
} buffer_node_t;

typedef struct buffer {
    buffer_node_t* head;
    buffer_node_t* tail;
} buffer_t;

typedef struct iterator {
    buffer_node_t* next;
} iterator;


bool empty(const buffer_t* const buffer);

bool enqueue(buffer_t* const buffer, void* data, size_t size);

void* dequeue(buffer_t* const buffer);

buffer_t* get_buffer();

void empty_buffer(buffer_t* const buffer);

void destroy_buffer(buffer_t* const buffer);

iterator* get_iterator(const buffer_t* const buffer);

void destroy_iterator(iterator* const iter);

//going direction tail to head, first element at tail
buffer_node_t* next(iterator* const iter);

void print_buffer(buffer_t* const buffer);

#endif