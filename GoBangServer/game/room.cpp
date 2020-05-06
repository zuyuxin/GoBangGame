#include "room.h"
#include<QDebug>
#include"util.h"
#include"gamethread.h"
Room::Room()
{
    this->game=NULL;
    this->readys=0;
    this->playersNum=0;
    first=NULL;
    second=NULL;
}
Room::Room(int id){

    this->roomId=id;
    this->game=NULL;
    this->readys=0;
    this->playersNum=0;
    first=NULL;
    second=NULL;
}
Room::Room(Room * room){
    roomId=room->roomId;
    playersNum=room->playersNum;
    first=room->first;
    second=room->second;
    game=room->game;
    readys=room->readys;
   // this->ready=room->ready;
}

int Room::addPlayer(QString & name,QString &socketId){
    if(playersNum>=2){
        return -1;
    }else if(playersNum==1){
        second=new Player(name);
        second->color=first->color^1;
        second->socketId=socketId;
        this->playersNum++;
        return second->color;
    }else{
        first=new Player(name);
        first->color=qrand()%2;
        first->socketId=socketId;
        this->playersNum++;
        return first->color;
    }
    return true;
}
bool Room::deletePlayer(QString & name){
    if(first&&first->userName==name){
        delete first;
        first=NULL;
        this->playersNum--;
        this->readys--;
        if(second){
            API *api= API::getInstance();
            api->sendQuitRoom(second->socketId);
        }// 空房间 半空房间
        qDebug()<<"-----the user"<< name<<"quit the room "<< roomId<<"------";
        return true;
    }else if(second&&second->userName==name){
        delete  second;
        second=NULL;
        this->playersNum--;
        this->readys--;
        if(first){
        API *api= API::getInstance();
        api->sendQuitRoom(first->socketId);
        }
        return true;
    }
    return false;
}
void Room::setRoomId(int id){
    this->roomId=id;
}
int Room::getRoomId(){
    return roomId;
}
int Room::getPlayersNum(){
    return playersNum;
}

void Room::broadCastRoomMsg(){
    API *api=API::getInstance();
    QByteArray firstMsg;
    util strUtil;
    QString ready=strUtil.intToString(first->ready);
    firstMsg.append(first->userName+CmdSplit+strUtil.intToString(first->color).toLocal8Bit()+CmdSplit+first->socketId+CmdSplit+ready.toUtf8());

    QByteArray secondMsg;
    secondMsg.append(second->userName+CmdSplit+strUtil.intToString(second->color).toLocal8Bit()+CmdSplit+second->socketId);
    //向玩家2发送创建房间的消息，并且渲染除所有信息
    api->sendEnterRoomMsg(strUtil.intToString(roomId).toLocal8Bit(),firstMsg,secondMsg,second->socketId);

    //向玩家1发送有新玩家加入房间的消息，并且渲染这个玩家的相关信息
    api->sendRoomNewPlayer(secondMsg,first->socketId);

}

void Room::reInit(){
    readys=0;
    first->ready=-1;
    second->ready=-1;
}

int Room::setReady(QString &name){
    API *api=API::getInstance();
    if(first&&first->userName==name){
        if(first->ready==1)
            return readys;
        first->ready=1;
        if(second)
            api->sendReady(second->socketId);
        ++readys;
    }else if(second&&second->userName==name){
        if(second->ready==1)
            return readys;
        second->ready=1;

        if(first)
            api->sendReady(first->socketId);
        ++readys;
    }

    if(readys>=2){
       api->sendStartGame(first->socketId);
       api->sendStartGame(second->socketId);
        if(!game)
            game=new Game();
       game->start();
    }

    return readys;
}

bool Room::hasPlayer(QString & name){
    if(first&&first->userName==name||second&&second->userName==name)
        return true;
    else
        return false;
}

void Room::pressDown(QByteArray &rowstr,QByteArray &colstr,QByteArray &colorstr){
   int row=rowstr.toInt();
   int col=colstr.toInt();
   int color=colorstr.toInt();
   API *api=API::getInstance();

   int ret=game->pressDown(row,col,color);
   if(ret!=-1){
       QString socketId=judgeRival(color);
       api->sendPiece(rowstr,colstr,colorstr,socketId,game->nowPlayer);

       int winner=winner=game->isWin(row,col);

       if(winner!=-1){//决出胜负
           reInit();
           game->setGameOver();
           QByteArray winnerStr;
           if(ret==0)
               winnerStr="0";
           else
               winnerStr="1";
           api->sendGameOver(winnerStr,first->socketId,second->socketId);
       }

    }else{
        //当前下棋方不是color 发送消息给color
       QString playersocketId=judgePlayer(color);
       api->sendUndoPiece(rowstr,colstr,game->nowPlayer,playersocketId);
    }
}

QString Room::judgeRival(int color){
    if(color==first->color)
        return second->socketId;
    else if(color==second->color)
        return first->socketId;
    else
        return "";
}

QString Room::judgePlayer(int color){
    if(first->color==color)
        return first->socketId;
    else if(second->color==color)
        return second->socketId;
    else
        return "";
}

