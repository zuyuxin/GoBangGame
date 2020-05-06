#include "pvpchess.h"
#include "ui_pvpchess.h"
#include<QDebug>
#include<QPainter>
#include<QBrush>
PVPChess::PVPChess(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PVPChess)
{
    ui->setupUi(this);
    clearChessBoard();
    setMouseTracking(true);
    step = 0;//步数初始化为0
    whoWin = 0;//赢家判断标志初始化为0
}

PVPChess::~PVPChess()
{
    delete ui;
}
void PVPChess::posDown(int row,int col,int color,int nowPlayer){
    chessBoard[row][col]=color;
    countWhoFirst=countPlayer1Use;
    update();
}

void PVPChess::synNowColor(int row,int col,int nowColor){
    chessBoard[row][col]=-1;
    countWhoFirst=nowColor;
    update();
}

bool PVPChess:: deleteChessBoardXY(){
    if(chessBoardX.empty()  || chessBoardY.empty()){
        return false;
    }
    else{
        chessBoard[chessBoardX.back()][chessBoardY.back()] = -1;


            step--;
            emit start_emit(step,0,0);



        chessBoardX.pop_back();
        chessBoardY.pop_back();
        preX = chessBoardX.back();
        preY = chessBoardY.back();
        return true;
    }
}

void PVPChess::clearChessBoard(){
    chessBoardX.clear();
    chessBoardY.clear();
    score1.clear();
    score2.clear();
    memset(chessBoard,-1,sizeof(chessBoard));
    step = 0;
}


void PVPChess::setStep(int step){
    this->step = step;
}

int PVPChess::getStep(){
    return this->step;
}

void PVPChess::setWhoWin(int num){
    this->whoWin = num;
}

void PVPChess::addChessBoardXY(int x,int y){
    chessBoardX.push_back(x);
    chessBoardY.push_back(y);
}

void PVPChess::mousePressEvent(QMouseEvent *event){

    if(gameState == true){
        moveY = (event->x()-5)/40;
        moveX = (event->y()-5)/40;
        if(chessBoard[moveX][moveY] == -1){

               if(countWhoFirst == countPlayer1Use){

                    step++;
                    chessBoard[moveX][moveY] = countPlayer1Use;
                    countWhoFirst=countWhoFirst^1;
                    qDebug()<<
                            "-----"<<moveX<<" ;"<<moveY<<"------";
                    addChessBoardXY(moveX,moveY);
                    emit start_emit(step,0,0);
                    preX = moveX;
                    preY = moveY;
                    emit  piece_emit(moveX,moveY,countPlayer1Use);
//                    if(isWin(moveX,moveY)== true){//满足胜利条件
//                        if(countPlayer1Use == 0){//玩家1是黑色
//                            whoWin = 1;//玩家1获胜
//                        }
//                        else whoWin = 2;//玩家2获胜
//                        qDebug("%d %d",gameMode,whoWin);
//                        //gameOver(gameMode,whoWin);
//                    }
//                    else if(step == 255){//平局
//                        //gameOver(gameMode,3);
//                    }
                }
            }

        update();
    }

}
int PVPChess::getChessBoard(int x,int y){
    return chessBoard[x][y];
}
void PVPChess::mouseMoveEvent(QMouseEvent *event) {
    moveX = (event->x()-5)/40;
    moveY = (event->y()-5)/40;
    update();
}
void PVPChess::paintEvent(QPaintEvent *event){

    QPainter *paint=new QPainter;
    paint->begin(this);//开始绘制
    paint->setRenderHint(QPainter::Antialiasing, true);//抗锯齿
    paint->setPen(QPen(Qt::black,2,Qt::SolidLine));
    paint->fillRect(QRect(10,10,590,590), QBrush(QColor(215,156,80)));

    //绘制棋盘线条
    for(int i = 0;i<15;i++){
        paint->drawLine(25+40*i,25,25+40*i,585);
    }
    for(int i = 0;i<15 ;i++){
        paint->drawLine(25,25+40*i,585,25+40*i);
    }


    //绘制五个棋盘黑点
    QBrush  *brush = new QBrush();
    brush->setStyle(Qt::SolidPattern);
    brush->setColor(Qt::black);
    paint->setBrush(*brush);
    paint->drawRect(140,140,10,10);
    paint->drawRect(460,460,10,10);
    paint->drawRect(140,460,10,10);
    paint->drawRect(460,140,10,10);
    paint->drawRect(300,300,10,10);

    //test
    /*
    chessBoard[0][0] = 2;
    chessBoard[8][8] = 1;
    chessBoard[11][8] = 1;
    chessBoard[14][8] = 1;
    chessBoard[7][2] = 1;*/

    //绘制棋子

        for(int i = 0; i < 15;i++){
            for(int j = 0; j< 15 ;j++){
                if(chessBoard[i][j] == 0){//黑子
                    brush->setColor(Qt::black);
                    paint->setPen(Qt::NoPen);
                    paint->setBrush(*brush);
                    paint->drawEllipse(11+j*40,11+i*40,28,28);
                }
                else if(chessBoard[i][j] == 1){//白子
                    brush->setColor(Qt::white);
                    paint->setPen(QPen(Qt::black,2,Qt::SolidLine));
                    paint->setBrush(*brush);
                    paint->drawEllipse(11+j*40,11+i*40,28,28);
                }
            }
        }


    QPen *pen = new QPen(Qt::red);
    pen->setWidth(2);
    paint->setPen(*pen);
    if(step!=0){
        paint->drawLine(preY*40+25-10,preX*40+25,preY*40+25+10,preX*40+25);
        paint->drawLine(preY*40+25,preX*40+25-10,preY*40+25,preX*40+25+10);
    }


    if(moveX*40+25 >=20 && moveX*40 +25 <= 600 && moveY*40+25 >=20 && moveY*40 +25 <= 600 && getChessBoard(moveX,moveY)==0){

        // paint->drawRect(moveX*40+25-15,moveY*40+25-15,30,30);
        paint->drawLine(moveX*40+25-15,moveY*40+25-15,moveX*40+25-5,moveY*40+25-15);
        paint->drawLine(moveX*40+25-15,moveY*40+25-15,moveX*40+25-15,moveY*40+25-5);
        paint->drawLine(moveX*40+25+15,moveY*40+25+15,moveX*40+25+5,moveY*40+25+15);
        paint->drawLine(moveX*40+25+15,moveY*40+25+15,moveX*40+25+15,moveY*40+25+5);

        paint->drawLine(moveX*40+25-15,moveY*40+25+15,moveX*40+25-5,moveY*40+25+15);
        paint->drawLine(moveX*40+25-15,moveY*40+25+15,moveX*40+25-15,moveY*40+25+5);
        paint->drawLine(moveX*40+25+15,moveY*40+25-15,moveX*40+25+5,moveY*40+25-15);
        paint->drawLine(moveX*40+25+15,moveY*40+25-15,moveX*40+25+15,moveY*40+25-5);
    }


    paint->end();//结束绘制
}
