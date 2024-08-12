#include <fsnav/term.h>

void mv_crs(int line, int collumn) {
    printf(ESC "%d;%dH", line, collumn);
}

bool init_scr(pstate_t* state) {
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