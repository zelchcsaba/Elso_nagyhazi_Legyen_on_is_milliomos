#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>

#include "jatek.h"
#include "kepernyofunkciok.h"
#include "rajzol.h"
#include "lista.h"
#include "debugmalloc.h"

void init(jatekinfo *info){
    info->nev[0]='\0';
    info->perc=0;
    info->masodperc=0;
    info->szint=1;
    info->nehezseg=0;
}

void printnehezseginfo(){

    hidecursor();

    clrscr();
    //kiirom a nehezseg kivalaszto ablakot
    setcolor(37);
    gotoxy(10,56);
    printf("Nehézség");
    gotoxy(14,25);
    printf("könnyü <1>");
    gotoxy(14,55);
    printf("közepes <2>");
    gotoxy(14,85);
    printf("nehéz <3>");

    showcursor();
}

void printjatekinfo(int x, char *nev){

    hidecursor();

    clrscr();

    //ablak design
    setcolor(36);
    drawbox(1,1,30,120);

    setcolor(33);
    drawbox(2,90,19,28);

    //kerdesinfonek doboz
    drawbox(21,10,3,100);
    drawbox(24,20,3,35);
    drawbox(27,20,3,35);
    drawbox(24,65,3,35);
    drawbox(27,65,3,35);

    //kiirom az informaciokat
    setcolor(37);
    gotoxy(6,5);
    printf("Válaszok: <A B C D>");
    gotoxy(8,5);
    printf("Játék mentése: <m>");
    gotoxy(10,5);
    printf("Kérdések felezése: <f>");
    gotoxy(12,5);
    printf("Közönség szavazat <k>");
    gotoxy(15,5);
    printf("Kilépés <x>");
    gotoxy(17,5);
    printf("Válasz:");
    gotoxy(4,5);
    printf("Név: %s", nev);

    //kiirom a kerdesinfo betujet
    gotoxy(25,22);
    printf("A");
    gotoxy(28,22);
    printf("B");
    gotoxy(25,67);
    printf("C");
    gotoxy(28,67);
    printf("D");

    //kiirom a szinteket es az ehhez tartozo osszeget
    gotoxy(4,92);
    printf("15      40.000.000 FT");
    gotoxy(5,92);
    printf("14      20.000.000 FT");
    gotoxy(6,92);
    printf("13      10.000.000 FT");
    gotoxy(7,92);
    printf("12       5.000.000 FT");
    gotoxy(8,92);
    printf("11       3.000.000 FT");
    gotoxy(9,92);
    printf("10       1.500.000 FT");
    gotoxy(10,92);
    printf(" 9         800.000 FT");
    gotoxy(11,92);
    printf(" 8         500.000 FT");
    gotoxy(12,92);
    printf(" 7         300.000 FT");
    gotoxy(13,92);
    printf(" 6         200.000 FT");
    gotoxy(14,92);
    printf(" 5         100.000 FT");
    gotoxy(15,92);
    printf(" 4          50.000 FT");
    gotoxy(16,92);
    printf(" 3          25.000 FT");
    gotoxy(17,92);
    printf(" 2          10.000 FT");
    gotoxy(18,92);
    printf(" 1           5.000 FT");
    gotoxy(19,92);
    printf("                 0 FT");
    //megjelolom azt, amelyik kerdesnel tartok a jatekban
    setcolor(31);
    gotoxy(19-x, 91);
    printf("x");
    gotoxy(20-x,91);
    printf("-");
    gotoxy(20-x,113);
    printf("-");

    showcursor();
}

void printkerdesinfo(kerdesinfo seged){

    //kiirom a kerdesinfoet
    hidecursor();
    setcolor(37);
    gotoxy(22,12);
    printf("%s",seged.kerdes);
    gotoxy(25,24);
    printf("%s",seged.a);
    gotoxy(28,24);
    printf("%s",seged.b);
    gotoxy(25,69);
    printf("%s",seged.c);
    gotoxy(28,69);
    printf("%s",seged.d);

    showcursor();
}

void printkozonseginfo(int *t){

    //kiirom a kozonseg szavazatat
    hidecursor();
    setcolor(37);
    gotoxy(7,53);
    printf("Közönség");
    gotoxy(10,38);
    printf("A:");
    gotoxy(10,48);
    printf("B:");
    gotoxy(10,58);
    printf("C:");
    gotoxy(10,68);
    printf("D:");
    gotoxy(10,40);
    printf("%d",t[0]);
    gotoxy(10,50);
    printf("%d",t[1]);
    gotoxy(10,60);
    printf("%d",t[2]);
    gotoxy(10,70);
    printf("%d",t[3]);

    showcursor();
}

void printwin(int penz){

    hidecursor();

    clrscr();
    setcolor(33);
    drawbox(1,1,30,120);
    setcolor(37);
    gotoxy(5,30);
    printf("Gratulálunk, ön milliomos lett. Nyereménye %d FT",penz);
    gotoxy(6,45);
    printf("Nyomjon meg egy gombot");
    getch();

    showcursor();
}
void printlose(int penz){

    hidecursor();

    clrscr();
    setcolor(31);
    drawbox(1,1,30,120);
    setcolor(37);
    gotoxy(5,30);
    printf("Ön sajnos most nem vitte végig a játékot de nyereménye %d FT",penz);
    gotoxy(6,45);
    printf("Nyomjon meg egy gombot");
    getch();

    showcursor();
}

char kivalasztnehezseg(){
    //bekerem a parancsot
    hidecursor();

    char c;
    c = getch();
    while(c-'0'<1||c-'0'>3){
        c = getch();
    }

    showcursor();

    return c;
}

//pontosvesszoig masol stringbe
void masol(char *s1, char *s2,int *i){
    int j=0;
    while (s2[*i]!=';' && s2[*i]!='\0'){
        s1[j]=s2[*i];
        *i+=1;
        j+=1;
    }s1[j]='\0';*i+=1;
}

//a lancolt listaban levo sort felbonotm es egy strukturaba helyezem
kerdesinfo atalakit(char *s){
    kerdesinfo seged;

    char tar[100];
    int k=0;

    masol(tar,s,&k);
    int nszint=atoi(tar);

    if(nszint<=5){
        seged.nehezseg=1;
    }else if(nszint<=10){
        seged.nehezseg=2;
    }else{
        seged.nehezseg=3;
    }

    masol(tar,s,&k);
    strcpy(seged.kerdes,tar);

    masol(tar,s,&k);
    strcpy(seged.a,tar);

    masol(tar,s,&k);
    strcpy(seged.b,tar);

    masol(tar,s,&k);
    strcpy(seged.c,tar);

    masol(tar,s,&k);
    strcpy(seged.d,tar);

    masol(tar,s,&k);
    seged.valasz=tar[0];

    masol(tar,s,&k);
    strcpy(seged.kategoria,tar);

    return seged;
}

//megfelezem a kerdesinfoet
void felez(kerdesinfo *p){
    if(p->valasz!='A'){
        p->a[0]='\0';
        if(p->valasz!='B'){
            p->b[0]='\0';
        }else{
            p->c[0]='\0';
        }
    }else{
        p->b[0]='\0';
        p->c[0]='\0';
    }
}

//eloallitom a kozonseg szavazatat
void kozonsegszavaz(int *t, char helyesvalasz){
    for(int i=0;i<4;i++){
        t[i]=rand()%100;
    }
    t[helyesvalasz-'A']=rand()%70+50;
}

//kiszamolom a jatekban toltott idot
void elteltido(time_t k_ido, int *minute, int *sec){
    time_t mostani_ido=time(0);
    int delta_ido = (int) mostani_ido - (int) k_ido;

    *minute = delta_ido/60;
    *sec = delta_ido%60;

}


//a jatek fuggvenye
int gojatek(jatekinfo jatek){

    //megnez ha van-e nev
    //ha nincs beker nev
    if (strcmp(jatek.nev,"")==0){
        return 4;

    //ha van beker nehezseg
    }else if(jatek.nehezseg==0){
        printnehezseginfo();
        jatek.nehezseg=kivalasztnehezseg()-'0';
    }
    //bekapcsol random
    srand(time(0));

    //beolvas kerdesinfo a megadott nehezseg szerint
    sor *eleje=NULL;
    int db=0;
    eleje=beolvaskerdes(jatek.nehezseg,&db);

    //programbeli valtozok
    int kerdesno;
    kerdesinfo kinfo;
    int szavazatk[4];
    char parancs;

    //nyeremenyek szint szerint
    int osszegtomb[15]={5000,10000,25000,50000,100000,200000,300000,500000,800000,1500000,3000000,5000000,10000000,20000000,40000000};
    int nyeremeny;
    if(jatek.szint!=1){
        nyeremeny=osszegtomb[jatek.szint-2];
    }else{
        nyeremeny=0;
    }

    bool win=false;
    bool kilep = false;
    bool kovkerdes=true;
    bool kozonseg=false;
    bool voltfelez=false;
    bool voltkozonseg=false;

    //kiszamit ido
    time_t kezdeti_ido=time(0)-(60*jatek.perc+jatek.masodperc);


    //maga a jatek
    while (kilep==false && jatek.perc<30){

        //kiszamitom a jatekban toltott idot
        elteltido(kezdeti_ido, &jatek.perc,&jatek.masodperc);

        if(kovkerdes==true){
            //kivalaszt kerdes random
            kerdesno=rand()%db;

            //megkeresem a listaaban a kerdest

            sor *mozgo=eleje;
            for (int i = 1; i<kerdesno; i++){
                mozgo=mozgo->kov;
            }

            //a listaban levo sort behelyezem egy strukturaba
            kinfo=atalakit(mozgo->str);
        }

    //kiirom a kerdest es a jatekinformaciokat
    printjatekinfo(jatek.szint,jatek.nev);
    printkerdesinfo(kinfo);
    gotoxy(2,7);
    printf("%d:%d",jatek.perc, jatek.masodperc);
    //ha kertem a kozonseg szavazatat kiirom ezt
    if (kozonseg==true){
        printkozonseginfo(szavazatk);
        kozonseg=false;
    }

    //beolvasom a valaszt vagy a parancsot
    gotoxy(17,14);
    scanf(" %c",&parancs);
    //kitorol buffer
    while (getchar() != '\n');

    switch (parancs){
    //valaszok
    case 'A':
    case 'B':
    case 'C':
    case 'D':
        //ha eltalaltam a helyes valaszt
        if(parancs==kinfo.valasz){
            nyeremeny=osszegtomb[jatek.szint-1];
            jatek.szint+=1;
            kovkerdes=true;
        //ha nem talaltam el kilepek
        }else{
            kilep=true;
        }
    break;

    //jatek mentese
    case 'm':
        elteltido(kezdeti_ido, &jatek.perc,&jatek.masodperc);
        mentesfajlba(&jatek);
        kovkerdes=false;
    break;

    //felezem a kerdeseket
    case 'f':
        if(voltfelez==false){
            felez(&kinfo);
            voltfelez=true;
        }
        kovkerdes=false;
    break;

    //kerem a kozonseg szavazatat
    case 'k':
        if(voltkozonseg==false){
            kozonsegszavaz(szavazatk,kinfo.valasz);
            kozonseg=true;
            voltkozonseg=true;
        }
        kovkerdes=false;
    break;

    //kilepes
    case 'x':
        kilep=true;
    break;

    //ha nem a fenti parancsok valamelyikere kattintottam nem csinalok semmit
    default:
        kovkerdes=false;
    break;
    }

    //megnezem, ha nem ertem-e haladtam el a legfelso szintet, ekkor nyereseg van
    if (jatek.szint==16){
        kilep=true;
        win=true;
    }

}
    if(win==true){
        printwin(nyeremeny);
    }else{
        printlose(nyeremeny);
    }

    elteltido(kezdeti_ido, &jatek.perc,&jatek.masodperc);
    beirdicsoseg(jatek.nev,jatek.perc,jatek.masodperc,nyeremeny);
    felszabaditkerdes(eleje);

    return 0;

}
