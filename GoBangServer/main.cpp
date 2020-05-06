
#include"view/homewidget.h"
#include <QApplication>
#include"gobang.h"
API* API::instance = nullptr;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   // HomeWidget w;
   // API &api = API::getInstance2();
   // w.show();
//    API * api=API::getInstance();
//    api->initServer(8888);
    GoBang * gameEngine=new GoBang();
    gameEngine->start();
    return a.exec();
}
