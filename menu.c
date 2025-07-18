#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

#include "menu.h"
#include "kepernyofunkciok.h"
#include "rajzol.h"

void printmenuinfo(){

    hidecursor();

    clrscr();

    //ablak design
    setcolor(36);
    drawbox(1,1,30,120);

    setcolor(33);
    drawbox(15,10,15,40);

    setcolor(37);
    //megrajzolom a cimet
    drawmilliomos();

    //kiirom az informaciokat
    setcolor(37);
    gotoxy(17,12);
    printf("Játék indítása <s>");
    gotoxy(19,12);
    printf("Dicsöséglista <d>");
    gotoxy(21,12);
    printf("Elmentett játékállások betöltése <b>");
    gotoxy(23,12);
    printf("Új név megadása <u>");
    gotoxy(25,12);
    printf("Kilépés <x>");;

    showcursor();
}

char kivalasztmenu(){

    //bekerem a parancsot
    hidecursor();

    char c;
    c = getch();

    showcursor();

    return c;
}

void nevolvas(char *str){

    //megadom a nevet
    gotoxy(15,60);
    setcolor(37);
    printf("Add meg a neved: ");
    scanf("%15[0-9a-zA-ZáéúöüóíÁÉÚÖÜÓÍ ]",str);
    while (getchar() != '\n');
}

int parancsmenu(char parancs){

    //a beerkezett parancsnak megfeleloen visszaadok egy erteket
    switch(parancs){
        case 's':
            return 1;
        break;
        case 'd':
            return 2;
        break;
        case 'b':
            return 3;
        break;
        case 'u':
            return 4;
        break;
        case 'x':
            return -1;
        break;
        default:
            return 0;
        break;
    }
}

//menu info kiiratasa parancs bekerese, ez alapjan kovetkezo muveletre lep
int gomenu(){
     printmenuinfo();
     char p=kivalasztmenu();
     return parancsmenu(p);
}
