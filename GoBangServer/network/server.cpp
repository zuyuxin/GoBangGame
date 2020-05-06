#include "server.h"
#include"util.h"
Server::Server(QObject *parent) : QObject(parent)
{
    //在一个客户端socket发送消息后，怎么判断是哪一个serversocket去处理呢？
    //init(8888);
    tcpServer=new QTcpServer();
    currentSocket=new QTcpSocket(this);

}

void Server::init(quint16 port){

    tcpServer->listen(QHostAddress::Any,port);
    connect(tcpServer,&QTcpServer::newConnection,this,&Server::handleNewConnection);
    qDebug()<<"------is binding the "<<port<<"port------";
}

void Server::handleNewConnection(){
   currentSocket= tcpServer->nextPendingConnection();
   util strutil;
   QString socketId=currentSocket->peerAddress().toString()+strutil.intToString(currentSocket->peerPort());
   sockets.insert(socketId,currentSocket);
   qDebug()<<"-----it is connecting socketId:"<<socketId<<"-----";
   connect(currentSocket,&QTcpSocket::readyRead,this,&Server::readData);
   connect(currentSocket,&QTcpSocket::disconnected,this,&Server::disconnect);
}

void Server::readData(){
    for(QTcpSocket* socket :sockets){
        QByteArray buffer=socket->readAll();
        if(buffer.isEmpty())
           continue;
        else{
            QTextCodec *tc = QTextCodec::codecForName("UTF-8");
            QString tmpQStr = tc->toUnicode(buffer);
            qDebug()<<"-----recive new Data: "<<tmpQStr<<"------";

            int endIndex;
            while((endIndex = buffer.indexOf(CmdEnd))>-1){
                //提取一行指令
                QByteArray data = buffer.mid(0,endIndex);
                buffer.remove(0,endIndex+CmdEnd.length());
                //提取指令和参数
                QByteArray cmd,args;
                int argIndex = data.indexOf(CmdSplit);
                if(argIndex==-1){
                    cmd = data;
                }else{
                    cmd = data.mid(0,argIndex);
                    args = data.mid(argIndex+CmdSplit.length(),data.length());
                }
                emit newData(cmd,args);
            }

        }
    }
}

void Server::sendData(QByteArray &data,QString &socketId){

    bool ret;
    if(sockets.find(socketId)!=sockets.end()){
        ret=sockets[socketId]->write(data,sockets[socketId]->peerPort());
        if(ret){
            qDebug()<<"-----"<<data<<" is sent sucessfully------";
        }else{
            qDebug()<<"------it is fail to send the data that"<<data<<"-----";
        }
    }else{
        qDebug()<<"-----not find the socketId"<<socketId;
    }

}

void Server::disconnect(){
    for(auto socket:sockets){
        if(socket->state()==QAbstractSocket::UnconnectedState||socket->waitForDisconnected(30000)){
            qDebug()<<"-----disconect the client" << socket->peerAddress().toString()<<" sucussfully-----";
            socket->destroyed();

            sockets.remove(socket->peerName());
        }
    }
}

void Server::readError(){
    QMessageBox msgBox;
    msgBox.setText(tr("failed to connect server because ..."));
}

Server::~Server(){

    for(auto client:sockets){
        //
        client->disconnectFromHost();
                bool ok = client->waitForDisconnected(1000);
                if(!ok)
                {
                    // 处理异常
                    qDebug()<<"------close error-----";
                }

        sockets.remove(client->peerName());
    }
    tcpServer->close();
    delete tcpServer;
    delete currentSocket;
}
