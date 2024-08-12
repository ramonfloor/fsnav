#include <fsnav/state.h>

pstate_t* mk_state() {
    pstate_t* s = (pstate_t*) malloc(sizeof(pstate_t));
    if(s != NULL) {
        s->cursor = NULL;
        memset(s->cwd_name, 0, sizeof(s->cwd_name));
        memset(s->cwd_path, 0, sizeof(s->cwd_path));
        s->dir_list = NULL;
        s->tree_cursor = NULL;
    }
    return s;
}

/*
    Remember to free members of s first! (buffer)
*/
void destroy_state(pstate_t* s) {
    free(s);
}

void set_name(pstate_t* state, char* cwd) {
    memset(state->cwd_name, 0, MAX_NAME_SIZE);
    memcpy(state->cwd_name, cwd, strlen(cwd)); //last character has to be '\0'
}

void set_path(pstate_t* state, char* parent, char* cwd) {
    char tmp1[MAX_PATH_SIZE];
    strcpy(tmp1, parent);
    char tmp2[MAX_PATH_SIZE];
    if(cwd != NULL) {
        strcpy(tmp2, cwd);
        strcat(tmp1, "/");
        strcat(tmp1, tmp2);
    }
    memcpy(state->cwd_path, tmp1, MAX_PATH_SIZE);
}