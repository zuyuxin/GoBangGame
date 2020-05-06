#include "roomman.h"

#include"util.h"

RoomMan::RoomMan(QObject *parent) : QObject(parent)
{
     nowId=0;
}

//根据roomId怎么寻找

void RoomMan::enterRoom(QString &userName,QString &socketId){

    if(notFullRoom.size()==0){

            notFullRoom.append(new Room(nowId));

            int color=notFullRoom[0]->addPlayer(userName,socketId);

            API *api=API::getInstance();
            util strutil;
            QString id=strutil.intToString(nowId);
            QString arg;
            arg.append(color+'0');
            api->sendRoomCreateRes(id.toUtf8(),arg.toUtf8(),socketId);
            nowId++;

    }else{
        Room *room=new Room(notFullRoom[0]);//浅拷贝
        room->addPlayer(userName,socketId);

        if(room->getPlayersNum()==2){
            notFullRoom.removeFirst();
            fullRooms.insert(room->getRoomId(),room);
        }
        room->broadCastRoomMsg();

    }
}
void RoomMan::readyGame(int roomId,QString name){
    if(fullRooms.find(roomId)!=fullRooms.end()){
        fullRooms[roomId]->setReady(name);
    }else {
        for(Room* room:notFullRoom){
            if(room->getRoomId()==roomId){
                room->setReady(name);
                return;
            }
        }
        qDebug()<<"-----cannot the roomId"<<roomId<<"-----";
    }
}
bool RoomMan::deleteNotFullRoomById(int id){
    for(Room*room: notFullRoom){
        if(room->getRoomId()==id){//找到对应的房间号并将其删除
            notFullRoom.removeOne(room);
            delete room;
            qDebug()<<"-----The room"<<room->getRoomId()<<"was deleted -----";
            return true;
        }
    }
    return NULL;
}

void RoomMan::quitRoom(int roomId,QString name){
    //在notfullroom fullrooms中查找roomId
    if(fullRooms.find(roomId)!=fullRooms.end()){
        fullRooms[roomId]->deletePlayer(name);

        if(fullRooms[roomId]->getPlayersNum()==0){
            Room *room=fullRooms[roomId];
            fullRooms.remove(roomId);
            delete room;
        }else {
            notFullRoom.append(fullRooms[roomId]);
            fullRooms.remove(roomId);
        }
    }else if(!deleteNotFullRoomById(roomId)){
        qDebug()<<"-----cannot find the roomId :"<<roomId<<"-----";
    }
}

void RoomMan::posDown(QByteArray &roomId,QByteArray &row,QByteArray &col,QByteArray &color){
    int id=roomId.toInt();
    if(fullRooms.find(id)!=fullRooms.end()){
        fullRooms[id]->pressDown(row,col,color);
    }else {
         qDebug()<<"-----fail to press down the piece because it cannot find the roomId"<<roomId<<"-----";
    }
}
bool RoomMan::searchRoomById(int id){
    if(id>=nowId)
        return false;
    else
        return true;
}

bool RoomMan::joinRoom(QString & name,int id,QString &socketId){
    if(id>=nowId){
        return false;
    }else{
        for(Room*room:notFullRoom){
            if(room->getRoomId()==id){
                room->addPlayer(name,socketId);
                return true;
            }
        }
    }
    return false;
}

//bool RoomMan::quitRoom(int id, QString & name){
//    if(id>=rooms.size()){
//        qDebug()<<"------the room"<< id<<"do not exsit-----";
//    }else{
//        rooms[id]->deletePlayer(name);
//        if(rooms[id]->getPlayersNum()==0)
//            rooms.remove(id);
//    }
//}

//bool RoomMan::pressDown(int roomId, QString & userName, int row, int col){


//    return true;

//}
