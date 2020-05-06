#include "api.h"
#include"util.h"
API::API(QObject *parent) : QObject(parent)
{
    server = new Server();
    connect(server,&Server::newData,this,&API::loginHandle);
    connect(server,&Server::newData,this,&API::RegsiterHandle);
    connect(server,&Server::newData,this,&API::EnterRoomHandle);
    connect(server,&Server::newData,this,&API::ReadyHandle);
    connect(server,&Server::newData,this,&API::quitRoomHandle);
    connect(server,&Server::newData,this,&API::PieceHandle);

    userMan=new UserMan();
    //roomMan=new RoomMan();
}
Server* API::getServer() {
    if(server== NULL) {
        server = new Server();
    }
    return server;
}

void API::loginHandle(QByteArray cmd,QByteArray args){
    if(cmd!=CmdLogin)
        return;
    else{
        QList<QByteArray> msg=args.split(argSplit);
        QString name=msg[0];
        QString pswd=msg[1];
        QString socketId=msg[2];
        QByteArray arg;
        arg.append(CmdLoginState+CmdSplit);
        bool ret= userMan->loginJudge(name,pswd);
        if(ret){
            arg.append("1"+CmdEnd);
            server->sendData(arg,socketId);
        }else{
            arg.append("0"+CmdEnd);
            server->sendData(arg,socketId);
        }
    }
}

void API::RegsiterHandle(QByteArray cmd,QByteArray args){
    if(cmd!=CmdReg)
        return;
    else{
        QList<QByteArray> msg=args.split(argSplit);
        QString name=msg[0];

        QString pswd=msg[1];

        QString socketId=msg[2];

        QByteArray arg;
        arg.append(CmdRegState+CmdSplit);
        bool ret= userMan->searchUserByName(name);
        if(ret){
            arg.append("0"+CmdEnd);
            server->sendData(arg,socketId);
        }else{
            arg.append("1"+CmdEnd);
            userMan->registerUser(name,pswd);
            server->sendData(arg,socketId);
        }
    }
}

void API::EnterRoomHandle(QByteArray cmd,QByteArray args){
    if(cmd!=CmdRoomCreat)
        return;
    else{
        QList<QByteArray> msg=args.split(argSplit);
        QString name=msg[0];
        QString socketId=msg[1];
        emit enterRoom(name,socketId);
    }
}
void API::ReadyHandle(QByteArray cmd,QByteArray args){
    if(cmd!=CmdReady)
        return;
    else{
        QList<QByteArray> msg=args.split(argSplit);
        int roomId=msg[0].toInt();
        QString name=msg[1];
        emit readyGame(roomId,name);
    }
}

void API::PieceHandle(QByteArray cmd,QByteArray args){
    if(cmd!=CmdPosDown)
        return;
    else{
        QList<QByteArray> msg=args.split(argSplit);
        QByteArray roomId=msg[0];
        QByteArray row=msg[1];
        QByteArray col=msg[2];
        QByteArray color=msg[3];
        emit posDown(roomId,row,col,color);
    }
}

void API::quitRoomHandle(QByteArray cmd,QByteArray args){
    if(cmd!=CmdGameQuit){
        return;
    }else{
        QList<QByteArray> msg=args.split(argSplit);
        int roomId=msg[0].toInt();
        QString name=msg[1];
        emit quitGame(roomId,name);
    }
}
void API::initServer(quint16 port){
    server->init(port);
}

void API::sendRoomCreateRes(QByteArray roomid, QByteArray arg,QString &socketId){
    QByteArray args;
    args.append(CmdRoomCreatRes+CmdSplit+roomid+CmdSplit+arg+CmdEnd);
    server->sendData(args,socketId);
}

void API::sendRoomNewPlayer(QByteArray msg,QString & socketId){
    QByteArray args;
    args.append(CmdNewPlayer+CmdSplit+msg+CmdEnd);
    server->sendData(args,socketId);
}
void API::sendEnterRoomMsg(QByteArray roomId,QByteArray firstmsg,QByteArray secondmsg,QString &secondSocketId){
    QByteArray args;
    args.append(CmdRoomJoin+CmdSplit+roomId+CmdSplit+firstmsg+CmdSplit+secondmsg+CmdEnd);
    server->sendData(args,secondSocketId);
}
void API::sendStartGame(QString &socketId2){
    QByteArray args;
    args.append(CmdGameBegin+CmdEnd);
    server->sendData(args,socketId2);
}

void API::sendReady(QString &socketId){

    QByteArray args;
    args.append(CmdReady+CmdEnd);
    server->sendData(args,socketId);
}

void API::sendQuitRoom(QString &socketId){
    QByteArray args;
    args.append(CmdGameQuit+CmdEnd);
    server->sendData(args,socketId);
}

void API::sendPiece(QByteArray &row,QByteArray &col,QByteArray &color,QString &socketId,int nowPlayer){
    QByteArray args;
    util strutil;
    args.append(CmdPosDown+CmdSplit+row+CmdSplit+col+CmdSplit+color+CmdSplit+strutil.intToString(nowPlayer).toUtf8()+CmdEnd);
    server->sendData(args,socketId);
}

void API::sendUndoPiece(QByteArray &row,QByteArray & col,int nowColor,QString &socketId){
    QByteArray args;
    util strutil;
    args.append(CmdSYNPiece+CmdSplit+row+CmdSplit+col+CmdSplit+strutil.intToString(nowColor)+CmdEnd);
    server->sendData(args,socketId);
}

void API::sendGameOver(QByteArray &winner,QString &socketId1,QString &socketId2){
    QByteArray args;
    args.append(CmdGameOver+CmdSplit+winner+CmdEnd);
    server->sendData(args,socketId1);
    server->sendData(args,socketId2);
}
