#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QList>
#include<QTextCodec>
class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);

signals:
    void newData(QByteArray cmd,QByteArray args);
public slots:
    void handleNewConnection();
    void disconnect();
    void sendData();
    void readData();
    void readError();

private:
    QTcpServer *tcpServer;
    QTcpSocket *currentSocket;
    QList<QTcpSocket*> sockets;
};

#endif // SERVER_H
