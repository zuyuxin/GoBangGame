#ifndef ROOM_H
#define ROOM_H


#include<QString>
class Room
{
    struct Player{

        int color;
        int ready;
        QString userName;

        Player(QString name,int ucolor,int uready):color(ucolor),ready(uready),userName(name){
        };
        Player(QString name,int ucolor):color(ucolor),userName(name){
            ready=-1;
        };

    };
public:
    Player * me,*rival;
    Room();
    Room(int);

    bool newPlayer(QString,int );
    void addPlayer(QString,int);
    int getRoomId(){
        return id;
    };

    void deleteRival();
private:

    int id;

};

#endif // ROOM_H
