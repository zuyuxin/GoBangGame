#ifndef GAME_H
#define GAME_H

#include<QString>
class Game
{
public:
    int nowPlayer;
    int chess[15][15];
    Game();
    int pressDown(int row,int col, int color);
    void start();  
    void setGameOver();
    int isWin(int,int);
    int getChessBoard(int x,int y);
private:
    enum GameStatus{
        PLAYING,OVER
    };
    GameStatus gameStatus;

};

#endif // PEOPLEGAME_H

//自动匹配玩家/手动匹配
//onlineList在线用户列表 map映射 name对应room 如果room==NULL则创建
//已经在房间的用户列表
