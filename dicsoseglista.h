#ifndef DICSOSEGLISTA_H
#define DICSOSEGLISTA_H

typedef struct dicsoseg{
    char nev[15+1];
    int perc;
    int masodperc;
    int nyeremeny;
    struct dicsoseg *kov;
}dicsoseg;

void printdicsoseginfo(dicsoseg *e);
int dicsoseglista();
#endif

