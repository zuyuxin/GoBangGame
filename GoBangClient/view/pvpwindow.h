#ifndef PVPWINDOW_H
#define PVPWINDOW_H

#include <QMainWindow>
#include "view/dialogchoosepiece.h"
#include"user.h"
#include"game/room.h"
#include<QDebug>
#include"pvpchess.h"

namespace Ui {
class PVPWindow;
}

class PVPWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit PVPWindow(QWidget *parent = 0);


    ~PVPWindow();

   // void roomInit(int ,QString ,QString );
    void roomInit(int ,QString,int);
    void roomInitTwoPlayer(int roomId, QString rivalName,int color,int ready);
    void enterRoom(QString);
    void addRival(QString &,int &);

    int getRoomId();



signals:
    void backhomeAndQuitRoom(int);//这个函数用户向主界面通知关闭的消息
public slots:
    void gameBegin();
    void setRivalReady();
    void rivalQuit();
    void gameOver(int);
private slots:

    void read_emit(int,int,int);

    void piece_send(int,int,int);


    void on_btn_back_clicked();

    void on_btn_start_clicked();

    void on_btn_undo_clicked();

    void on_btn_giveup_clicked();


private:
    Ui::PVPWindow *ui;
    Room * room;
    PVPChess *chess;

    void paintEvent(QPaintEvent *);
};

#endif // PVPWINDOW_H
