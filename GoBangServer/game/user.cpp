#include "user.h"

User::User()
{

}
User::User(QString &name,QString &pswd){
    this->name=name;
    this->pswd=pswd;
    online=false
            ;//表示上线
}
QString User::getUserName(){
    return name;
}

bool User::judgePswd(QString &pswd){
    return this->pswd==pswd;
}

void User::setOnlineState( bool state){
    this->online=state;
}
bool User::getOnline(){
    return online;
}
