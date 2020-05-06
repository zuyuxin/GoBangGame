#ifndef USER_H
#define USER_H

#include<QString>
class User
{
public:
    User();
    User(QString &name,QString &pswd);
    QString getUserName();
    bool judgePswd(QString & pswa);
    void setOnlineState(bool state);
    bool getOnline();
private:
    QString name;
    QString pswd;
    bool online;


};

#endif // USER_H
