#include "history.h"
#include "ui_history.h"
#include "Cloth.h"
#include "showhistory.h"
#include "mainwindow.h"
history::history(int id,QWidget *parent)
    :userID(id), QDialog(parent)
    , ui(new Ui::history)
{
    ui->setupUi(this);
    setWindowTitle("码上穿衣-穿搭日历");
    QIcon* icon=new QIcon(":/images/icon.png");
    setWindowIcon(*icon);

}
history::~history()
{
    delete ui;
}

void history::on_dateEdit_userDateChanged(const QDate &date)
{
    date1=date;
}


void history::on_pushButton_clicked()
{
    this->close();
    showHistory * showH = new showHistory(userID,date1);
    showH->show();
}


void history::on_pushButton_2_clicked()
{
    this->close();
    MainWindow * mainW = new MainWindow(userID);
    mainW->show();
}

