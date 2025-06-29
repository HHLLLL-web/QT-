#include "recommend.h"
#include "ui_recommend.h"
#include "Cloth.h"
#include <QString>
#include <QSettings>
#include "recommend_algorithm.h"
#include "QVector"
#include "QColor"
#include "QColorDialog"
#include "mainwindow.h"
#include "showrecommend.h"
recommend::recommend(int id,QWidget *parent)
    : userID(id),QDialog(parent)
    , ui(new Ui::recommend)
{
    ui->setupUi(this);
    ui->style->addItem("休闲");
    ui->style->addItem("正式");
    ui->style->addItem("运动");
    ui->style->addItem("商务");
    ui->style->addItem("美观");
    ui->season->addItem("春");
    ui->season->addItem("夏");
    ui->season->addItem("秋");
    ui->season->addItem("冬");
    ui->weather->addItem("下雨");
    ui->weather->addItem("下雪");
    ui->weather->addItem("大风");
    ui->weather->addItem("多云");
    ui->weather->addItem("晴天");
    ui->weather->addItem("暴晒");

    setWindowTitle("码上穿衣-穿搭推荐");
    QIcon* icon=new QIcon(":/images/icon.png");
    setWindowIcon(*icon);
}

recommend::~recommend()
{
    delete ui;
}


void recommend::on_color_clicked()
{
    QColor color = QColorDialog::getColor(QColor(0,255,0),this,"窗口标题");
}


void recommend::on_next_clicked()
{
    this->close();
    showRecommend * myShow = new showRecommend(userID,style,season,weather,temperature,color);
    myShow->show();

}

void recommend::on_style_currentTextChanged(const QString &arg1)
{
    style=arg1;
}


void recommend::on_temperature_valueChanged(int arg1)
{
    temperature = arg1;
}


void recommend::on_season_currentTextChanged(const QString &arg1)
{
    season=arg1;
}


void recommend::on_weather_currentTextChanged(const QString &arg1)
{
    weather=arg1;
}


void recommend::on_return_2_clicked()
{
    this->close();
    MainWindow *window = new MainWindow(userID);
    window->show();
}

