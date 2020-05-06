#ifndef API_H
#define API_H

#include<QObject>
#include"network/server.h"
#include"game/user.h"
#include"game/userman.h"


class API : public QObject
{
    Q_OBJECT
private:
    explicit API(QObject *parent = nullptr);

    static API* instance;
    const QByteArray CmdGameBegin = "GAME_BEGIN";  //请求建立房间
    const QByteArray CmdGameJion = "GAME_JION";  //请求加入游戏
    const QByteArray CmdRoomCreat = "Room_CREAT";
    const QByteArray CmdRoomCreatRes="Room_CREAT_RES";
    const QByteArray CmdRoomJoin="ROOM_JOIN";
    const QByteArray CmdNewPlayer="NewPlayer";
    const QByteArray CmdReady="READY";
    const QByteArray CmdPosDown = "POSITION";  //发送落子位置信息
    const QByteArray CmdSYNPiece="SYNCOLOR";
    const QByteArray CmdForPeace = "FORPEACE"; //对方求和指令
    const QByteArray CmdForPeaceReturn = "FORPEACE_RETURN"; //对方求和指令,是
    const QByteArray CmdForRegret = "FORREGRET";  //对方请求悔棋指令
    const QByteArray CmdForRegretReturn = "FORREGRET_RETURN"; //对方反馈的请求悔棋，是
    const QByteArray CmdGiveUp = "GIVE_UP";  //发送认输指令
    const QByteArray CmdSendMsg = "SEND_MESSAGE";  //发送对话消息
    const QByteArray CmdGameOver = "GAMEOVER";  //游戏结束指令
    const QByteArray CmdTimeOut = "TIMEOUT";  //落子超时指令
    const QByteArray CmdGameQuit = "GAME_QUIT";  //游戏退出指令
    const QByteArray CmdLogin = "LOGIN";  //登入指令
    const QByteArray CmdLoginState="LOGINSTATE";
    const QByteArray CmdReg="REGISTER";
    const QByteArray CmdRegState="REGISTERSTATE";

    //控制内容
    const QByteArray CmdGameInfo= "GAME_INFO";  //服务端下发游戏大厅指令
    const QByteArray CmdGameInfoAdd = "GAME_INFO_ADD";  //服务端下发游戏大厅指令,添加客户
    const QByteArray CmdGameInfoRemove = "GAME_INFO_REMOVE";  //服务端下发游戏大厅指令，移除客户
    const QByteArray CmdServerClose = "SERVER_CLOSE";  //服务端停止服务指令

    //特殊指令
    const QByteArray CmdEnd = "\r\n";  //结束符
    const QByteArray CmdSplit = ";";  //间隔符
    const char argSplit=';';
    Server* server;
    UserMan* userMan;
public:

    static API* getInstance() {
        if(instance == nullptr) {
            instance = new API();
        }
        return instance;
    }

    static API& getInstance2() {
        static API api;
        return api;
    }

    Server* getServer();
    class CGarbo //它的唯一工作就是在析构函数中删除CSingleton的实例

       {

           public:

               ~CGarbo()

               {

                   if( instance )

                     delete API::instance;

               }

       };

    static CGarbo Garbo; //定义一个静态成员，程序结束时，系统会自动调用它的析构函数


    void initServer(quint16 port);

public slots:
    void loginHandle(QByteArray ,QByteArray );
    void RegsiterHandle(QByteArray ,QByteArray);
    void EnterRoomHandle(QByteArray,QByteArray);
    void ReadyHandle(QByteArray,QByteArray);
    void PieceHandle(QByteArray,QByteArray);
    void quitRoomHandle(QByteArray,QByteArray);
    void sendRoomCreateRes(QByteArray, QByteArray ,QString &socketId);
    void sendEnterRoomMsg(QByteArray,QByteArray,QByteArray,QString &socketId);
    void sendRoomNewPlayer(QByteArray,QString &);
    void sendStartGame(QString &);
    void sendReady(QString&);
    void sendQuitRoom(QString &);
    void sendPiece(QByteArray &,QByteArray &,QByteArray&,QString &,int);
    void sendUndoPiece(QByteArray &row,QByteArray & col,int nowColor,QString &socketId);
    void sendGameOver(QByteArray& ,QString &,QString &);
signals:
    void enterRoom(QString &,QString &);
    void readyGame(int,QString );
    void quitGame(int,QString);
    void posDown(QByteArray&,QByteArray&,QByteArray&,QByteArray&);
};

#endif // API_H
