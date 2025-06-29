#ifndef CHANGEUSERINFO_H
#define CHANGEUSERINFO_H

#include <QDialog>

namespace Ui {
class changeUserInfo;
}

class changeUserInfo : public QDialog
{
    Q_OBJECT

public:
    explicit changeUserInfo(int id, QWidget *parent = nullptr);
    ~changeUserInfo();
    int userID;

private slots:

    void on_confirm_clicked();

    void on_return_2_clicked();

private:
    Ui::changeUserInfo *ui;
};

#endif // CHANGEUSERINFO_H
