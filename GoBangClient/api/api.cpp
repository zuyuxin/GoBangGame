#include "api.h"

#include"global.h"
API::API(QObject *parent) : QObject(parent){

     client=new Client();
     connect(client,&Client::newData,this,&API::handleRecvSignal);
//     connect(this, &API::loginSucess, [=]{

//     });
}

void API::sendLoginMsg(QString &name ,QString &pswd){
    QByteArray data;
    data.append(CmdLogin+CmdSplit+name+CmdSplit+pswd+CmdSplit);
    client->sendData(data);
}

void API::sendRegMsg(QString & name, QString & pswd){
    QByteArray data;
    data.append(CmdReg+CmdSplit+name+CmdSplit+pswd+CmdSplit);
    client->sendData(data);
}

void API::sendRoomEnter(QString  userName){
    QByteArray data;
    data.append(CmdRoomCreat+CmdSplit+userName+CmdSplit);
    client->sendData(data);
}

void API::sendReady(QString roomId,QString name){
    QByteArray data;
    qDebug()<<"-----roomId is:"<<roomId.toUtf8()<<"----";
    data.append(CmdReady+CmdSplit+roomId.toUtf8()+CmdSplit+name+CmdEnd);
    client->sendDataWithoutId(data);
}
void API::sendQuitRoom(QString roomId, QString name){
    QByteArray data;
    data.append(CmdGameQuit+CmdSplit+roomId+CmdSplit+name+CmdEnd);
    client->sendDataWithoutId(data);
}

void API::sendPiece(int roomId,int row,int col,int color){
    QByteArray data;
    util strutil;
    QString idstr=strutil.intToString(roomId);
    QString rowstr=strutil.intToString(row);
    QString colstr=strutil.intToString(col);
    QString colorstr=strutil.intToString(color);
    data.append(CmdPosDown+CmdSplit+idstr.toLocal8Bit()+CmdSplit+rowstr.toLocal8Bit()+CmdSplit+colstr.toLocal8Bit()+CmdSplit+colorstr.toLocal8Bit()+CmdEnd);
    client->sendDataWithoutId(data);
}
void API::bindPort(int port){
    client->bindMyPort(port);
}
bool API::connectToHost(){
    bool ret=client->connectToServer();
    return ret;
}
//根据newData发送给对应类
void API::handleRecvSignal(QByteArray cmd,QByteArray args){

    if(cmd==this->CmdLoginState){
        if(args.toInt()==1){
            emit loginSucess();
        }else{
            emit loginFailiure();
        }
    }else if(cmd==CmdRegState){
        if(args.toInt()==1)
            emit regSucess();
        else
            emit regFailiure();
    }else if(cmd==CmdRoomCreatRes){
        QList<QByteArray> msg=args.split(argSplit);
        int roomId=msg[0].toInt();
        int color=msg[1].toInt();
        emit roomEnterRes(roomId,color);
    }else if(cmd==CmdRoomJoin){//加入其他玩家创建的房间
        QList<QByteArray> msg=args.split(argSplit);
        int roomId=msg[0].toInt();
        QString rival=msg[1];
        int ready=msg[5].toInt();
        int rivalcolor=msg[2].toInt();
        //QString socketId=msg[4];

        emit roomJoin(roomId,rival,rivalcolor,ready);
    }else if(cmd==CmdNewPlayer){
        QList<QByteArray> msg=args.split(argSplit);
        QString rival=msg[0];
        QString color=msg[1];
        emit newPlayer(rival,color.toInt());
    }else if(cmd==CmdGameBegin){
        emit gameBegin();
    }else if(cmd==CmdReady){
        emit setRivalReady();
    }else if(cmd==CmdGameQuit){
        emit rivalQuitRoom();
    }else if(cmd==CmdPosDown){
        QList<QByteArray> msg=args.split(argSplit);
        int row=msg[0].toInt();
        int col=msg[1].toInt();
        int color=msg[2].toInt();
        int nowColor=msg[3].toInt();
        emit posDown(row,col,color,nowColor);
    }else if(cmd==CmdSYNPiece){
        QList<QByteArray> msg=args.split(argSplit);
        int row=msg[0].toInt();
        int col=msg[1].toInt();
        int nowColor=msg[2].toInt();
        emit synNowColor(row,col,nowColor);
    }else if(cmd==CmdGameOver){
        int winner=args.toInt();
        qDebug()<<"-----gameover: the winner is :"<<winner<<"-----";
        emit gameOver(winner);
    }
}
