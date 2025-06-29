include "newclothespattern.h"
#include "ui_newclothespattern.h"

newClothesPattern::newClothesPattern(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::newClothesPattern)
{
    ui->setupUi(this);
}

newClothesPattern::~newClothesPattern()
{
    delete ui;
}
