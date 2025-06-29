#include "newclothestype.h"
#include "ui_newclothestype.h"
#include "closet.h"
#include <QDebug>
#include "Cloth.h"
newClothesType::newClothesType(int id, QWidget *parent)
    :userID(id), QDialog(parent)
    , ui(new Ui::newClothesType)
{//选其他类型：风格、薄厚等，是最后一步
    ui->setupUi(this);
    ui->type->addItem("上衣");
    ui->type->addItem("下衣");
    ui->type->addItem("连衣裙");
    ui->type->addItem("鞋子");

    ui->style->addItem("休闲");
    ui->style->addItem("正式");
    ui->style->addItem("运动");
    ui->style->addItem("商务");
    ui->style->addItem("美观");

    ui->pattern->addItem("纯色");
    ui->pattern->addItem("格纹");
    ui->pattern->addItem("印花");

    ui->material->addItem("棉");
    ui->material->addItem("麻");
    ui->material->addItem("羊毛");
    ui->material->addItem("丝绸");
    ui->material->addItem("化纤");

    ui->thickness->addItem("薄");
    ui->thickness->addItem("中");
    ui->thickness->addItem("厚");

    ui->season->addItem("春");
    ui->season->addItem("夏");
    ui->season->addItem("秋");
    ui->season->addItem("冬");

    setWindowTitle("码上穿衣-新增衣服");
    QIcon* icon=new QIcon(":/images/icon.png");
    setWindowIcon(*icon);
}

newClothesType::~newClothesType()
{
    delete ui;
}



void newClothesType::on_type_currentTextChanged(const QString &arg1)
{//按不同的选项
    type=arg1;
}


void newClothesType::on_style_currentTextChanged(const QString &arg1)
{
    style=arg1;
}


void newClothesType::on_material_currentTextChanged(const QString &arg1)
{
    material=arg1;
}


void newClothesType::on_pattern_currentTextChanged(const QString &arg1)
{
    pattern=arg1;
}


void newClothesType::on_season_currentTextChanged(const QString &arg1)
{
    season=arg1;
}


void newClothesType::on_thickness_currentTextChanged(const QString &arg1)
{
    thickness=arg1;
}


void newClothesType::on_next_clicked()
{
    //分别保存数据
    type=ui->type->currentText();
    int typeName=-1;
    if(type=="上衣"){typeName=0;}
    else if (type=="下衣"){typeName=1;}
    else if (type=="连衣裙"){typeName=2;}
    else if (type=="鞋子"){typeName=3;}
    else if (type=="配饰"){typeName=4;}
    if(typeName==-1){
        qDebug()<<"type按键返回值和函数内枚举值不对应！";
    }
    else {
        Cloth::saveSingleFeature(userID,"type",QString::number(typeName));
    }

    style=ui->style->currentText();
    Cloth::saveSingleFeature(userID,"style",style);

    material=ui->material->currentText();
    Cloth::saveSingleFeature(userID,"material",material);

    pattern=ui->pattern->currentText();
    Cloth::saveSingleFeature(userID,"pattern",pattern);

    season=ui->season->currentText();
    Cloth::saveSingleFeature(userID,"season",season);

    thickness=ui->thickness->currentText();
    Cloth::saveSingleFeature(userID,"thickness",thickness);

    this->close();
    closet *myCloset = new closet(userID);
    myCloset->show();
}

