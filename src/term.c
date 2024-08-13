#include <fsnav/term.h>


extern buffer_t* ctrl_buffer;
extern sem_t* ctrl_lock;
//extern pthread_mutex_t exit_mut;


void mv_crs(int line, int collumn) {
    printf(ESC "%d;%dH", line, collumn);
}

void reset_term() {
    printf(SHOW_CURS);
}

bool init_scr(pstate_t* state) {
    printf(HIDE_CURS);
    mv_crs(0, 0);
    printf(ERS);
    fflush(stdout);

    printf(BOLD RED "%s" RESET, state->cwd_name);
    buffer_node_t* temp = state->dir_list->tail;
    while(temp != NULL) {
        printf(VERT_UNIT HOR_UNIT "%s", temp->data);
        temp = temp->prev;
    }
    puts("");

    return true;
}

void update_scr(pstate_t* state) {
    
}

void next_state(enum KEY key) {
    switch (key) {
        case UP:
            puts("UP");
            break;
        case DOWN:
            puts("DOWN");
            break;
        case LEFT:
            puts("LEFT");
            break;
        case RIGHT:
            puts("RIGHT");
            break;
        case KEY_ESC:
            exit(0);
            break;
    }
}

void key_handler() {
    bool run = true;
    while(run) {
        sem_wait(ctrl_lock);
        void* data = dequeue(ctrl_buffer);
        long key_code = *(long*)data;
        switch (key_code) {
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
            case KEY_ESC:
                run = false;
                //pthread_mutex_unlock(&exit_mut);
        }
        free(data);
    }
}