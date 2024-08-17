#include <fsnav/term.h>

extern pstate_t* glob_state;
extern buffer_t* ctrl_buffer;
extern sem_t* ctrl_lock;
//extern pthread_mutex_t exit_mut;

struct termios term;

void reset_term() {
    MV_CURS(0,0);
    printf(ERS);
    term.c_lflag |= ECHO;
    tcsetattr(fileno(stdin), 0, &term);
    printf(SHOW_CURS);
    fflush(stdout);
}

void next_scr() {
    MV_CURS(0, 0);
    printf(ERS);

    printf(BOLD YELLOW "%s" RESET, glob_state->_cwd_path);
    buffer_node_t* temp = glob_state->_dir_list->_tail;
    while(temp != glob_state->_cursor) {
        printf(BOLD YELLOW NEWLINE VERT_UNIT RESET HOR_UNIT"%s", temp->_data);
        temp = temp->_prev;
    }
    printf(BOLD YELLOW NEWLINE VERT_UNIT HOR_UNIT "%s" RESET, temp->_data);
    temp = temp->_prev;
    while(temp != NULL) {
        printf(NEWLINE VERT_UNIT HOR_UNIT"%s", temp->_data);
        temp = temp->_prev;
    }
    MV_CURS(glob_state->_term_curs, 0);
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
            MV_CURS(glob_state->_term_curs + 1, 0);
            printf(ERS_LN);
            printf(VERT_UNIT HOR_UNIT "%s", glob_state->_cursor->_prev->_data);
            MV_CURS(glob_state->_term_curs, 0);
            printf(BOLD YELLOW VERT_UNIT HOR_UNIT "%s" RESET, glob_state->_cursor->_data);
            break;
        case DOWN:
            MV_CURS(glob_state->_term_curs - 1, 0);
            printf(ERS_LN);
            printf(BOLD YELLOW VERT_UNIT RESET HOR_UNIT "%s", glob_state->_cursor->_next->_data);
            MV_CURS(glob_state->_term_curs, 0);
            printf(BOLD YELLOW VERT_UNIT HOR_UNIT "%s" RESET, glob_state->_cursor->_data);
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