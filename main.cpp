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

struct Bod {
    int x, y;

    template <class T>
    T& get (vector<vector<T>> &data);
    int get (Mapa data);

    Bod operator+ (Bod a) {
        return Bod(this->x+a.x, this->y+a.y);
    }

    bool operator== (Bod a) {
        return (a.x == this->x) && (a.y == this->y);
    }

    Bod (int x, int y) {
        this->x = x;
        this->y = y;
    }

    template <class T>
    Bod (T data) {
        this->x = data.x;
        this->y = data.y;
    }

    Bod () {}    //Shut up Code::Blocks
};

template <class T>
T& Bod::get (vector<vector<T>> &data) {
    return data[x][y];
}

int Bod::get (Mapa data) {
    return data.zisti(x, y);
}






int ja;   // ktory hrac som
Mapa mapa;

Stav stav;
Tah mojTah;
vector<Bod> d_cka= {{-1,0},{-1,1},{-1,-1},{0,1},{0,-1},{1,0},{1,1},{1,-1}};


int sgn(int c);
void bfs(vector<vector<int> > &nazov, Bod bod);
void bfs(vector<vector<int> > &nazov, Bod bod, vector <vector<int> > &beware);


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



void bfs(vector<vector<int> > &nazov, Bod bod) {

    nazov.clear();
    nazov.resize(mapa.w,vector<int> (mapa.h,100908));
    queue<Bod> haldicka;


    haldicka.push(bod);
    bod.get(nazov)=0;
    int pocet = 0;

    while(!haldicka.empty()) {
        Bod pom = haldicka.front();
        haldicka.pop();

        for(auto pos: d_cka) {
            Bod tar = pos + pom;

            if((mapa.zisti(tar.x, tar.y) > 0) && (nazov[tar.x][tar.y] > nazov[pom.x][pom.y] + 1) ) {
                nazov[tar.x][tar.y] = nazov[pom.x][pom.y]+1;
                haldicka.push(tar);
            }
        }
    }
}

void bfs(vector<vector<int> > &nazov, Bod bod, vector<vector<int> > &beware) {

    nazov.clear();
    nazov.resize(mapa.w,vector<int> (mapa.h,100908));
    queue<Bod> haldicka;


    haldicka.push(bod);
    bod.get(nazov)=0;
    int pocet = 0;

    while(!haldicka.empty()) {
        Bod pom = haldicka.front();
        haldicka.pop();

        for(auto pos: d_cka) {
            Bod tar = pos + pom;

            if((mapa.zisti(tar.x, tar.y) > 0) && (nazov[tar.x][tar.y] > nazov[pom.x][pom.y] + 1) ) {
                if (beware[tar.x][tar.y] == 1) continue;
                nazov[tar.x][tar.y] = nazov[pom.x][pom.y]+1;
                haldicka.push(tar);
            }
        }
    }
}

int sgn(int c) {
    if (c < 0) return -1;
    if (c > 0) return 1;
    return 0;
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


