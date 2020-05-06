#ifndef NOTIFYDIG_H
#define NOTIFYDIG_H

#include <QWidget>
#include<QString>
namespace Ui {
class NotifyDig;
}

class NotifyDig : public QWidget
{
    Q_OBJECT

public:
    explicit NotifyDig(QWidget *parent = nullptr);
    ~NotifyDig();
    void showMsg(QString &);

signals:

private slots:
    void on_backBt_clicked();

private:
    Ui::NotifyDig *ui;


};

#endif // NOTIFYDIG_H
