#include "mainwindow.h"
#include <QApplication>
#include "myread.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();

    MyRead mread;
    mread.start();

    return a.exec();
}
