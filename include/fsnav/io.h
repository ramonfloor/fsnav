#ifndef IO_H
#define IO_H

#include <string.h>
#include <stdio.h>
#include <fsnav/buffer.h>
#include <fsnav/directory.h>


#define ROOT "/"

#define VERT_UNIT "\n|__ "

#define RESET "\e[0m"
#define RED "\e[1;31m"
#define GREEN "\e[1;32m"
#define BLUE "\e[1;34m"


void produce_output(char* cwd, buffer_t* dir_list) {
    printf(RED "%s" RESET, cwd);
    while(!empty(dir_list)) {
        printf(VERT_UNIT BLUE "%s" RESET, dequeue(dir_list));
    }
    printf("\n");
}

void listen() {
    int max_len = 120;
    char input[max_len];

    buffer_t* out_buffer = get_buffer();
    if(out_buffer != NULL) {
        buffer_t* dir_list = get_buffer();
        if(dir_list != NULL) {
            while(true)
            {
                fgets(input, max_len, stdin);
                input[strcspn(input, "\n")] = 0;
                if(!strcmp(input, "exit")) {
                    break;
                }
                list_directories(dir_list, input);
                produce_output(input, dir_list);
                empty_buffer(dir_list);
            }
            destroy_buffer(dir_list);
        }
        destroy_buffer(out_buffer);
    }
}

#endif