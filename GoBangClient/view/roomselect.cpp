#include "view/roomselect.h"
#include "ui_roomselect.h"
#include"global.h"
RoomSelect::RoomSelect(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RoomSelect)
{
    ui->setupUi(this);
    user=NULL;
    api=API::getInstance();
    pvpWindow=NULL;
    connect(api,&API::roomEnterRes,this,&RoomSelect::enterRoomRes);
    connect(api,&API::roomJoin,this,&RoomSelect::joinRoom);
    connect(api,&API::newPlayer,this,&RoomSelect::newPlayer);
    notifyDig=NULL;
}

RoomSelect::~RoomSelect()
{
    if(pvpWindow){

        sendQuitRoom(pvpWindow->getRoomId());
        delete pvpWindow;
    }

    if(notifyDig)
        delete notifyDig;
    delete ui;

}

void RoomSelect::on_createRoomBt_clicked()
{
    //发送信息给服务器 申请房间号
    //收到消息后 显示分配好的房间号在pvpwindow中
    //房间分配失败 返回错误信息
    user=User::getInstance();
    api->sendRoomEnter(user-> geUserName());

}

void RoomSelect::on_joinRoomBt_clicked()
{
    if(ui->joinRoomIdInput->text()!=NULL){
        //发送消息给服务器 连接房间
        //收到消息后 显示pvpwindow 并且在pvpwindow中显示分配的房间号
        //若收到消息房间已满分配失败 显示NotifyDig 设置错误信息为加入房间已满
        //   PVPWindow *pvpWindow = new PVPWindow(this);
        //    this->close();
         //   pvpWindow->roomInit(ui->joinRoomIdInput->text().toInt(),user->geUserName());
         //   pvpWindow->show();
         //   connect(pvpWindow,&PVPWindow::backhome,this,&RoomSelect::show);

    }else{
        if(!notifyDig)
        notifyDig=new NotifyDig();
        QString retmsg="输入房间为空";
        notifyDig->showMsg(retmsg);

    }
}
void RoomSelect::sendQuitRoom(int roomId){
    API *api=API::getInstance();
    util strutil;
    api->sendQuitRoom(strutil.intToString(roomId),user->geUserName());
}

void RoomSelect::showAndHandleQuitRoom(int roomId){

    if(pvpWindow){
        delete pvpWindow;
        pvpWindow=NULL;
    }
    sendQuitRoom(roomId);
    this->show();
}

void RoomSelect::on_backhomeBt_clicked()
{
    this->close();
    emit backhome();
}

void RoomSelect::enterRoomRes(int roomId,int color){

        this->close();
        if(!pvpWindow){
             pvpWindow=new PVPWindow();
             connect(pvpWindow,&PVPWindow::backhomeAndQuitRoom,this,&RoomSelect::showAndHandleQuitRoom);

        }
        pvpWindow->roomInit(roomId,user->geUserName(),color);
        pvpWindow->show();

}

void RoomSelect::joinRoom(int roomId,QString rivalName,int rivalColor,int ready){
    this->close();
    if(!pvpWindow){
         pvpWindow=new PVPWindow();
         connect(pvpWindow,&PVPWindow::backhomeAndQuitRoom,this,&RoomSelect::showAndHandleQuitRoom);
    }
    pvpWindow->roomInitTwoPlayer(roomId,rivalName,rivalColor,ready);
    pvpWindow->show();
}

void RoomSelect::newPlayer(QString &rival,int color){
    if(pvpWindow){
        pvpWindow->addRival(rival,color);
    }
}
