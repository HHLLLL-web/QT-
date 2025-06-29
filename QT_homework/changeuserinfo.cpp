#include "changeuserinfo.h"
#include "ui_changeuserinfo.h"
#include "mainwindow.h"
#include "QMessageBox"
#include "Cloth.h"
#include "DataBase.h"
changeUserInfo::changeUserInfo(int id, QWidget *parent)
    : userID(id),QDialog(parent)
    , ui(new Ui::changeUserInfo)
{
    //用户管理界面

    QSettings settings2("magicCloset", "UserContent");
    settings2.beginGroup("id_" + QString::number(userID));

    QString username=settings2.value("account").toString();
    QString password=settings2.value("password").toString();
    settings2.endGroup();
    QString confirmpassword=password;
    ui->setupUi(this);
    ui->username->setText(username);
    ui->password->setText(password);
    ui->confirmPassword->setText(password);

}

changeUserInfo::~changeUserInfo()
{
    delete ui;
}


void changeUserInfo::on_confirm_clicked()
{
    //确认按钮点击，先判断填的对不对，如果对了，修改账号密码并返回首页

    QString newUsername=ui->username->text();
    QString newPassword=ui->password->text();
    QString confirmpassword=ui->confirmPassword->text();
    if(newPassword!=confirmpassword){
        QMessageBox::critical(this, tr("提示"), tr("两次输入密码不一致，请重新填写！"));
        return;
    }
    else if((newPassword=="")||(newUsername=="")||(confirmpassword=="")){
        QMessageBox::critical(this, tr("提示"), tr("信息填写不完整"));
        return;
    }
    //*这里需修改信息账号密码
    //先根据id找到用户名
    QSettings settings2("magicCloset", "UserContent");
    settings2.beginGroup("id_" + QString::number(userID));
    QString originAccount=settings2.value("account").toString();
    QString originPassword=settings2.value("password").toString();
    settings2.endGroup();

    QSettings settings("magicCloset", "LoginSystem");
    settings.beginGroup("account_" + originAccount);
    settings.setValue("account",newUsername);
    settings.setValue("password",newPassword);
    settings.endGroup();

    settings2.beginGroup("id_" + QString::number(userID));
    settings2.setValue("account",newUsername);
    settings2.setValue("password",newPassword);
    settings2.endGroup();

    this->close();
    MainWindow *window = new MainWindow(userID);
    window->show();
}


void changeUserInfo::on_return_2_clicked()
{
    //返回首页
    this->close();
    MainWindow * window=new MainWindow(userID);
    window->show();
}

