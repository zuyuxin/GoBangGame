#include "view/mainwindow.h"
#include <QApplication>
#include <QPushButton>
#include <QPalette>
User * User::instance=NULL;
API* API::instance = nullptr;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("欢乐五子棋-HappyRenJu");


    w.show();//显示窗体
    return a.exec();
}
