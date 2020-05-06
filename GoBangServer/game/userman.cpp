#include "userman.h"

UserMan::UserMan()
{

}

bool UserMan::searchUserByName(QString &name){
    if(users.find(name)!=users.end()){
        return true;
    }else{
        return false;
    }
}

bool UserMan::registerUser(QString &name, QString &pswd){
    if(users.find(name)!=users.end()){
        return false;
    }else{
        users.insert(name,new User(name,pswd));
        return true;
    }
}

User* UserMan::getUserByName(QString &name){
    if(users.find(name)!=users.end()){
        return users[name];
    }else{
        return NULL;
    }
}
bool UserMan::loginJudge(QString &name, QString &pswd){
    if(users.find(name)==users.end()/*||users[name]->getOnline()*/)
        return false;
    else{
        return users[name]->judgePswd(pswd);
    }
}

