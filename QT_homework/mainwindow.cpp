#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "changeuserinfo.h"
#include "closet.h"
#include "recommend.h"
#include "history.h"
MainWindow::MainWindow(int id, QWidget *parent)
    : QMainWindow(parent)
    ,userID(id) , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("码上穿衣-主页");
    QIcon* icon=new QIcon(":/images/icon.png");
    setWindowIcon(*icon);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_userButton_clicked()
{
    //用户管理按钮
    this->close();
    changeUserInfo *changeuser = new changeUserInfo(userID);
    changeuser->show();
}


void MainWindow::on_closetButton_clicked()
{
    //我的衣橱按钮
    this->close();
    closet *mycloset = new closet(userID);
    mycloset->show();

}


void MainWindow::on_recommendButton_clicked()
{
    this->close();
    recommend *myRec = new recommend(userID);
    myRec->show();

}


void MainWindow::on_calendarButton_clicked()
{
    this->close();
    history *myHis = new history(userID);
    myHis->show();
}

