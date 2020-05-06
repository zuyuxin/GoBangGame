#include "user.h"



QString User::geUserName(){
    return this->userName;
}

void User::setUserName(QString name){
    this->userName=name;
}
