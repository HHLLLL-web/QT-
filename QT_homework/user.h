#ifndef USER_H
#define USER_H

#include <QDialog>

namespace Ui {
class user;
}

class user : public QDialog
{
    Q_OBJECT

public:
    explicit user(int id,QWidget *parent = nullptr);
    ~user();
    int userID;

private:
    Ui::user *ui;
};

#endif // USER_H
