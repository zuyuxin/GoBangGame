#include "gobang.h"

GoBang::GoBang(QObject *parent) : QObject(parent)
{
    roomMan=new RoomMan();
    api=API::getInstance();
    connect(api,&API::enterRoom,roomMan,&RoomMan::enterRoom);
    connect(api,&API::readyGame,roomMan,&RoomMan::readyGame);
    connect(api,&API::posDown,roomMan,&RoomMan::posDown);
    connect(api,&API::quitGame,roomMan,&RoomMan::quitRoom);
    //connect(api,&API::sendJoinRoomMsg,roomMan,&RoomMan::joinRoom);
}

void GoBang::start(){
    api->initServer(8888);
}
