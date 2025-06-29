#ifndef SHOWHISTORY_H
#define SHOWHISTORY_H

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
#include "Cloth.h"
namespace Ui {
class showHistory;
}

class showHistory : public QDialog
{
    Q_OBJECT

public:
    int userID;
    explicit showHistory(int id,QDate d,QWidget *parent = nullptr);
    QList<QList<Cloth>> totalClothes;
    QDate date;
    class showClothes: public QWidget{
    public:
        int userID;
        explicit showClothes(int id,Cloth cloth);//*里面要有一个clothes类
        Cloth mycloth;
        QVBoxLayout *total = new QVBoxLayout();//三
        QGridLayout * labelSet = new QGridLayout();
        QFrame *frame = new QFrame();
        QLabel *labelName= new QLabel();
        QLabel *labelPosition = new QLabel();
        QLabel *labelType= new QLabel();
        QLabel *labelStyle= new QLabel();
        QLabel *labelColor=new QLabel();
        QLabel *labelPattern = new QLabel();
        QLabel *labelMaterial = new QLabel();
        QLabel *labelThickness = new QLabel();
        QLabel *labelSeason = new QLabel();
        //以上8个label描述特征
    };
    void returnMainPage();
    QPushButton * returnButton = new QPushButton("返回主页");
    QScrollArea *scrollArea = new QScrollArea;
    QWidget* scrollWidget = new QWidget;
    QVBoxLayout* scrollLayout = new QVBoxLayout(scrollWidget);
    QVBoxLayout * mainLayout = new QVBoxLayout();

    ~showHistory();

private:
    Ui::showHistory *ui;
};

#endif // SHOWHISTORY_H
