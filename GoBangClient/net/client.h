#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include<QTcpSocket>
#include<QNetworkInterface>
#include<QTextCodec>
#include<QHostAddress>
#include<QDebug>
#include<QMessageBox>

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = nullptr);
    ~Client();
    QString getClientIpAdress();
    void init();
    bool bindMyPort(int);
    bool connectToServer();
    void disconnect();
    //游戏内容
    const QByteArray CmdEnd = "\r\n";  //结束符
    const QByteArray CmdSplit = ";";  //间隔符
    void sendDataWithoutId(QByteArray &);
signals:
    void newData(QByteArray cmd,QByteArray args);

public slots:
    void readData();
    void ReadError(QAbstractSocket::SocketError);
    void sendData(QByteArray &data);



 //   bool sendCreateRoom(QString &name); //创建房间
//    bool jionRoom(QString &roomId);  //加入房间
//    bool sendPosition(const int chess_x, const int chess_y);
//    //求和指令
//    bool sendPeaceCmd();
//    bool sendPeaceReturnCmd(bool);
//    //悔棋指令
//    bool sendRegretCmd();
//    bool sendRegretreturnCmd(QByteArray flag);
//    //认输指令
//    bool sendGiveUpCmd();
//    //发送消息
//    bool sendMessage(QByteArray* m_msg);
//    //发送决出胜负指令
//    bool sendGameOverCmd();



private:


    QTcpSocket * socket;
    QString myaddr;
    QString serveraddr;
    quint16 myport=8890,serverport=8888;

};

#endif // CLIENT_H
