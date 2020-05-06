#ifndef USER_H
#define USER_H
#include<QString>

class User
{
private:
    User(){};
    User(const User&);
    User & operator =(const User &); //防止拷贝 而是使用引用
    QString userName;
public:
    static User * getInstance(){
        if(instance==NULL){
            instance=new User();
        }
        return instance;
    }
    static User* instance;

    QString geUserName();
    void setUserName(QString name);
    class CGarbo //它的唯一工作就是在析构函数中删除CSingleton的实例
    {

           public:

               ~CGarbo()

               {

                   if( User::instance )

                     delete User::instance;

               }

       };

    static CGarbo Garbo; //定义一个静态成员，程序结束时，系统会自动调用它的析构函数
};

#endif // USER_H
