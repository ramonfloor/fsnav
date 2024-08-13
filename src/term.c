#include <fsnav/term.h>

extern pstate_t* glob_state;
extern buffer_t* ctrl_buffer;
extern sem_t* ctrl_lock;
//extern pthread_mutex_t exit_mut;

struct termios term;


void mv_crs(int line, int collumn) {
    printf(ESC "%d;%dH", line, collumn);
}

void reset_term() {
    mv_crs(0,0);
    printf(ERS);
    term.c_lflag |= ECHO;
    tcsetattr(fileno(stdin), 0, &term);
    printf(SHOW_CURS);
    fflush(stdout);
}

void next_scr() {
    mv_crs(0, 0);
    printf(ERS);

    printf(BOLD RED "%s" RESET, glob_state->cwd_path);
    buffer_node_t* temp = glob_state->dir_list->tail;
    while(temp != glob_state->cursor) {
        printf(BOLD RED NEWLINE VERT_UNIT RESET HOR_UNIT"%s", temp->data);
        temp = temp->prev;
    }
    printf(BOLD RED NEWLINE VERT_UNIT HOR_UNIT "%s" RESET, temp->data);
    temp = temp->prev;
    while(temp != NULL) {
        printf(NEWLINE VERT_UNIT HOR_UNIT"%s", temp->data);
        temp = temp->prev;
    }
    mv_crs(glob_state->term_curs, 0);
    fflush(stdout);
}

bool init_scr() {
    tcgetattr(fileno(stdin), &term);
    term.c_lflag &= ~ECHO;
    tcsetattr(fileno(stdin), 0, &term);
    printf(HIDE_CURS);
    
    next_scr();
    return true;
}

void update_scr(enum KEY key) {
    switch(key) {
        case UP:
            mv_crs(glob_state->term_curs + 1, 0);
            printf(ERS_LN);
            printf(VERT_UNIT HOR_UNIT "%s", glob_state->cursor->prev->data);
            mv_crs(glob_state->term_curs, 0);
            printf(BOLD RED VERT_UNIT HOR_UNIT "%s" RESET, glob_state->cursor->data);
            break;
        case DOWN:
            mv_crs(glob_state->term_curs - 1, 0);
            printf(ERS_LN);
            printf(BOLD RED VERT_UNIT RESET HOR_UNIT "%s", glob_state->cursor->next->data);
            mv_crs(glob_state->term_curs, 0);
            printf(BOLD RED VERT_UNIT HOR_UNIT "%s" RESET, glob_state->cursor->data);
            break;
    }
    fflush(stdout);
}

void next_state(enum KEY key) {
    bool u = false;
    switch(key) {
        case UP:
            u = update_state(UP);
            if(u) {
                update_scr(UP);
            }
            break;
        case DOWN:
            u = update_state(DOWN);
            if(u) {
                update_scr(DOWN);
            }
            break;
        case LEFT:
            update_state(LEFT);
            next_scr();
            break;
        case RIGHT:
            update_state(RIGHT);
            next_scr();
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