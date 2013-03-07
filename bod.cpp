
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

struct Quest_spec{
    int item_owner;  // -1- invalid, 0 - zem, 1- prisera, 2- hrac;
    Bod poz;
    int vzdialenost_k_mestu;

    Quest_spec(int, Bod, int);
    Quest_spec();
};


Quest_spec::Quest_spec(int a, Bod b, int c){

    this->item_owner=(a);
    this->poz=(b);
    this->vzdialenost_k_mestu=(c);
}

Quest_spec::Quest_spec (){
    this->item_owner=(-1);
    this->poz=(-1,-1);
    this->vzdialenost_k_mestu=(100000);
}
