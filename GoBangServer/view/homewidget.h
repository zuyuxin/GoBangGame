#ifndef HOMEWIDGET_H
#define HOMEWIDGET_H

#include <QWidget>
#include"game/user.h"
#include"game/room.h"
#include"game/game.h"
#include"network/api.h"
namespace Ui {
class HomeWidget;
}
//struct ClientSocket{
//    QHostAddress addr;
//    quint16 port;
//    ClientSocket(QHostAddress ip,quint16 port){
//      this->addr=QHostAddress(ip);
//      this->port=port;
//    };
//};

class HomeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HomeWidget(QWidget *parent = nullptr);
    ~HomeWidget();

private slots:

    void on_bindBt_clicked();

private:
    Ui::HomeWidget *ui;
    API* api;

};

#endif // HOMEWIDGET_H
