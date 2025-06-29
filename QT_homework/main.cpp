#include "mainwindow.h"
#include "login.cpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    login *mylogin=new login();
    mylogin->show();
    return a.exec();
}
