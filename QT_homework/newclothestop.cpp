#include "newclothestop.h"
#include "ui_newclothestop.h"

newClothesTop::newClothesTop(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::newClothesTop)
{
    ui->setupUi(this);
}

newClothesTop::~newClothesTop()
{
    delete ui;
}
