/*
    These functions are primarily used for directory names
*/

#ifndef STRBUILDER_H
#define STRBUILDER_H


typedef struct strbld {
    int cap;
    char* str;
} strbld_t;

/*
    Append src string to dest string builder
*/
void append(strbld_t* dest, char* src) {

}

/*
    Convert content of strbld to a string and save in dest
*/
void to_str(strbld_t* strbld, char* dest) {

}

#endif