#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <unistd.h>
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;

#include "common.h"
#include "marshal.h"
#include "update.h"

#include "debug.cpp"
#include "actions.cpp"

#define vykonaj(p) vykonajPrikaz(mapa, stav, mojTah, (p))


int ja;   // ktory hrac som
Mapa mapa;

Stav stav;
Tah mojTah;
vector<Bod> d_cka= {{-1,0},{-1,1},{-1,-1},{0,1},{0,-1},{1,0},{1,1},{1,-1}};


void inicializuj() {
    debug_init();

    adddf("Initialize");

    debug("started");
    debug ("finished");

    unddf();
}

void zistiTah() {

    setdf("Clock");
    ss << stav.cas;
    debug();

    setdf ("Actualize");

    debug ("started");
    debug("finished");
}


int main() {
    // v tejto funkcii su vseobecne veci, nemusite ju menit (ale mozte).

    unsigned int seed = time(NULL) * getpid();
    srand(seed);

    nacitaj(cin, ja);
    nacitaj(cin, mapa);
    fprintf(stderr, "START ja=%d, pid=%d, seed=%u\n", ja, getpid(), seed);
    inicializuj();

    while (cin.good()) {
        nacitaj(cin, stav);
        mojTah = zaciatokTahu(stav, ja);
        zistiTah();
        uloz(cout, mojTah.prikazy);
        cout << ".\n" << flush;   // bodka a flush = koniec odpovede
    }

    return 0;
}


