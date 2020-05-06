#ifndef ROOMMAN_H
#define ROOMMAN_H
#include<QObject>
#include"game/room.h"
#include<QVector>
#include<QQueue>
#include<QDebug>
#include"network/api.h"
#include <QtGlobal>

class RoomMan: public QObject
{
    Q_OBJECT

public:

    explicit RoomMan(QObject *parent = nullptr);
    bool searchRoomById(int );
    bool joinRoom(QString &,int,QString & );
    Room *getOneNotFullRoom(QString &);
private:

    QHash<int,Room*> fullRooms;
    QList<Room*> notFullRoom;
    int nowId;
    bool deleteNotFullRoomById(int);
public slots:
     void enterRoom(QString &,QString &);
     void readyGame(int,QString);
     void quitRoom(int,QString);
     void posDown(QByteArray &,QByteArray &,QByteArray &,QByteArray &);
};

#endif // ROOMMAN_H
