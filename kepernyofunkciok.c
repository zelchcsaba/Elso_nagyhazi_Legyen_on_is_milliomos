#include <stdio.h>
#include <conio.h>
#include <windows.h>

#include "kepernyofunkciok.h"

void gotoxy(int x,int y){
    printf("\033[%d;%dH", x, y);
}

//torol kepernyo
void clrscr(){
    system("cls");
}

//set betu szine
void setcolor(int szin){
    printf("\033[0;%dm",szin);
}

//eltunteti a kurzort
void hidecursor(){
    printf("\033[?25l");
}

//megjeleniti a kurzort
void showcursor(){
    printf("\033[?25h");
}
