#ifndef ROOM_H
#define ROOM_H
#include<string>
#include"game.h"
#include"user.h"
#include"network/api.h"

// rooms 队列
// 根据房间人数排列 房间数越大排列在前
// 属性：
// players 人数
// 白棋选手
// 黑棋选手
// 游戏逻辑判断
// 状态 0人ready  1人ready 两人ready->游戏开始
// 游戏结束
class Room
{
private:
    int roomId;
    int playersNum;
    int readys;
    Game * game;
    //int judgeColor(std::string player);
    //void setPlayer(PiecesType);
    //std::string match(std::string player);
    //void readyGame();
   // std::string judgeOpponent(std::string);
    struct Player{
        QString socketId;
        int color;
        int ready;
        QString userName;
        Player(QString &name):userName(name){
          color=0;//白
          ready=-1;
        };

    };

    Player * first,*second;
    const QByteArray CmdSplit = ";";  //间隔符
    QString judgeRival(int );
    QString judgePlayer(int);
    void reInit();
public:
    Room();
    Room(int);
    Room(Room* room);
    int addPlayer(QString &,QString &);
    void setRoomId(int id);
    bool deletePlayer(QString &);
    int getPlayersNum();
    int getRoomId();
    int setReady(QString &);
    void pressDown(QByteArray &row,QByteArray & col,QByteArray &color);
    void broadCastRoomMsg();
    bool hasPlayer(QString &);

   // void pressDown(QString &,int ,int );
};

#endif // ROOM_H
