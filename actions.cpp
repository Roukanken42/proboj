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
        return Prikaz::chod (actor.id, actor.x, actor.y);
    };

    Action (Zivocich actor) {
        this->id = ACTION_ID++;
        this->actor = actor;
    }

    Action () {
        this->id = ACTION_ID++;
    }

};

struct CollectItemsOnGround: public Action {
    Quest targetQuest;
    vector <vector<int> > bfsdata;


    void QuestSelect(){
        if (!QuestExist(targetQuest)){
            for(Quest quest: stav.questy){
                for (Quest_spec item: get_Quest_spec(quest)){

                }
            }
        }
    }

    Prikaz get_command(){
        vector<vector<int>> bfsdata;
        bfs(bfsdata, Bod(actor));

        QuestSelect ();
        if ()
    }
};


