#include "newclothes.h"
#include "ui_newclothes.h"
#include "newclothespic.h"
#include <QMessageBox>
#include <QSettings>

newClothes::newClothes(int id, QWidget *parent)
    :userID(id), QDialog(parent)
    , ui(new Ui::newClothes)
{
    //这个界面是先添加衣服名字和位置，再点下一步
    ui->setupUi(this);
    setWindowTitle("码上穿衣-新增衣服");
    QIcon* icon=new QIcon(":/images/icon.png");
    setWindowIcon(*icon);
}

newClothes::~newClothes()
{
    delete ui;
}



void newClothes::on_next_clicked()
{

    QString name=ui->name->text();
    QString position=ui->position->text();

    if((name=="")||(position=="")){
        QMessageBox::critical(this, tr("提示"), tr("未完整填写！"));
        return;
    }

    Cloth::saveSingleFeature(userID,"name",name);
    Cloth::saveSingleFeature(userID,"position",position);

    this->close();
    newClothesPic *ClothesPic = new newClothesPic(userID);
    ClothesPic->show();
}

