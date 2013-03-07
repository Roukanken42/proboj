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

struct CollectItems: public Action {
    Quest targetQuest;

    vector <vector<int> > bfsdata;


    void QuestSelect(){
        if (!QuestExist(targetQuest)){
            vector <pair <Quest, Quest_spec>> data;

            for(Quest quest: stav.questy){
                Quest_spec target_item = getBestItem(quest);
                if (target_item.item_owner != -1) data.push_back(make_pair(quest, target_item));
            }

            for (auto x: data){


            }
        }
    }

    Prikaz get_command(){
        bfsdata = bfsmem(Bod(actor));

        QuestSelect ();
    }
};


