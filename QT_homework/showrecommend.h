#ifndef SHOWRECOMMEND_H
#define SHOWRECOMMEND_H

#include <QDialog>
#include <QLayout>
#include <QLabel>
#include <Cloth.h>
#include <QList>
#include <QColor>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QComboBox>
#include <QCheckBox>
#include "Cloth.h"

namespace Ui {
class showRecommend;
}

class showRecommend : public QDialog
{
    Q_OBJECT

public:
    QGridLayout *total = new QGridLayout();
    QGridLayout *layoutTop = new QGridLayout();
    QGridLayout *layoutUnder = new QGridLayout();
    QGridLayout *layoutDress = new QGridLayout();
    QGridLayout *layoutAccessory = new QGridLayout();
    QGridLayout *layoutShoes = new QGridLayout();
    QVBoxLayout *layoutPage = new QVBoxLayout();

    QLabel *labelTop = new QLabel("上衣");
    QLabel *labelUnder = new QLabel("下衣");
    QLabel *labelDress = new QLabel("连衣裙");
    QLabel *labelShoes = new QLabel("鞋子");
    QLabel *labelAccessory = new QLabel("配饰");

    QPushButton * returnButton = new QPushButton("返回主页");

    QScrollArea *scrollArea = new QScrollArea;
    QWidget* scrollWidget = new QWidget;
    QVBoxLayout* scrollLayout = new QVBoxLayout(scrollWidget);
    QVBoxLayout * mainLayout = new QVBoxLayout();

    QString occasion;
    QString season;
    QString weather;
    int temperature;
    QColor color;
    int userID;
    QList<Cloth> recommendClothes;

    void returnMainPage();

    class showClothes: public QWidget{
    public:
        int userID;
        explicit showClothes(int id,Cloth mycloth);//*里面要有一个clothes类
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
    QVector<showClothes*> vectorTop;
    QVector<showClothes*> vectorUnder;
    QVector<showClothes*> vectorDress;
    QVector<showClothes*> vectorShoes;
    QVector<showClothes*> vectorAccessory;
    explicit showRecommend(int _userID,QString _occasion,
                           QString _season,QString _weather,int _temperature,
                           QColor _color, QWidget *parent = nullptr);
    ~showRecommend();

private:
    Ui::showRecommend *ui;
};

#endif // SHOWRECOMMEND_H
