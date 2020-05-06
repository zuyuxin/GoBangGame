#include "game.h"
#include<QDebug>
Game::Game()
{
    memset(chess,-1,sizeof(chess));
    gameStatus=OVER;
    nowPlayer=1;//默认白棋先下
}

void Game::start(){
    gameStatus=PLAYING;
    memset(chess,-1,sizeof (chess));
}

int Game::pressDown(int row, int col, int color){
    if(gameStatus!=PLAYING||color!=nowPlayer)
        return false;
    else if(color==nowPlayer){
        chess[row][col]=color;
        nowPlayer=nowPlayer^1;//0^1=1 1^1=0
        return true;
    }
}

void Game::setGameOver(){
    gameStatus=OVER;
}

int Game::getChessBoard(int x, int y){
    return chess[x][y];
}

int Game::isWin(int row,int col){
    for (int i = 0; i < 5; i++)
    {
        // 往左5个，往右匹配4个子，20种情况
        if (col - i >= 0 &&
                col - i + 4 < 15 &&
                getChessBoard(row,col - i) == getChessBoard(row,col - i + 1) &&
                getChessBoard(row,col - i) == getChessBoard(row,col - i + 2) &&
                getChessBoard(row,col - i) == getChessBoard(row,col - i + 3) &&
                getChessBoard(row,col - i) == getChessBoard(row,col - i + 4)){
            return getChessBoard(row,col-i);

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

            return getChessBoard(row-i,col);

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
            return getChessBoard(row+i,col-i);

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
            return getChessBoard(row-i,col-i);

        }

    }

    qDebug()<<"-----not over-----";
    return -1;
}
