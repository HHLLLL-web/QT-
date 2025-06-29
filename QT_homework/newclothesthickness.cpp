#include "newclothesthickness.h"
#include "ui_newclothesthickness.h"

newClothesThickness::newClothesThickness(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::newClothesThickness)
{
    ui->setupUi(this);
}

newClothesThickness::~newClothesThickness()
{
    delete ui;
}
