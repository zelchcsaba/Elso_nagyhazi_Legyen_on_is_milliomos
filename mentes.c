#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <conio.h>

#include "mentes.h"
#include "lista.h"
#include "kepernyofunkciok.h"
#include "debugmalloc.h"

void printmentesinfo(int x, menteselem q){

    //kiirom a menteseket

    clrscr();

    gotoxy(2,50);
    printf("Játékmentések:");

    int i=4;
    mentes *mozgo;
    for(mozgo=q.elso->kov;mozgo!=q.utolso;mozgo=mozgo->kov){
        gotoxy(i,4);
        printf("Név: %15s \t Játékidö: %d min %d sec   \t Játékszint: %2d  \t Nehézseg: %d\n", mozgo->nev,mozgo->perc,mozgo->masodperc, mozgo->szint, mozgo->nehezseg);
        i+=1;
    }
    gotoxy(x+4, 2);
    printf("x");

    gotoxy(25,98);
    printf("Felfele léptet  <PgUp>");
    gotoxy(26,99);
    printf("Lefele léptet   <PgDn>");
    gotoxy(27,98);
    printf("Töröl              <d>");
    gotoxy(28,98);
    printf("Betölt játékmentés <b>");
    gotoxy(29,98);
    printf("Kilépés            <x>");
}

int jatekmentes(jatekinfo *info){

    hidecursor();
    //beolvasom a mentesadatokat
    menteselem lista;
    lista=beolvasmentes();

    char c;
    int p=0;
    bool kilep=false;
    //kivalasztom a lista elso elemet
    mentes *mozgo=lista.elso->kov;

    //bentmaradok ebben az ablakban, amig meg nem nyomom az x-et
    while (kilep==false){

        printmentesinfo(p,lista);
        c=getch();

        switch(c){
        case KEY_UP:
            //ha van elem a listaban, es nem az elso elem van kivalasztva, kivalasztom a lista elozo elemet
            if(mozgo!=lista.utolso){
                if(mozgo->elozo!=lista.elso){
                    p-=1;
                    mozgo=mozgo->elozo;
                }
            }
        break;
        case KEY_DOWN:
            //ha van elem a listaban, es nem az utolso elem van kivalasztva, kivalasztom a lista kovetkezo elemet
            if(mozgo!=lista.utolso){
                if(mozgo->kov!=lista.utolso){
                    p+=1;
                    mozgo=mozgo->kov;
                }
            }
        break;
        case 'd':
            //ha van elem a listaban, akkor kitorlom a kivalasztott elemet
            if(mozgo!=lista.utolso){
                mozgo->elozo->kov = mozgo->kov;
                mozgo->kov->elozo = mozgo->elozo;
                free(mozgo);
                mozgo=lista.elso->kov;
                p=0;
                ujrairmentesfajlba(&lista);
            }
        break;
        case 'b':
            if(mozgo!=lista.utolso){
                   strcpy(info->nev, mozgo->nev);
                   info->perc=mozgo->perc;
                   info->masodperc=mozgo->masodperc;
                   info->szint=mozgo->szint;
                   info->nehezseg=mozgo->nehezseg;
                   felszabaditmentes(lista.elso);
                   showcursor();
                   return 1;
            }
        break;
        case 'x':
            kilep=true;
        break;
        default:
        break;
        }

    }

    felszabaditmentes(lista.elso);

    showcursor();
    return 0;
}

