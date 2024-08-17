#ifndef BUFFER_H
#define BUFFER_H

#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>


typedef struct buffer_node {
    struct buffer_node* _next;
    struct buffer_node* _prev;
    void* _data;
    size_t _size;
} buffer_node_t;

typedef struct buffer {
    buffer_node_t* _head;
    buffer_node_t* _tail;
} buffer_t;


bool empty(const buffer_t* const buffer);

bool enqueue(buffer_t* const buffer, void* data, size_t size);

void* dequeue(buffer_t* const buffer);

buffer_t* get_buffer();

void empty_buffer(buffer_t* const buffer);

void destroy_buffer(buffer_t* const buffer);

void print_buffer(buffer_t* const buffer);

#endif