#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "lista.h"
#include "debugmalloc.h"

sor *beolvaskerdes(int nehezseg, int *darab){

    //megnyitom a fajlt olvasasra
    FILE *f;
    f = fopen("kerdesek.csv", "r");
     if (f == NULL) {
        perror("Nem sikerült megnyitni a kerdes fajlt");
    }

    //a beolvasashoz szukseges valtozok
    char fsor[200];
    char *enter;
    int nszint;
    sor *uj;
    sor *e=NULL;
    int hossz;

    //amig nem ertem a fajl vegere olvasom a sorokat
    while(fgets(fsor,200,f)){

        //a beolvasott sorbol kinullazom a /n-et
        enter = strchr(fsor, '\n');
        if (enter != NULL)
            *enter = '\0';

        //kiolvasom a nehezsegi szintet
        nszint=fsor[0]-'0';
        if (isdigit(fsor[1])){
            nszint=nszint*10+(fsor[1]-'0');
        }
        //ha a kiolvasott nszint megegyezik a nehezseggel, akkorbeszurom a sort a lista ere
        if(nszint==nehezseg){

            uj = (sor*) malloc(sizeof(sor));
            hossz=strlen(fsor)+1;
            uj->str=(char*)malloc(hossz*sizeof(char));
            strcpy(uj->str,fsor);

            if(e==NULL){
                uj->kov = NULL;
                e=uj;

            }else{
                uj->kov = e;
                e = uj;
            }
            *darab+=1;
        }
    }
    //visszaadom a lista ere mutato pointert
    return e;
    //bezarom a fajlt
    fclose(f);
}


dicsoseg *beolvasdicsoseg(){

    //megnyitom a fajlt olvasasra
    FILE *f;
    f = fopen("dicsoseg.txt", "r");
     if (f == NULL) {
        perror("Nem sikerült megnyitni a dicsoseg fajlt");
    }

    //a beolvasashoz szukseges valtozok
    char fsor[100];
    char *enter;
    dicsoseg *uj;
    dicsoseg *e=NULL;

    //amig nem ertem a fajl vegere olvasom a sorokat
    while(fgets(fsor,100,f)){

        //a beolvasott sorbol kinullazom a /n-et
        enter = strchr(fsor, '\n');
        if (enter != NULL)
            *enter = '\0';

        char tar[30];
        int k=0;

        uj = (dicsoseg*) malloc(sizeof(dicsoseg));

        //feltoltom a beolvasott elemekkel az uj strukturat
        masol(tar,fsor,&k);
        strcpy(uj->nev,tar);
        masol(tar,fsor,&k);
        uj->perc=atoi(tar);
        masol(tar,fsor,&k);
        uj->masodperc=atoi(tar);
        masol(tar,fsor,&k);
        uj->nyeremeny=atoi(tar);

        //rendezve szurom be az uj elemet a listaba
        dicsoseg *lemarado=NULL;
        dicsoseg *mozgo=e;

        while (mozgo != NULL && mozgo->nyeremeny > uj->nyeremeny) {
            lemarado = mozgo;
            mozgo = mozgo->kov;
        }
        if (lemarado == NULL) {
            uj->kov = e;
            e = uj;
        }else{
            lemarado->kov = uj;
            uj->kov = mozgo;
        }
    }

    //visszaadom a lista ere mutato pointert
    return e;
    //bezarom a fajlt
    fclose(f);
}

menteselem beolvasmentes(){

    //megnyitom a fajlt olvasasra
    FILE *f;
    f = fopen("mentes.txt", "r");
     if (f == NULL) {
        perror("Nem sikerult megnyitni a mentes fajlt");
    }

    //a beolvasashoz szukseges valtozok
    char fsor[100];
    char *enter;
    mentes *uj;
    menteselem q;

    //lefoglalom a memoriat a strazsa elemeknek
    q.elso = (mentes*) malloc(sizeof(mentes));
    q.utolso = (mentes*) malloc(sizeof(mentes));

    q.elso->kov=q.utolso;
    q.elso->elozo=NULL;
    q.utolso->elozo=q.elso;
    q.utolso->kov=NULL;

    //amig nem ertem a fajl vegere olvasom a sorokat
    while(fgets(fsor,100,f)){

        //a beolvasott sorbol kinullazom a /n-et
        enter = strchr(fsor, '\n');
        if (enter != NULL)
            *enter = '\0';


        char tar[30];
        int k=0;

        uj = (mentes*) malloc(sizeof(mentes));

        //feltoltom a beolvasott elemekkel az uj strukturat
        masol(tar,fsor,&k);
        strcpy(uj->nev,tar);
        masol(tar,fsor,&k);
        uj->perc=atoi(tar);
        masol(tar,fsor,&k);
        uj->masodperc=atoi(tar);
        masol(tar,fsor,&k);
        uj->szint=atoi(tar);
        masol(tar,fsor,&k);
        uj->nehezseg=atoi(tar);

        //beszurom a duplan lancolt listam elejere az uj elemet
        mentes *mozgo = q.elso->kov;

        uj->elozo = mozgo->elozo;
        uj->kov = mozgo;
        mozgo->elozo->kov = uj;
        mozgo->elozo = uj;
    }

    //visszaadom a lista elso es utolso elemere mutato strukturat
    return q;
    //bezarom a fajlt
    fclose(f);
}

void beirdicsoseg(char *nev, int m, int s, int osszeg){

    //megnyitom a fajlt irasra, a kurzort a fajl vegere helyezem
    FILE *f;
    f = fopen("dicsoseg.txt", "a");
     if (f == NULL) {
        perror("Nem sikerült megnyitni a fajlt");
    }
    fprintf(f,"%s;%d;%d;%d\n",nev,m,s,osszeg);

    //bezarom a fajlt
    fclose(f);
}

void mentesfajlba(jatekinfo *info){

    //megnyitom a fajlt olvasasra
    FILE *f;
    f = fopen("mentes.txt", "a");
     if (f == NULL) {
        perror("Nem sikerült megnyitni a fajlt");
    }
    fprintf(f,"%s;%d;%d;%d;%d\n",info->nev,info->perc,info->masodperc,info->szint,info->nehezseg);

    //bezarom a fajlt
    fclose(f);
}

void ujrairmentesfajlba(menteselem *info){

    //megnyitom a fajlt irasra
    FILE *f;
    f = fopen("mentes.txt", "w");
     if (f == NULL) {
        perror("Nem sikerült megnyitni a fajlt");
    }

    //visszairom a mentesadatokat a fajlba
    mentes *mozgo;
    for(mozgo=info->utolso->elozo; mozgo!=info->elso; mozgo=mozgo->elozo){
        fprintf(f,"%s;%d;%d;%d;%d\n",mozgo->nev,mozgo->perc,mozgo->masodperc,mozgo->szint,mozgo->nehezseg);
    }
    //bezarom a fajlt
    fclose(f);
}


//felszabaditom a lefoglalt memoriateruletet
void felszabaditkerdes(sor *e){
    //felszabaditom a kerdesek listajat
    sor *iter;
    iter = e;
    while (iter != NULL){
        free(iter->str);
        sor *kov = iter->kov;
        free(iter);
        iter = kov;
    }

}

void felszabaditdicsoseg(dicsoseg *e){
    //felszabaditom a dicsoseg listat
    dicsoseg *iter;
    iter = e;
    while (iter != NULL){
        dicsoseg *kov = iter->kov;
        free(iter);
        iter = kov;
    }

}

void felszabaditmentes(mentes *e){
    //felszabaditom a mentes listat
    mentes *iter;
    iter = e;
    while (iter != NULL){
        mentes *kov = iter->kov;
        free(iter);
        iter = kov;
    }

}

