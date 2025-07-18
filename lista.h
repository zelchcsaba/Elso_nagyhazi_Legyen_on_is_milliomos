#ifndef LISTA_H
#define LISTA_H

#include "dicsoseglista.h"
#include "mentes.h"
#include "jatek.h"

typedef struct sor{
    char *str;
    struct sor *kov;
}sor;

sor *beolvaskerdes(int nehezseg, int *darab);
dicsoseg *beolvasdicsoseg();
menteselem beolvasmentes();
void beirdicsoseg(char *nev, int m, int s, int osszeg);
void mentesfajlba(jatekinfo *info);
void ujrairmentesfajlba(menteselem *info);
void felszabaditkerdes(sor *e);
void felszabaditdicsoseg(dicsoseg *e);
void felszabaditmentes(mentes *e);

#endif
