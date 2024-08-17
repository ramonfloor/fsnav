#include <fsnav/state.h>

pstate_t* mk_state() {
    pstate_t* s = (pstate_t*) malloc(sizeof(pstate_t));
    if(s != NULL) {
        s->_term_curs = 2;
        s->_cursor = NULL;
        memset(s->_cwd_name, 0, sizeof(s->_cwd_name));
        memset(s->_cwd_path, 0, sizeof(s->_cwd_path));
        s->_dir_list = NULL;
        s->_tree_cursor = NULL;
    }
    return s;
}

/*
    Remember to free members of s first! (buffer)
*/
void destroy_state(pstate_t* s) {
    if(s){
        free(s);
    }
}

void set_name(pstate_t* state, char* cwd, size_t size) {
    memset(state->_cwd_name, 0, MAX_NAME_SIZE);
    memcpy(state->_cwd_name, cwd, size); //last character has to be '\0'
}

void set_path(pstate_t* state, char* parent, char* cwd) {
    char tmp1[MAX_PATH_SIZE];
    strcpy(tmp1, parent);
    char tmp2[MAX_PATH_SIZE];
    if(cwd != NULL) {
        strcpy(tmp2, cwd);
        if(!strcmp(tmp2, "/")) {
            strcat(tmp1, "/");
        }
        strcat(tmp1, tmp2);
        strcat(tmp1, "/");
    }
    memcpy(state->_cwd_path, tmp1, MAX_PATH_SIZE);
}