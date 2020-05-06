#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QList>
#include<QTextCodec>
#include<QHash>
#include<QMessageBox>
class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    void init(quint16);
    ~Server();
signals:
    void newData(QByteArray cmd,QByteArray args);
public slots:
    void handleNewConnection();
    void disconnect();
    void sendData(QByteArray & ,QString & );
    void readData();
    void readError();

private:
    //特殊指令
    const QByteArray CmdEnd = "\r\n";  //结束符
    const QByteArray CmdSplit = ";";  //间隔符
    QTcpServer *tcpServer;
    QTcpSocket *currentSocket;
    QHash<QString,QTcpSocket*> sockets;
};

#endif // SERVER_H
