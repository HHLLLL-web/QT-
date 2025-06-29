#include "newclothesstyle.h"
#include "ui_newclothesstyle.h"

newClothesStyle::newClothesStyle(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::newClothesStyle)
{
    ui->setupUi(this);
}

newClothesStyle::~newClothesStyle()
{
    delete ui;
}
