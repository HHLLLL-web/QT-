#include "login.h"
#include "ui_login.h"
#include "signup.h"
#include "QMessageBox"
#include "mainwindow.h"
#include "DataBase.h"

login::login(QWidget *parent)//登录界面
    : QDialog(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);
    ui->usernameLine->setPlaceholderText("用户名");
    ui->passwordLine->setPlaceholderText("密码");
    setWindowTitle("码上穿衣-登录");
    QIcon* icon=new QIcon(":/images/icon.png");
    setWindowIcon(*icon);
}

login::~login()
{
    delete ui;
}

void login::on_signupButton_clicked()
{//按注册按钮
    this->close();
    signup* mySignup = new signup();
    mySignup->show();
}


void login::on_loginButton_clicked()
{
    //登录按钮按下，判断信息有没有错误，没有就进入主页面
    //*还需完成：1.判断输入的账号密码是否正确 2.用户要有一个ID，以便之后主界面载入用户数据之类的
    QString username=ui->usernameLine->text();
    QString password=ui->passwordLine->text();
    if((password=="")||(username=="")){
        QMessageBox::critical(this, tr("提示"), tr("信息填写不完整"));
        return;
    }

    if(!checkPassword(username,password)){//*这里需要函数，判断输入的账号密码是否正确
        QMessageBox::critical(this, tr("提示"), tr("密码错误！"));
        return;
    }

    //根据用户名获取用户Id
    QSettings settings("magicCloset", "LoginSystem");
    settings.beginGroup("account_" + username);
    int userID=settings.value("Id").toInt();//*这里需要获取用户ID
    settings.endGroup();

    this->close();
    MainWindow *window = new MainWindow(userID);
    window->show();

}

