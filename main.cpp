#include "mainwindow.h"
#include"startscene.h"
#include <QApplication>
#include"endscene.h"
#include"doublescene.h"
#include"test.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StartScene w;
    w.show();
    return a.exec();
//    Test test;
//    QTest::qExec(&test);
}
