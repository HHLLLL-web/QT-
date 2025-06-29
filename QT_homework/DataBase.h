#ifndef DATABASE_H
#define DATABASE_H
#include <QSettings>
#include <QMessageBox>
#include "Cloth.h"

//文件中存在settings("magicCloset", "LoginSystem")和settings("magicCloset", "UserContent")
//前者根据username查询，存储：密码和id
//后者根据 用户id  查询，存储：username、密码、账户的所有衣服信息以及所有历史使用记录

//检查用户是否已存在
inline bool isUserExist(QSettings &settings, const QString &groupName) {
    return settings.childGroups().contains("account_"+groupName);
}

// 存储账户密码 返回是否成功
inline bool saveAccount(const QString &username, const QString &password) {
    //根据username存储
    QSettings settings("magicCloset", "LoginSystem");
    //检查是否已存在
    if (isUserExist(settings, username)) {
        return false;
    }
    //如果之前还没有账户存在，需要新建lastUserId这个标签
    if(!settings.contains("lastUserId")){
        settings.setValue("lastUserId",0);
    }
    //获取应创建的id，为数据库内历史存在过的用户数量+1
    int lastUserId=settings.value("lastUserId",0).toInt();
    int newId=lastUserId+1;

    settings.beginGroup("account_" + username);
    settings.setValue("password", password);//用户id根据创建顺序分发，从1开始。
    settings.setValue("Id",newId);
    settings.endGroup();

    settings.setValue("lastUserId",newId);

    //根据id存储
    QSettings settings2("magicCloset", "UserContent");
    settings2.beginGroup("id_" + QString::number(newId));
    settings2.setValue("account",username);
    settings2.setValue("password",password);
    settings2.endGroup();

    return true;
}

inline bool checkPassword(const QString &inputUsername, const QString &inputPassword) {
    QSettings settings("magicCloset", "LoginSystem");

    settings.beginGroup("account_" + inputUsername);
    QString savedPassword = settings.value("password").toString();
    settings.endGroup();

    return ( inputPassword == savedPassword);
}

#endif // DATABASE_H
