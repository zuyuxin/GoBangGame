#include "view/connectdig.h"
#include "ui_connectdig.h"
#include"api/api.h"
ConnectDig::ConnectDig(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConnectDig)
{

    QColor btnColor = QColor(0,161,241);

    QPalette btnPalette = QPalette(btnColor);
    QPalette palette(this->palette());
    palette.setColor(QPalette::Background, QColor(124,187,0));
    this->setPalette(palette);

    ui->setupUi(this);

    api=API::getInstance();

    notifyDig=new NotifyDig();

    choiceDig=NULL;
}

ConnectDig::~ConnectDig()
{
    if(notifyDig)
        delete notifyDig;
    delete ui;
}


/*登录按钮*/
void ConnectDig::on_loginButton_clicked()
{
     QString name=ui->lineEditUserName->text();
     QString pswd=ui->lineEditPsw->text();
     User *user=User::getInstance();
     user->setUserName(name);
     api->sendLoginMsg(name,pswd);
     connect(api,&API::loginSucess,this,&ConnectDig::loginSucess);
     connect(api,&API::loginFailiure,this,&ConnectDig::loginFailure);
}

void ConnectDig::on_backhomeBt_clicked()
{
    this->close();
    emit backhome();
}

void ConnectDig::loginSucess(){
    this->close();
    if(!choiceDig)
        choiceDig=new RoomSelect();
    if(choiceDig){
        choiceDig->show();
        connect(choiceDig,&RoomSelect::backhome,this,&ConnectDig::handleBackhome);
    }else{
        qDebug()<<"------some erors happened to th choiceDig-----";
    }
}

void ConnectDig::handleBackhome(){
    if(choiceDig)
        delete choiceDig;
    this->show();
}

void ConnectDig::loginFailure(){
    QString retmsg="用户名或密码错误";
    if(!notifyDig)
        notifyDig=new NotifyDig();
    notifyDig->showMsg(retmsg);
}

void ConnectDig::on_regBt_clicked()
{
    QString name=ui->lineEditUserName->text();
    QString pswd=ui->lineEditPsw->text();
    if(!isValidPswd(pswd)){
       // QMessageBox box=new QMessageBox(this);
        QString retmsg="密码不足6位，请重新设置至少6位的密码";
        if(!notifyDig)
            notifyDig=new NotifyDig();
        notifyDig->showMsg(retmsg);
    }else{
        User *user=User::getInstance();
        user->setUserName(name);
        api->sendRegMsg(name,pswd);
        connect(api,&API::regSucess,this,&ConnectDig::regSucess);
        connect(api,&API::regFailiure,this,&ConnectDig::regFailure);
    }
}
bool ConnectDig::isValidPswd(QString & str){
    return str.length()>=6;
}
void ConnectDig::regSucess(){
    if(!notifyDig)
        notifyDig=new NotifyDig();
    QString retmsg="注册成功";
    notifyDig->showMsg(retmsg);
}

void ConnectDig::regFailure(){
    if(!notifyDig)
        notifyDig=new NotifyDig();
    QString retmsg="用户名被占用";
    notifyDig->showMsg(retmsg);
}


void ConnectDig::on_bindButton_clicked()
{
    api->bindPort(ui->myportInput->text().toInt());
    api->connectToHost();
    ui->bindButton->setEnabled(false);

}

