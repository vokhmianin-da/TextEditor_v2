#include "mainwindow.h"
#include <QApplication>
#include "testgui.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();

//    QTest::qExec(new TestGui(), argc, argv);
}
