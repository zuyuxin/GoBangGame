#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>
#include <QCloseEvent>
#include <view/pvpwindow.h>
#include <view/pvmwindow.h>
#include"connectdig.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
private slots:

void closeEvent( QCloseEvent * event );

void reshow();

void on_btnPVP_clicked();

void on_btnPVM_clicked();

void on_btnQuit_clicked();

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

signals:
    void clicked();
};

#endif // MAINWINDOW_H
