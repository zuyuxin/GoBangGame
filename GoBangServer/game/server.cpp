#include "server.h"

Server::Server(QObject *parent) : QObject(parent)
{
    tcpServer=new QTcpServer();
    tcpServer->listen(QHostAddress::Any,8888);
    currentSocket=new QTcpSocket(this);

    connect(tcpServer,&QTcpServer::newConnection,this,&Server::handleNewConnection);
    //在一个客户端socket发送消息后，怎么判断是哪一个serversocket去处理呢？
}

void Server::handleNewConnection(){
   currentSocket=new QTcpSocket(this);
   sockets.append(currentSocket);
   qDebug()<<"-----it is connecting ip:"<<currentSocket->peerAddress().toString()<<","<<"port:"<<currentSocket->peerPort()<<"-----";
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
