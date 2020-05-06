#include "view/pvpwindow.h"
#include "ui_pvpwindow.h"
#include"api/api.h"
#include"user.h"
#include"global.h"
#include"notifydig.h"
PVPWindow::PVPWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::PVPWindow)
{
    ui->setupUi(this);
    chess = new PVPChess(ui->widget_chess);
    room=new Room();
    API *api=API::getInstance();
    connect(chess,&PVPChess::piece_emit,this,&PVPWindow::piece_send);
    connect(api,&API::posDown,chess,&PVPChess::posDown);
    connect(api,&API::synNowColor,chess,&PVPChess::synNowColor);

    connect(api,&API::rivalQuitRoom,this,&PVPWindow::rivalQuit);
    connect(api,&API::gameBegin,this,&PVPWindow::gameBegin);
    connect(api,&API::setRivalReady,this,&PVPWindow::setRivalReady);
    connect(api,&API::gameOver,this,&PVPWindow::gameOver);

    connect(chess,SIGNAL(start_emit(int , int ,int)),this,SLOT(read_emit(int,int,int)));

}

PVPWindow::~PVPWindow()
{


    delete this->chess;
    delete this->room;
    delete ui;
}

//void PVPWindow::roomInit(int roomId, QString user1, QString user2){
//    if(!room){
//        room=new Room(roomId);
//        room->addPlayer(user1);
//        room->addPlayer(user2);
//    }
//}
void PVPWindow::roomInit(int roomId, QString user,int color){
    if(!room){
        room=new Room(roomId);
    }else{
        chess->countPlayer1Use=color;
        room->addPlayer(user,color);


        ui->meReadyLabel->setText("未准备");
    }
}
void PVPWindow::roomInitTwoPlayer(int roomId, QString rivalName,int color,int ready){
    if(!room){
        room=new Room(roomId);
     }else{
        User *user=User::getInstance();
        chess->countPlayer1Use=color^1;
        room->addPlayer(user->geUserName(),color^1);
        room->newPlayer(rivalName,color);
        ui->rivalNameLable->setText(rivalName);
        if(ready!=1)
            ui->rivalReadyLable->setText("未准备");
        else
            ui->rivalReadyLable->setText("已准备");
        ui->meReadyLabel->setText("未准备");

    }
}
//void PVPWindow::enterRoom(QString name,QString user){

//}
void PVPWindow::addRival(QString & name, int &color){
    if(!room){
        qDebug()<<"-----error------";
        return;
    }else{
        room->newPlayer(name,color);
        ui->rivalNameLable->setText(name);
        ui->rivalReadyLable->setText("未准备");
    }

}

int PVPWindow::getRoomId(){
    return this->room->getRoomId();
}
void PVPWindow::on_btn_back_clicked()
{
    chess->gameState = false;
    chess->countPlayer1Use = 1;
    this->close();
    emit backhomeAndQuitRoom(room->getRoomId());

}

void PVPWindow::on_btn_start_clicked()
{

    chess->clearChessBoard();
    chess->setWhoWin(-1);
    this->ui->label_step->setText(QString("STEP： ")+QString::number(this->chess->getStep(),10)+QString(" 步"));

    this->ui->btn_start->setText("已准备");
    ui->meReadyLabel->setText("已准备");
    this->ui->btn_start->setDisabled(false);

    API *api=API::getInstance();
    User * user=User::getInstance();
    util strutil;
    QString roomId=strutil.intToString(room->getRoomId());
    api->sendReady(roomId,user->geUserName());

}

void PVPWindow::on_btn_undo_clicked()
{
    chess->gameState = true;
    chess->deleteChessBoardXY();
    //发送给对方悔棋 但是需要对方同意
  //  API *api;

    update();
}

void PVPWindow::read_emit(int num,int score1 , int score2){
    QString str = QString("STEP： ")+QString::number(num,10)+QString(" 步");
    ui->label_step->setText(str);
}

void PVPWindow::piece_send(int row,int col,int color){
   API *api=API::getInstance();
   api->sendPiece(room->getRoomId(),row,col,color);
}



void PVPWindow::gameBegin(){

    chess->gameState=true;
    chess->countWhoFirst=1;//默认白棋先下
    ui->rivalReadyLable->setText("已准备");
    ui->btn_start->setEnabled(false);

}
void PVPWindow::gameOver(int winner){

    NotifyDig *notifyDig=new NotifyDig();
    QString data;
    if(winner==room->me->color)
        data="恭喜你，你赢了！";
    else
        data="很遗憾，你输了";
    notifyDig->showMsg(data);

    chess->gameState=false;
    chess->countWhoFirst=1;
    ui->btn_start->setEnabled(true);
    ui->btn_start->setText("重新开始");
    ui->rivalReadyLable->setText("未准备");
    ui->meReadyLabel->setText("未准备");
}
void PVPWindow::setRivalReady(){
    qDebug()<<" rival is ready";
    ui->rivalReadyLable->setText("已准备");
}
void PVPWindow::rivalQuit(){
    room->deleteRival();
    ui->rivalNameLable->setText("等待其他玩家进入房间");
    ui->rivalReadyLable->setText("");
    this->update();
}


void PVPWindow::on_btn_giveup_clicked()
{

}

void PVPWindow::paintEvent(QPaintEvent *)//绘制事件
{


    QPainter *paint=new QPainter;
    paint->begin(this);//开始绘制
    paint->setRenderHint(QPainter::Antialiasing, true);//抗锯齿
    paint->setPen(Qt::NoPen);
    QBrush  *brush = new QBrush();
    brush->setStyle(Qt::SolidPattern);

    if(room->me&&room->me->color==0){
        brush->setColor(Qt::black);
        paint->setBrush(*brush);
        paint->drawEllipse(625,180,28,28);
    }else if(room&&room->me->color==1){
        brush->setColor(Qt::white);
        paint->setBrush(*brush);
        paint->drawEllipse(625,180,28,28);
    }
    if(room->rival&&room->rival->color==1){
        brush->setColor(Qt::white);
        paint->setBrush(*brush);
        paint->drawEllipse(725,180,28,28);
    }else if(room->rival&&room->rival->color==0){
        brush->setColor(Qt::black);
        paint->setBrush(*brush);
        paint->drawEllipse(725,180,28,28);
    }
    paint->end();
}
