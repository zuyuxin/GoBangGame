#ifndef GAMETHREAD_H
#define GAMETHREAD_H

#include"game.h"
#include <QThreadPool>

class GameThread:public QRunnable
{
private:
    int chess[15][15];
    int row,col;
    int *winner;
public:
    GameThread(Game * &game,int row,int col,int *winner);
    void run() override;
    void isWin();
    int getChessBoard(int x,int y);
};

#endif // GAMETHREAD_H
