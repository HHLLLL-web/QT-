#include "signup.h"
#include "ui_signup.h"
#include "QMessageBox"
#include "login.h"
signup::signup(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::signup)
{
    ui->setupUi(this);

    setWindowTitle("码上穿衣-注册");
    QIcon* icon=new QIcon(":/images/icon.png");
    setWindowIcon(*icon);
}

signup::~signup()
{
    delete ui;
}

void signup::on_signupButton_clicked()
{
    //注册，如果填写信息有错误，让他再填。如果填写信息正确，将用户名密码保存，返回登录界面登录
    //还需完成：*创建账户，将账号密码保存下来
    QString username=ui->username->text();
    QString password=ui->password->text();
    QString confirmpassword=ui->confirmPassword->text();
    if(password!=confirmpassword){
        QMessageBox::critical(this, tr("提示"), tr("两次输入密码不一致，请重新填写！"));
        return;
    }
    else if((password=="")||(username=="")||(confirmpassword=="")){
        QMessageBox::critical(this, tr("提示"), tr("信息填写不完整"));
        return;
    }

    //*这里需要创建账户ID，保存账号密码
    bool saveSuccess=saveAccount(username,password);
    if(!saveSuccess){
        QMessageBox::critical(this, tr("提示"), tr("用户已存在，请直接登录"));
        return;
    }

    this->close();
    login *myLogin= new login();
    myLogin->show();

}


void signup::on_pushButton_clicked()
{
    this->close();
    login *myLogin= new login();
    myLogin->show();
}

