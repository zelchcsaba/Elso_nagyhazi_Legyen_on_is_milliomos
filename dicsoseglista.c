#include <stdio.h>
#include <stdbool.h>
#include <conio.h>

#include "dicsoseglista.h"
#include "lista.h"
#include "kepernyofunkciok.h"
#include "debugmalloc.h"

void printdicsoseginfo(dicsoseg *e){

    //kiirom a dicsoseglistat
    clrscr();

    gotoxy(2,50);
    printf("Dics�s�glista:");

    int i=4;
    int j=1;
    dicsoseg *mozgo;
    for(mozgo=e; mozgo!=NULL; mozgo=mozgo->kov){
        gotoxy(i,2);
        printf("%d.",j);
        gotoxy(i,6);
        printf("N�v: %15s \t J�t�kid�: %d min %d sec \t Nyerem�ny: %8d Ft\n", mozgo->nev,mozgo->perc,mozgo->masodperc, mozgo->nyeremeny);
        i+=1;
        j+=1;
    }

    gotoxy(29,108);
    printf("Kil�p�s <x>");
}

int dicsoseglista(){

    hidecursor();
    //beolvasom a dicsoseglistat
    dicsoseg *eleje;
    eleje = beolvasdicsoseg();

    char c;
    bool kilep=false;

    //bentmaradok ebben az ablakban, amig meg nem nyomom az x-et
    while (kilep==false){

        printdicsoseginfo(eleje);
        c=getch();

        if (c=='x'){
            kilep=true;
        }

    }

    //felszabaditom a lefoglalt memoriat
    felszabaditdicsoseg(eleje);
    showcursor();

    return 0;
}

