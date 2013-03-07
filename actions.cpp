#include "common.h"
#include "basic_function.cpp"

int ACTION_ID = 0;

extern int ja;   // ktory hrac som
extern Mapa mapa;

extern Stav stav;
extern Tah mojTah;


//basic action
struct Action {
    int id;
    Zivocich actor;

    double get_priority (){
        return 0;
    }

    int get_ap (){
        int NOT_IMPLEMENTED = -1;
        return NOT_IMPLEMENTED;
    }

    Prikaz get_command () {

    };

    Action (Zivocich actor) {
        this->id = ACTION_ID++;
        this->actor = actor;
    }

    Action () {
        this->id = ACTION_ID++;
    }

};

struct CollectItems: public Action {
    Quest targetQuest;

    void QuestSelect(){
        if (!QuestExist(targetQuest)){

        }
    }

    Prikaz get_command(){
        QuestSelect ();

    }
};


