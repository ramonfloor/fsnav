#include <fsnav/buffer.h>

bool empty(const buffer_t* const buffer) {
    bool ret = buffer->_head == NULL & buffer->_tail == NULL;
    return ret;
} 

bool enqueue(buffer_t* const buffer, void* data, size_t size) {
    bool return_value = false;
    buffer_node_t* node = (buffer_node_t*) malloc(sizeof(buffer_node_t));
    if(!(node == NULL)) {
        node->_prev = NULL;
        node->_next = NULL;
        node->_size = size;
        node->_data = malloc(size);
        if(node->_data == NULL) {
            exit(1);
        }
        for(size_t i = 0; i < size; i++) {
            *(char*)(node->_data + i) = *(char*)(data + i);
        }
        if(empty(buffer)) {
            node->_next = NULL;
            buffer->_head = node;
            buffer->_tail = node;
        } else {
            node->_next = buffer->_head;
            buffer->_head->_prev = node;
            buffer->_head = node;
        }
        return_value = true;
    }
    return return_value;
}

void* dequeue(buffer_t* const buffer) {
    void* return_value = NULL;
    if(!empty(buffer)) {
        return_value = buffer->_tail->_data;
        if(buffer->_tail->_prev != NULL) {
            buffer_node_t* tmp = buffer->_tail->_prev;
            free(buffer->_tail);
            buffer->_tail = tmp;
            buffer->_tail->_next = NULL;
        } else {
            free(buffer->_tail);
            buffer->_tail = NULL;
            buffer->_head = NULL;
        }
    }
    return return_value;
}

buffer_t* get_buffer() {
    buffer_t* buffer = (buffer_t*) malloc(sizeof(buffer_t));
    if(buffer != NULL) {
        buffer->_head = NULL;
        buffer->_tail = NULL;
    }
    return buffer;
}

void empty_buffer(buffer_t* const buffer) {
    if(buffer) {
        while(!empty(buffer)) {
            free(dequeue(buffer));
        }
    }
}

void destroy_buffer(buffer_t* const buffer) {
    if(buffer) {
        empty_buffer(buffer);
        free(buffer);
    }
}

void print_buffer(buffer_t* const buffer) {
    buffer_node_t* n = buffer->_tail;
    if(n) {
        while(n) {
            printf("%s\n", n->_data);
            n = n->_prev;
        }
    }
}
