#include "mainwindow.h"
#include"users.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    users u;
    u.show();
    return a.exec();
}
