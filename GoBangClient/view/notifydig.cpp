#include "view/notifydig.h"
#include "ui_notifydig.h"
#include<QString>
NotifyDig::NotifyDig(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::NotifyDig)
{
    ui->setupUi(this);
}
void NotifyDig::showMsg(QString & msg ){
    ui->notifyLabel->setText(QString(msg));
    this->show();
}
NotifyDig::~NotifyDig()
{
    delete ui;
}

void NotifyDig::on_backBt_clicked()
{
    this->close();
}
