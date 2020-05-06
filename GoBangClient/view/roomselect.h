#ifndef ROOMSELECT_H
#define ROOMSELECT_H

#include <QWidget>
#include"notifydig.h"
#include"pvpwindow.h"
#include"user.h"
#include"api/api.h"
namespace Ui {
class RoomSelect;
}

class RoomSelect : public QWidget
{
    Q_OBJECT

public:
    explicit RoomSelect(QWidget *parent = nullptr);
    ~RoomSelect();

signals:
    void backhome();
private slots:
    void on_createRoomBt_clicked();

    void on_joinRoomBt_clicked();

    void showAndHandleQuitRoom(int);
    void on_backhomeBt_clicked();
    void sendQuitRoom(int);
public slots:
    void enterRoomRes(int roomId,int color);
    void joinRoom(int,QString,int,int);
    void newPlayer(QString &rival,int color);
private:
    Ui::RoomSelect *ui;
    User *user;
    API * api;
    NotifyDig* notifyDig;
    PVPWindow *pvpWindow;
};

#endif // ROOMSELECT_H
