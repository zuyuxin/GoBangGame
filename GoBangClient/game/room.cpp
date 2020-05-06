#include "game/room.h"

Room::Room()
{
   me=NULL;
   rival=NULL;
}

Room::Room(int roomId){
    this->id=roomId;
    me=NULL;
    rival=NULL;
}

bool Room::newPlayer(QString name,int color){

        rival=new Player(name,color);
        me->color=color^1;
        return true;
}
void Room::addPlayer(QString meName, int color){
    me=new Player(meName,color);
}

void Room::deleteRival(){
    delete rival;
    rival=NULL;

}
