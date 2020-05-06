#ifndef API_H
#define API_H
#include<QObject>
#include"net/client.h"
class API :public QObject
{
    Q_OBJECT
private:
    explicit API(QObject *parent = nullptr);
private:

    const QByteArray CmdGameBegin = "GAME_BEGIN";  //请求建立房间
    const QByteArray CmdGameJion = "GAME_JION";  //请求加入游戏
    const QByteArray CmdRoomCreat = "Room_CREAT";  //请求建立房间
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
public:
    Client *client;
    static API *instance;
    static API * getInstance(){
        if(instance==NULL){
            instance=new API();
        }
        return instance;
    }
    void bindPort(int);
    bool connectToHost();
    void sendLoginMsg(QString &,QString &);
    void sendRegMsg(QString &,QString &);
    void sendRoomEnter(QString );
    void sendReady(QString,QString);
    void sendQuitRoom(QString ,QString);
    void sendPiece(int,int,int,int);
signals:
    void loginSucess();
    void loginFailiure();
    void regSucess();
    void regFailiure();
    void roomEnterRes(int roomId,int);
    void roomJoin(int ,QString ,int,int);
    void newPlayer(QString &,int);
    void gameBegin();
    void setRivalReady();
    void rivalQuitRoom();
    void posDown(int,int,int,int);
    void synNowColor(int,int,int);
    void gameOver(int);
public slots:
    void handleRecvSignal(QByteArray ,QByteArray);

};

#endif // API_H
