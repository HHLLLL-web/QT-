#include "user.h"
#include "ui_user.h"

user::user(int id,QWidget *parent)
    : userID(id),QDialog(parent)
    , ui(new Ui::user)
{
    ui->setupUi(this);
}

user::~user()
{
    delete ui;
}
