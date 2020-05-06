#include "gamethread.h"
#include<QDebug>
GameThread::GameThread(Game * &game,int row,int col,int *winner)
{
    memcpy(this->chess,game->chess,sizeof (game->chess));
    this->row=row;
    this->col=col;
    this->winner=winner;
}

int GameThread::getChessBoard(int x, int y){
    return chess[x][y];
}

void GameThread::isWin(){
    for (int i = 0; i < 5; i++)
    {
        // 往左5个，往右匹配4个子，20种情况
        if (col - i >= 0 &&
                col - i + 4 < 15 &&
                getChessBoard(row,col - i) == getChessBoard(row,col - i + 1) &&
                getChessBoard(row,col - i) == getChessBoard(row,col - i + 2) &&
                getChessBoard(row,col - i) == getChessBoard(row,col - i + 3) &&
                getChessBoard(row,col - i) == getChessBoard(row,col - i + 4)){
            *winner= getChessBoard(row,col-i);
            return;
        }
    }

    // 竖直方向(上下延伸4个)
    for (int i = 0; i < 5; i++)
    {
        if (row - i >= 0 &&
                row - i + 4 < 15 &&
                getChessBoard(row - i,col) == getChessBoard(row - i + 1,col) &&
                getChessBoard(row - i,col) == getChessBoard(row - i + 2,col) &&
                getChessBoard(row - i,col) == getChessBoard(row - i + 3,col) &&
                getChessBoard(row - i,col) == getChessBoard(row - i + 4,col)){

            *winner=getChessBoard(row-i,col);
            return;
        }

    }

    // 左斜方向
    for (int i = 0; i < 5; i++)
    {
        if (row + i <15 &&
                row + i - 4 >= 0 &&
                col - i >= 0 &&
                col - i + 4 < 15 &&
                getChessBoard(row + i,col - i) == getChessBoard(row + i - 1,col - i + 1) &&
                getChessBoard(row + i,col - i) == getChessBoard(row + i - 2,col - i + 2) &&
                getChessBoard(row + i,col - i) == getChessBoard(row + i - 3,col - i + 3) &&
                getChessBoard(row + i,col - i) == getChessBoard(row + i - 4,col - i + 4)){
            *winner=getChessBoard(row+i,col-i);
            return;
        }
    }

    // 右斜方向
    for (int i = 0; i < 5; i++)
    {
        if (row - i >= 0 &&
                row - i + 4 < 15 &&
                col - i >= 0 &&
                col - i + 4 < 15 &&
                getChessBoard(row - i,col - i) == getChessBoard(row - i + 1,col - i + 1) &&
                getChessBoard(row - i,col - i) == getChessBoard(row - i + 2,col - i + 2) &&
                getChessBoard(row - i,col - i) == getChessBoard(row - i + 3,col - i + 3) &&
                getChessBoard(row - i,col - i) == getChessBoard(row - i + 4,col - i + 4)){
            *winner=getChessBoard(row-i,col-i);
            return ;
        }

    }

    qDebug()<<"-----not over-----";
    *winner=-1;
}

void GameThread::run(){
    isWin();
}
