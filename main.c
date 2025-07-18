#include <stdio.h>
#include <stdlib.h>
#ifdef _WIN32
#include <windows.h>
#endif

#include "menu.h"
#include "jatek.h"
#include "kepernyofunkciok.h"
#include "debugmalloc.h"
#include "dicsoseglista.h"
#include "mentes.h"

int main(){
    #ifdef _WIN32
    SetConsoleCP(1250);
    SetConsoleOutputCP(1250);
    #endif
    int status=0;
    jatekinfo jinfo;
    init(&jinfo);


    while (status!=-1){
        switch(status){
        case 0:
            status=gomenu();
        break;

        case 1:
            status=gojatek(jinfo);
            init(&jinfo);
        break;
        case 2:
            status=dicsoseglista();
        break;
        case 3:
            status=jatekmentes(&jinfo);
        break;
        case 4:
            nevolvas(jinfo.nev);
            status=0;
        break;
        }
    }

    clrscr();
    return 0;


}
