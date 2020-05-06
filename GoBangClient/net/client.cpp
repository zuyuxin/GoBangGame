#include "client.h"
#include <QUdpSocket>
Client::Client(QObject *parent) : QObject(parent)
{

    myaddr=getClientIpAdress();
    serveraddr=getClientIpAdress();
    socket=new QTcpSocket(this);
    socket->abort();
  //  socket->bind(myport);
    connect(socket,&QTcpSocket::readyRead,this,&Client::readData);

    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(ReadError(QAbstractSocket::SocketError)));
  //  init();

}

QString Client::getClientIpAdress(){


        QList<QHostAddress> list =QNetworkInterface::allAddresses();
        for (QHostAddress address: list)
        {
           if(address.protocol() ==QAbstractSocket::IPv4Protocol)
               //我们使用IPv4地址
               return address.toString();
        }
        return 0;

}

Client::~Client(){
    delete socket;
}

void Client::init(){
    if(socket==NULL){
        socket=new QTcpSocket(this);
        socket->abort();
        socket->bind(myport);
        connect(socket,&QTcpSocket::readyRead,this,&Client::readData);

        connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),
                this, SLOT(ReadError(QAbstractSocket::SocketError)));

    }
}
bool Client::bindMyPort(int port){
    myport=port;
    socket->bind(myport);
    return true;
}
bool Client::connectToServer(){
    socket->connectToHost(serveraddr, serverport);
    if (socket->waitForConnected(1000))  // 连接成功则进入if{}
    {
        qDebug()<<"-----connect successfully-----";
        return  true;
    }else
        return false;
}
void Client::readData(){
   QByteArray buffer= socket->readAll();
   //读取出数据包
   if(buffer.isEmpty())
       return;
   QTextCodec *tc = QTextCodec::codecForName("UTF-8");
   QString tmpQStr = tc->toUnicode(buffer);
   qDebug()<<"------recive new Data: "<<tmpQStr<<"-----";

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
void Client::ReadError(QAbstractSocket::SocketError)
{
    socket->disconnectFromHost();
    qDebug()<<"-----some errors happened,disconnect from host-----";
    QMessageBox msgBox;
    msgBox.setText(tr("failed to connect server because %1").arg(socket->errorString()));
}


QString toString(int num){
    QString res="";
    while(num){
        res.append(num%10+'0');
        num=num/10;
    }
    QString ret;
    int j=0;
    for(int i=res.size()-1;i>=0;i--)
        ret[j++]=res[i];

    return ret;
}
void Client::sendDataWithoutId(QByteArray &data){
    socket->write(data,data.length());
    qDebug()<<"------msg :"<<data<<" is sent sucssufully-----";
}
void Client::sendData(QByteArray &data){
    QString port=toString(myport);
    qDebug()<<port;

    data.append("::ffff:"+myaddr.toLocal8Bit()+port.toLocal8Bit()+CmdEnd);
    socket->write(data.data(),data.length());
    qDebug()<<"------msg :"<<data<<" is sent sucssufully-----";
}

void Client::disconnect(){
  //  a）断开TCP连接的函数：void disconnectFromHost()是从QAbstractSocket继承的public function，同时它又是一个virtual function。作用为：Attempts to close the socket. If there is pending data waiting to be written, QAbstractSocket will enter ClosingState and wait until all data has been written. Eventually, it will enter UnconnectedState and emit the disconnected() signal.
  //  b）等待TCP断开连接函数：bool waitForDisconnected(int msecs = 30000)，同样是从QAbstractSocket继承下来的public function，同时它又是一个virtual function。作用为：Waits until the socket has disconnected, up to msecs milliseconds. If the connection has been disconnected, this function returns true; otherwise it returns false. In the case where it returns false, you can call error() to determine the cause of the error.

    socket->disconnectFromHost();
    if(socket->state()==QAbstractSocket::UnconnectedState||socket->waitForConnected(30000)){
        qDebug()<<"-----disconect from host sucussfully-----";
    }
}

