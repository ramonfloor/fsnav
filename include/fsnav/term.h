/*
    functions and macros for program output on terminal
*/

#ifndef TERM_H
#define TERM_H

/*======================*/
/* Include header files */ 
/*======================*/

#include <termios.h>
#include <stdio.h>

#include <fsnav/buffer.h>
#include <fsnav/tree.h>
#include <fsnav/enum.h>

/*=======================*/
/* General screen macros */
/*=======================*/

#define RESET "\033[0m"

/*========================*/
/* Macros cursor movement */
/*========================*/

#define ESC "\033["
#define CURS_ZERO "\033[H"
#define MV_ONE_UP "\033[1A"
#define MV_ONE_DOWN "\033[1B"
#define CR "\015"

/*=====================*/
/* Macros erase screen */
/*=====================*/

#define ERS "\033[0J"
#define ERS_LN "\033[0K"

/*=====================*/
/* Macros output units */
/*=====================*/

#define VERT_UNIT "\n|"
#define HOR_UNIT "__ "
#define COMMAND ">>> "

/*===================*/
/* Macros for colors */
/*===================*/

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m"
#define BLUE "\033[34m"
#define WHITE "\033[37m"

/*=======================*/
/* Macros for text style */
/*=======================*/

#define BOLD "\033[1m"
#define ITALIC "\033[3m"


void mv_crs(int line, int collumn) {
    printf(ESC "%d;%dH", line, collumn);
}

/*
    Draw next state to the screen
*/
void update_scr() {

}

#endif