#include "newclothesunder.h"
#include "ui_newclothesunder.h"

newClothesUnder::newClothesUnder(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::newClothesUnder)
{
    ui->setupUi(this);
}

newClothesUnder::~newClothesUnder()
{
    delete ui;
}
