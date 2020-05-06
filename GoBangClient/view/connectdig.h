#ifndef CONNECTDIG_H
#define CONNECTDIG_H
#include"api/api.h"
#include <QWidget>
#include"roomselect.h"
#include"notifydig.h"
#include"user.h"
#include<QMessageBox>
namespace Ui {
class ConnectDig;
}

class ConnectDig : public QWidget
{
    Q_OBJECT

public:
    explicit ConnectDig(QWidget *parent = nullptr);
    ~ConnectDig();

public slots:

    void on_loginButton_clicked();
    void on_backhomeBt_clicked();
    void loginSucess();
    void loginFailure();
    void regSucess();
    void regFailure();
    void handleBackhome();
signals:
    void backhome();

private slots:
    void on_regBt_clicked();
    void on_bindButton_clicked();


private:
    Ui::ConnectDig *ui;
    API *api;
    NotifyDig * notifyDig;
    RoomSelect *choiceDig;
    bool isValidPswd(QString &);

};

#endif // CONNECTDIG_H
