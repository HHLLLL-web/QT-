#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(int id, QWidget *parent = nullptr);
    ~MainWindow();
    int userID;

private slots:
    void on_userButton_clicked();

    void on_closetButton_clicked();

    void on_recommendButton_clicked();

    void on_calendarButton_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
