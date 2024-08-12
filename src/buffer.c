#include <fsnav/buffer.h>

bool empty(const buffer_t* const buffer) {
    bool ret = buffer->head == NULL & buffer->tail == NULL;
    return ret;
} 

bool enqueue(buffer_t* const buffer, void* data, size_t size) {
    bool return_value = false;
    buffer_node_t* node = (buffer_node_t*) malloc(sizeof(buffer_node_t));
    if(!(node == NULL)) {
        node->prev = NULL;
        node->prev = NULL;
        node->data = malloc(size);
        memcpy(node->data, data, size);
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

void* dequeue(buffer_t* const buffer) {
    void* return_value = NULL;
    if(!empty(buffer)) {
        return_value = buffer->tail->data;
        if(buffer->tail->prev != NULL) {
            buffer_node_t* tmp = buffer->tail->prev;
            free(buffer->tail->data);
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
    if(buffer != NULL) {
        buffer->head = NULL;
        buffer->tail = NULL;
    }
    return buffer;
}

void empty_buffer(buffer_t* const buffer) {
    if(!empty(buffer)) {
        buffer_node_t* node = buffer->head;
        while(node->next != NULL) {
            buffer_node_t* tmp = node->next;
            free(node->data);
            free(node);
            node = tmp;
        }
        free(node->data);
        free(node);
    }
    buffer->head = NULL;
    buffer->tail = NULL;
}

void destroy_buffer(buffer_t* const buffer) {
    empty_buffer(buffer);
    free(buffer);
}

iterator* get_iterator(const buffer_t* const buffer) {
    iterator* iter = NULL;
    if(!empty(buffer)) {
        iter = (iterator*) malloc(sizeof(iterator));
        if(iter != NULL) {
            iter->next = buffer->tail;
        }
    }
    return iter;
}

void destroy_iterator(iterator* const iter) {
    free(iter);
}

//going direction tail to head, first element at tail
buffer_node_t* next(iterator* iter) {
    buffer_node_t* return_value = NULL;
    if(iter->next != NULL) {
        buffer_node_t* tmp = iter->next;
        iter->next = tmp->prev; //iterator goes backwards
        return_value = tmp;
    }
    return return_value;
}

void print_buffer(buffer_t* const buffer) {
    iterator iter = {buffer->tail};
    if(&iter != NULL) {
        while(iter.next != NULL) {
            printf("%s\n", next(&iter)->data);
        }
    }
}
