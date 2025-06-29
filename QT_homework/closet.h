#ifndef CLOSET_H
#define CLOSET_H
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QComboBox>
#include <QScrollArea>
#include <QDialog>
#include <QLabel>
#include <QCheckBox>
#include "Cloth.h"

namespace Ui {
class closet;
}

class closet : public QDialog
{
    Q_OBJECT

public:
    explicit closet(int id, QWidget *parent = nullptr);
    ~closet();
    int userID;

    class showClothes: public QWidget{

        friend class closet;
    public:
        explicit showClothes(closet * parent, const Cloth &cloth);//*里面要有一个clothes类
        closet *parentCloset;
        QVBoxLayout *total = new QVBoxLayout();//三
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
        QGridLayout * labelSet = new QGridLayout();
        QFrame *frame = new QFrame();
        QCheckBox *checkBox = new QCheckBox("穿它", this);
        bool select;
        void selectChange();
        QPushButton *cancel = new QPushButton("删除");
        void deleteClothes();

    private:
        Cloth m_cloth;
    };


    //五种衣服类别

    QGridLayout *layoutTop = new QGridLayout();
    QGridLayout *layoutUnder = new QGridLayout();
    QGridLayout *layoutDress = new QGridLayout();
    QGridLayout *layoutShoes = new QGridLayout();
    QGridLayout *layoutAccessory = new QGridLayout();

    QLabel *labelTop = new QLabel("上衣");
    QLabel *labelUnder = new QLabel("下衣");
    QLabel *labelDress = new QLabel("连衣裙");
    QLabel *labelShoes = new QLabel("鞋子");
    QLabel *labelAccessory = new QLabel("配饰");

    QScrollArea *scrollArea = new QScrollArea;
    QWidget* scrollWidget = new QWidget;
    QVBoxLayout* scrollLayout = new QVBoxLayout(scrollWidget);
    QVBoxLayout * mainLayout = new QVBoxLayout();


    QVector<showClothes*> vectorTop;
    QVector<showClothes*> vectorUnder;
    QVector<showClothes*> vectorDress;
    QVector<showClothes*> vectorShoes;
    QVector<showClothes*> vectorAccessory;

    QPushButton * selectConfirm = new QPushButton("今天就穿这些");
    QPushButton * add = new QPushButton("加入新衣服");
    QPushButton * returnButton = new QPushButton("返回主页");

    void selectClothes();
    void addClothes();
    void returnMainPage();

private:
    Ui::closet *ui;
    QVector<Cloth> m_clothes; //存储所有衣物数据
    void loadClothesFromSettings();
    void saveClothesToSettings();

};

#endif // CLOSET_H
