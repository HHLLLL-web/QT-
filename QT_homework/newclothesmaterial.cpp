#include "newclothesmaterial.h"
#include "ui_newclothesmaterial.h"

newClothesMaterial::newClothesMaterial(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::newClothesMaterial)
{
    ui->setupUi(this);
}

newClothesMaterial::~newClothesMaterial()
{
    delete ui;
}
