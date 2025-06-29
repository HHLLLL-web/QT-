#include "newclothespic.h"
#include "ui_newclothespic.h"
#include "QColor"
#include "QColorDialog"
#include <QFileDialog>
#include <QMessageBox>
#include <QPixmap>
#include "newclothestype.h"
#include <QSettings>
newClothesPic::newClothesPic(int id, QWidget *parent)
    : userID(id),QDialog(parent)
    , ui(new Ui::newClothesPic)
{//添加衣服的第二步，传图片，选颜色
    ui->setupUi(this);
    setWindowTitle("码上穿衣-新增衣服");
    QIcon* icon=new QIcon(":/images/icon.png");
    setWindowIcon(*icon);
}

newClothesPic::~newClothesPic()
{
    delete ui;
}

void newClothesPic::on_color_clicked()
{
    QColor color = QColorDialog::getColor(QColor(0,255,0),this,"窗口标题");

    QString rgbString=QString ("rgb(%1,%2,%3)").arg(color.red()).arg(color.green()).arg(color.blue());

    Cloth::saveSingleFeature(userID,"color",rgbString);

    qDebug()<<color;
    //记录颜色

}


void newClothesPic::on_picture_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(
        this,
        "选择图片",
        QDir::homePath(),
        "图片文件 (*.jpg *.jpeg *.png *.bmp)"
        );

    if (filePath.isEmpty()) {
        QMessageBox::warning(this, "错误", "未选择文件");
        return;
    }

    Cloth::saveSingleFeature(userID,"path",filePath);

    // 处理选中的图片文件
    QPixmap pixmap(filePath);
    if (pixmap.isNull()) {
        QMessageBox::warning(this, "错误", "无法加载图片");
        return;
    }

    // 在QLabel中显示图片（缩放适应）
    ui->label->resize(300,300);
    ui->label->setPixmap(pixmap.scaled(ui->label->size(), Qt::KeepAspectRatio));
}


void newClothesPic::on_next_clicked()
{
    QSettings settings("magicCloset", "UserContent");
    settings.beginGroup(QString("id_%1").arg(userID));
    int size = settings.beginReadArray("clothes");
    settings.setArrayIndex(size-1);

    bool selectColor=settings.contains("path");
    bool selectPath=settings.contains("color");

    settings.endArray();
    settings.endGroup();
    if(!selectColor)
    {
        QMessageBox::warning(this,"提示","未选择图片！");
    }
    if(!selectPath)
    {
        QMessageBox::warning(this,"提示","未选择颜色！");
    }
    if(selectPath and selectColor){
        this->close();
        newClothesType *type = new newClothesType(userID);
        type->show();
    }
}

