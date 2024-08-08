#ifndef IO_H
#define IO_H

#include <string.h>
#include <stdio.h>
#include <linux/input.h>
#include <fcntl.h>

#include <fsnav/buffer.h>
#include <fsnav/directory.h>
#include <fsnav/tree.h>
#include <fsnav/structures.h>


#define ROOT_STR "/"
#define ROOT_CHAR '/'

#define VERT_UNIT "\n|"
#define HOR_UNIT "__ "
#define COMMAND ">>> "

#define RESET "\e[0m"
#define RED "\e[1;31m"
#define GREEN "\e[1;32m"
#define BLUE "\e[1;34m"

#define CLEAR_SCR() printf("\033[H\033[J")


#define DEVICE "/dev/input/event6" //On my system event6 is keyboard input, may differ on your system!


buffer_t* ctrl_buffer;
iterator* dir_iter;
extern sem_t buffer_lock;

state_t* programm_state;

void produce_output() {
    iterator* iter = get_iterator(programm_state->dir_list);

    CLEAR_SCR();
    fflush(stdout);

    if(iter != NULL) {
        printf(RED "%s" RESET, programm_state->cwd_path);
        while(iter->next != NULL) {
            printf(VERT_UNIT HOR_UNIT "%s", go_backwards(iter)->data);
        }
    }
    fflush(stdout);
}

void initialize() {
    programm_state = (state_t*) malloc(sizeof(state_t));
    if(programm_state != NULL) {
        ctrl_buffer = get_buffer();
        if(ctrl_buffer != NULL) {
            programm_state->dir_list = get_buffer();
            if(programm_state->dir_list != NULL) {
                programm_state->cwd_name = ROOT_STR;
                programm_state->cwd_path[0] = ROOT_CHAR;
                programm_state->parent_dir = ROOT_STR;
                programm_state->parent_dir_path[0] = ROOT_CHAR;
                programm_state->last_key = NO_KEY;

                list_directories(programm_state->dir_list, ROOT_STR);
                dir_iter = get_iterator(programm_state->dir_list);
                if(dir_iter != NULL) {
                    programm_state->cursor = programm_state->dir_list->tail;

                    CLEAR_SCR();
                    printf(RED ROOT_STR RESET "\n");
                    fflush(stdout);
                } else {
                    destroy_buffer(programm_state->dir_list);
                }
            } else {
                destroy_buffer(ctrl_buffer);
            }
        } else {
            free(programm_state);
        }
    }
}

void destroy() {
    destroy_buffer(programm_state->dir_list);
    destroy_buffer(ctrl_buffer);
    destroy_iterator(dir_iter);
    free(programm_state);
}

void listen() {
    int fd = open(DEVICE, O_RDONLY);
    if(fd != -1) {
        while(true) {
            struct input_event input;
            ssize_t ret = read(fd, &input, sizeof(struct input_event));
            if(ret > 0) {
                if(input.type == EV_KEY && (input.value == 0 || input.value == 2)) {
                    long code = input.code;
                    enqueue(ctrl_buffer, (void*) code);
                    sem_post(&buffer_lock);
                }
            }
        }
        close(fd);
    }
}

void next_state(enum KEY key) {
    buffer_node_t* next_curs;
    switch(key) {
        case UP:
            if(programm_state->last_key == DOWN) {
                go_forwards(dir_iter);
                go_forwards(dir_iter);
            }
            next_curs = go_forwards(dir_iter);
            if(dir_iter->next == NULL) {
                dir_iter->next = programm_state->cursor;
            }
            programm_state->cursor = next_curs;
            programm_state->last_key = UP;
            produce_output();
            break;
        case DOWN:
            if(programm_state->last_key == UP) {
                go_backwards(dir_iter);
                go_backwards(dir_iter);
            }
            next_curs = go_backwards(dir_iter);
            if(dir_iter->next == NULL) {
                dir_iter->next = programm_state->cursor;
            }
            programm_state->cursor = next_curs;
            programm_state->last_key = DOWN;
            produce_output();
            break;
        case LEFT:
            break;
        case RIGHT:
            memset(programm_state->parent_dir_path, 0, sizeof(programm_state->parent_dir_path));
            memcpy(programm_state->parent_dir_path, programm_state->cwd_path, sizeof(programm_state->cwd_path));
            programm_state->parent_dir = programm_state->cwd_name;

            strcat(programm_state->cwd_path, programm_state->cursor->data);
            strcat(programm_state->cwd_path, "/");

            programm_state->cwd_name = programm_state->cursor->data;
            programm_state->last_key = RIGHT;

            empty_buffer(programm_state->dir_list);
            list_directories(programm_state->dir_list, programm_state->cwd_path);
            if(programm_state->dir_list->head != NULL) {
                if(programm_state->dir_list != NULL) {
                    programm_state->cursor = programm_state->dir_list->tail;
                    produce_output();
                } else {
                    fprintf(stderr, "Something went wrong with malloc\n");    
                    exit(1);
                }
            } else {
                printf("Not a directory.\n");
            }
            break;
    }
}

void input_handler() {
    while(true) {
        sem_wait(&buffer_lock);
        long c = (long) dequeue(ctrl_buffer);
        switch(c) {
            case UP:
                next_state(UP);
                break;
            case DOWN:
                next_state(DOWN);
                break;
            case LEFT:
                next_state(LEFT);
                break;
            case RIGHT:
                next_state(RIGHT);
                break;
        }
    }
}

#endif