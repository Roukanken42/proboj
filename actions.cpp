#include "common.h"
#include "basic_function.cpp"

#define vykonaj(p) vykonajPrikaz(mapa, stav, mojTah, (p))

int ACTION_ID = 0;

extern int ja;   // ktory hrac som
extern Mapa mapa;

extern Tah tah;
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

        return zistiApCenu(mapa,stav,tah,);
    }

    Prikaz get_command () {
        return Prikaz::chod (actor.id, actor.x, actor.y);
    };

    void execute () {
        vykonaj (this->get_command());
    }

    Action (Zivocich actor) {
        this->id = ACTION_ID++;
        this->actor = actor;
    }

    Action () {
        this->id = ACTION_ID++;
    }

};

bool asdfghjkl (pair <Quest, Quest_spec> a, pair <Quest, Quest_spec> b){
    return (a.first.zlato - (double)a.second.vzdialenost_k_mestu/10)*1000 / a.second.vzdialenost_k_mestu >
    (b.first.zlato - (double)b.second.vzdialenost_k_mestu/10)*1000 / b.second.vzdialenost_k_mestu;
}


struct CollectItems: public Action {
    Quest targetQuest;
    Quest_spec targetItem;

    vector <vector<int> > bfsdata;


    void QuestSelect(){
        if (!QuestExist(targetQuest)){
            vector <pair <Quest, Quest_spec>> data;

            for(Quest quest: stav.questy){
                Quest_spec target_item = getBestItem(quest);
                if (target_item.item_owner != -1) data.push_back(make_pair(quest, target_item));
            }

            sort (data.begin(), data.end(), asdfghjkl);
            if (data.size() > 1) {
                targetItem = data[1].second;
                targetQuest = data[1].first;
            }
            else if (data.size() > 0){
                targetItem = data[0].second;
                targetQuest = data[0].first;
            }
        }
    }

    Prikaz get_command(){
        bfsdata = bfsmem(Bod(actor));

        QuestSelect ();
        Bod target = targetItem.poz;
        if (actor.nesenyPredmet == targetQuest.ziadanyPredmet) target = Bod (targetQuest.cielX, targetQuest.cielY);

        int v = target.get(bfsdata);
        Bod next;
        for (auto smer: d_cka){
            if ((smer + target).get(bfsdata) < v) {
                next = smer + target;
                v = (smer + target).get(bfsdata);
            }
        }

        return Prikaz::chod(actor.id, next.x, next.y);
    }

};


