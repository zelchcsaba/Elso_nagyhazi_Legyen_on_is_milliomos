#ifndef JATEKMENTES_H
#define JATEKMENTES_H

#include "jatek.h"

#define KEY_UP 72

#define KEY_DOWN 80

typedef struct mentes{
    char nev[15+1];
    int perc;
    int masodperc;
    int szint;
    int nehezseg;
    struct mentes *elozo,*kov;
}mentes;

typedef struct menteselem{
    mentes *elso;
    mentes *utolso;
} menteselem;

void printmentesinfo(int x, menteselem q);
int jatekmentes(jatekinfo *info);
#endif
