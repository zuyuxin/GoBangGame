#ifndef USERMAN_H
#define USERMAN_H

#include"game/user.h"
#include<QHash>
#include<QString>
class UserMan
{
private:
    User& operator =(User&);
public:
    UserMan();
    QHash<QString,User*> users;
    bool searchUserByName(QString &name);
    bool registerUser(QString &name,QString &pswd);
    User* getUserByName(QString &name);
    bool loginJudge(QString &name,QString &pswd);

};

#endif // USERMAN_H
