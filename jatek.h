#ifndef JATEK_H
#define JATEK_H

typedef struct kerdesinfo{
    int nehezseg;
    char kerdes[100];
    char a[30];
    char b[30];
    char c[30];
    char d[30];
    char valasz;
    char kategoria[20];
}kerdesinfo;

typedef struct jatekinfo{
    char nev[15+1];
    int perc;
    int masodperc;
    int szint;
    int nehezseg;
}jatekinfo;

void init(jatekinfo *info);
void printnehezseginfo();
void printjatekinfo(int x, char *nev);
void printkerdesinfo(kerdesinfo seged);
void printkozonseginfo(int *t);
void printwin(int penz);
void printlose(int penz);

char kivalasztnehezseg();
void masol(char *s1, char *s2,int *i);
kerdesinfo atalakit(char *s);
void felez(kerdesinfo *p);
void kozonsegszavaz(int *t, char helyesvalasz);
void elteltido(time_t k_ido, int *minute, int *sec);
int gojatek(jatekinfo jatek);

#endif
