#ifndef GOBANG_H
#define GOBANG_H

#include <QObject>
#include"game/roomman.h"
#include"game/userman.h"
#include"network/api.h"
class GoBang : public QObject
{
    Q_OBJECT
public:
    explicit GoBang(QObject *parent = nullptr);
    void start();

private:
    RoomMan *roomMan;
    API *api;

};

#endif // GOBANG_H
