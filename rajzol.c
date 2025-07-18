#include <stdio.h>
#include <stdlib.h>
#include "rajzol.h"
#include "kepernyofunkciok.h"

//rajzolok egy teglalapot
void drawbox(int x, int y, int magassag, int hossz){

    //kirajzol szelei
    for (int i=x+1;i<magassag+x-1;i++){
        gotoxy(i,y);
        printf("|");
        gotoxy(i,hossz+y-1);
        printf("|");
    }

    for (int i=y+1;i<hossz+y-1;i++){
        gotoxy(x,i);
        printf("-");
        gotoxy(magassag+x-1,i);
        printf("-");
    }

    //kirajzol sarkai
    gotoxy(x,y);
    printf("/");
    gotoxy(x,hossz+y-1);
    printf("\\");
    gotoxy(magassag+x-1,y);
    printf("\\");
    gotoxy(magassag+x-1,hossz+y-1);
    printf("/");

}

//rajzolok egy vonalat
void drawline(int x,int y,int hossz){
    for(int i=y;i<hossz+y-1;i++){
        gotoxy(x,i);
        printf("-");
    }
}

//kirajzol milliomos
void drawmilliomos(){
    gotoxy(5,10);
    printf("                                    . .\n");
    gotoxy(6,10);
    printf("      ___  ___        ___           ___             ___                         ___          ___   ___\n");
    gotoxy(7,10);
    printf("|    |    |    \\   / |     |\\  |   |   | |\\  |   | |      |\\  /| | |    |    | |   | |\\  /| |   | |    \n");
    gotoxy(8,10);
    printf("|    |___ | _   \\ /  |___  | \\ |   |   | | \\ |   | |__    | \\/ | | |    |    | |   | | \\/ | |   | |__\n");
    gotoxy(9,10);
    printf("|    |    |  |   |   |     |  \\|   |   | |  \\|   |    |   |    | | |    |    | |   | |    | |   |    |\n");
    gotoxy(10,10);
    printf("|___ |___ |__|   |   |___  |   |   |___| |   |   | ___|   |    | | |___ |___ | |___| |    | |___| ___|");
}

