
#include "bod.cpp"

#define For(q,w) for(int q=0; q<w; q++)

extern int ja;   // ktory hrac som
extern Mapa mapa;

extern Stav stav;
extern Tah mojTah;
extern vector<Bod> d_cka;


vector<vector<vector<int> > > vzdialenostOdMiest;
vector<Bod> mesta;

void basic_function_setMap();
void bfs(vector<vector<int> > &nazov, Bod bod);
void bfs(vector<vector<int> > &nazov, Bod bod, vector <vector<int> > &beware);
int sgn(int c);
void inicializujZoznamMiest();
void preratajVzdialenostOdMiest();    // zavolat!!!1
Zivocich findLifeByID(int ID);
int vratCislomesta(Bod m);
vector<Quest_spec> get_Quest_spec(Quest);
bool QuestExist(Quest);

template <class T> int find_item_by_x_y (vector<T > &data, Bod b);

vector<vector<vector<vector<int>>>> bfsdatamem;

vector<vector<int>>& bfsmem (Bod a){
    bfs(bfsdatamem[a.x][a.y], a);
    return a.get(bfsdatamem);
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
            /*if((tar.get(mapa) > 0) && (tar.get(nazov) > pom.get(nazov) + 1) ) {
                tar.get(nazov) = pom.get(nazov)+1;
                haldicka.push(tar);
            }*/

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
            /*if((tar.get(mapa) > 0) && (tar.get(nazov) > pom.get(nazov) + 1) ) {
                tar.get(nazov) = pom.get(nazov)+1;
                haldicka.push(tar);
            }*/

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

void inicializujZoznamMiest () {
    for (int y = 0; y < mapa.h; y++) {
        for (int x = 0; x < mapa.w; x++) {
            if (mapa.zisti(x, y) == MAPA_MESTO) {
                mesta.push_back(Bod(x, y));
            }
        }
    }
}

void preratajVzdialenostOdMiest(){

    vzdialenostOdMiest.resize(mesta.size());
    for(int i=0; i<mesta.size();i++){
        bfs(vzdialenostOdMiest[i], Bod(mesta[i]));

    }

}

Zivocich findLifeByID(int ID){
    for (auto ziv: stav.zivocichy){
        if (ziv.id == ID) return ziv;
    }

    return stav.zivocichy[0];
}

int vratCislomesta(Bod m){
    for(int i=0; i<mesta.size(); i++){
        if(mesta[i]==m) return i;

    }
    return -1;
}

vector<Quest_spec> get_Quest_spec(Quest q){

    vector<Quest_spec> pole;

    bool found = false;
    for(auto na_zemi: stav.predmety){
        if( na_zemi.typ == q.ziadanyPredmet){
                pole.push_back( Quest_spec(0, Bod(), Bod(na_zemi).get(vzdialenostOdMiest[vratCislomesta(Bod(q.cielX, q.cielY))])) );
        }

    }

    return pole;
}

bool QuestExist(Quest q){

    bool found=false;

    for(auto pom_q: stav.questy){
        if(q.ziadanyPredmet == pom_q.ziadanyPredmet && ( pom_q.cielX == q.cielX && pom_q.cielY == q.cielY  ) ){
            found=true;
        }
    }

    return found;

}


template <class T> int find_by_x_y (vector<T > &data, Bod b){

    For(i,data.size()){

        if( Bod (data[i].x, data[i].y) == b ){
            return i;
        }
    }

}



