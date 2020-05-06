#include "homewidget.h"
#include "ui_homewidget.h"
#include<iostream>
#include<QTcpSocket>

HomeWidget::HomeWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::HomeWidget)
{
    ui->setupUi(this);


}

HomeWidget::~HomeWidget()
{
    delete ui;
}


void HomeWidget::on_bindBt_clicked()
{
    QString ip=ui->inputAdress->text();
    QString port=ui->inputPort->text();
    QString msg;
    api=API::getInstance();
    api->initServer(8888);

   // bool ret=socket->bind(port.toInt());
//    if(!ret)
//        msg="bind fail"+socket->errorString();
//    else{
//         msg="bind sucess";
//    }
    //ui->messageList->append(msg);

    //qDebug()<<msg.toUtf8().data();
}

