#ifndef HISTORY_H
#define HISTORY_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QComboBox>
#include <QScrollArea>
#include <QDialog>
#include <QLabel>
#include <QCheckBox>
#include <QDate>
#include <QList>
namespace Ui {
class history;
}

class history : public QDialog
{
    Q_OBJECT

public:

    int userID;
    QDate date1;
    explicit history(int id, QWidget *parent = nullptr);
    ~history();

private slots:
    void on_dateEdit_userDateChanged(const QDate &date);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::history *ui;
};

#endif // HISTORY_H
