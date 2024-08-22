#include <fsnav/term.h>

extern pstate_t* glob_state;
extern buffer_t* ctrl_buffer;
extern sem_t* ctrl_lock;

struct termios std, term; 

struct termios term;

void reset_term() {
    MV_CURS(0,0);
    printf(ERS SHOW_CURS);
    tcsetattr(STDIN_FILENO, 0, &std);
    fflush(stdout);
}


void next_scr() {
    MV_CURS(0, 0);

    printf(ERS BOLD YELLOW "%s" RESET, glob_state->_cwd_path);
    buffer_node_t* temp = glob_state->_dir_list->_tail;
    while(temp != glob_state->_cursor) {
        printf(BOLD YELLOW NEWLINE VERT_UNIT RESET "%s", temp->_data);
        temp = temp->_prev;
    }
    printf(BOLD YELLOW NEWLINE VERT_POINTER HOR_UNIT "%s" RESET, temp->_data);
    temp = temp->_prev;
    while(temp != NULL) {
        printf(NEWLINE VERT_UNIT "%s", temp->_data);
        temp = temp->_prev;
    }
    MV_CURS(glob_state->_term_curs, 0);
    fflush(stdout);
}

bool init_scr() {
    tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHO | ICANON | IEXTEN);
	term.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
	tcsetattr(STDIN_FILENO, 0, &term);
    printf(HIDE_CURS);
    
    next_scr();
    return true; 
}

void update_scr(enum KEY key) {
    switch(key) {
        case UP:
            MV_CURS(glob_state->_term_curs + 1, 0);
            printf(ERS_LN);
            printf(VERT_UNIT "%s", glob_state->_cursor->_prev->_data);
            MV_CURS(glob_state->_term_curs, 0);
            printf(BOLD YELLOW VERT_POINTER HOR_UNIT "%s" RESET, glob_state->_cursor->_data);
            break;
        case DOWN:
            MV_CURS(glob_state->_term_curs - 1, 0);
            printf(ERS_LN);
            printf(BOLD YELLOW VERT_UNIT RESET "%s", glob_state->_cursor->_next->_data);
            MV_CURS(glob_state->_term_curs, 0);
            printf(BOLD YELLOW VERT_POINTER HOR_UNIT "%s" RESET, glob_state->_cursor->_data);
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
    }
}

static inline void key_handler(long key_code, bool* run, int fd) {
    switch(key_code) {
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
            *run = false;
            break;
    }
}

void key_listener() {
    bool run = true;
    int fd = open(DEVICE, O_RDONLY);
    if(fd != -1) {
        while(run) {
            struct input_event input;
            ssize_t ret = read(fd, &input, sizeof(struct input_event));
            if(ret > 0) {
                if(input.type == EV_KEY && (input.value == 0 || input.value == 2)) {
                    long key_code = input.code;
                    key_handler(key_code, &run, fd);
                }
            }
        }
        close(fd);
    }
}
