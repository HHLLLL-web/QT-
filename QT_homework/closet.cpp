#include "closet.h"
#include "ui_closet.h"
#include "newclothes.h"
#include "mainwindow.h"
#include "DataBase.h"
#include <QLayout>
#include <QPixmap>
#include <QIcon>
closet::closet(int id, QWidget *parent)
    : userID(id), QDialog(parent)
    , ui(new Ui::closet)
{
    //我的衣橱界面

    //加载用户username
    QSettings settings("magicCloset", "UserContent");
    settings.beginGroup("id_"+QString::number(userID));
    QString username=settings.value("username").toString();
    settings.endGroup();

    //初始化ui
    ui->setupUi(this);
    scrollArea->setWidgetResizable(true);
    resize(900,600);

    // 加载衣物数据
    loadClothesFromSettings();

    // //把衣服数据输进来
    // int clothesNum = 25;//*获取它的衣服数量

    // 根据衣物数据创建显示项
    for (const Cloth &cloth : m_clothes) {
        showClothes *item = new showClothes(this, cloth);

        switch(cloth.type()) {
        case Cloth::Top:
            vectorTop.append(item);
            break;
        case Cloth::Under:
            vectorUnder.append(item);
            break;
        case Cloth::Dress:
            vectorDress.append(item);
            break;
        case Cloth::Shoes:
            vectorShoes.append(item);
            break;
        case Cloth::Accessory:
            vectorAccessory.append(item);
            break;
        }
    }
    //设置不同类别的衣服的显示格式，2件为1组

    labelTop->setStyleSheet("QLabel{font-size:18px;font-family:黑体;font-weight:bold;letter-spacing:1px;}");
    labelUnder->setStyleSheet("QLabel{font-size:18px;font-family:黑体;font-weight:bold;letter-spacing:1px;}");
    labelDress->setStyleSheet("QLabel{font-size:18px;font-family:黑体;font-weight:bold;letter-spacing:1px;}");
    labelShoes->setStyleSheet("QLabel{font-size:18px;font-family:黑体;font-weight:bold;letter-spacing:1px;}");
    labelAccessory->setStyleSheet("QLabel{font-size:18px;font-family:黑体;font-weight:bold;letter-spacing:1px;}");
    layoutTop->setSpacing(15);
    layoutUnder->setSpacing(15);
    layoutDress->setSpacing(15);
    layoutShoes->setSpacing(15);
    layoutAccessory->setSpacing(15);

    layoutTop->setContentsMargins(2,20,2,20);
    layoutUnder->setContentsMargins(2,20,2,20);
    layoutDress->setContentsMargins(2,20,2,20);
    layoutShoes->setContentsMargins(2,20,2,20);
    layoutAccessory->setContentsMargins(2,20,2,20);

    layoutTop->addWidget(labelTop,0,0,1,2);
    layoutUnder->addWidget(labelUnder,0,0,1,2);
    layoutDress->addWidget(labelDress,0,0,1,2);
    layoutShoes->addWidget(labelShoes,0,0,1,2);
    layoutAccessory->addWidget(labelAccessory,0,0,1,2);

    QFrame *hLine1 = new QFrame;
    hLine1->setFrameShape(QFrame::HLine);
    layoutTop->addWidget(hLine1,1,0,1,2);

    QFrame *hLine2 = new QFrame;
    hLine2->setFrameShape(QFrame::HLine);
    layoutUnder->addWidget(hLine2,1,0,1,2);

    QFrame *hLine3 = new QFrame;
    hLine3->setFrameShape(QFrame::HLine);
    layoutDress->addWidget(hLine3,1,0,1,2);

    QFrame *hLine4 = new QFrame;
    hLine4->setFrameShape(QFrame::HLine);
    layoutShoes->addWidget(hLine4,1,0,1,2);

    QFrame *hLine5 = new QFrame;
    hLine5->setFrameShape(QFrame::HLine);
    layoutAccessory->addWidget(hLine5,1,0,1,2);

    for (int i=0;i<vectorTop.size();i++)
        layoutTop->addWidget(vectorTop[i],i/2+2,i%2);
    for (int i=0;i<vectorUnder.size();i++)
        layoutUnder->addWidget(vectorUnder[i],i/2+2,i%2);
    for (int i=0;i<vectorDress.size();i++)
        layoutDress->addWidget(vectorDress[i],i/2+2,i%2);
    for (int i=0;i<vectorShoes.size();i++)
        layoutShoes->addWidget(vectorShoes[i],i/2+2,i%2);
    for (int i=0;i<vectorAccessory.size();i++)
        layoutAccessory->addWidget(vectorAccessory[i],i/2+2,i%2);

    //滑动模块把几组衣服加入进去
    scrollLayout->addLayout(layoutTop);
    scrollLayout->addLayout(layoutUnder);
    scrollLayout->addLayout(layoutDress);
    scrollLayout->addLayout(layoutDress);
    scrollLayout->addLayout(layoutShoes);
    scrollLayout->addLayout(layoutAccessory);

    scrollArea->setWidget(scrollWidget);
    scrollArea->setWidgetResizable(true);
    //主页面加入
    QLabel * title = new QLabel("我的衣橱");
    title->setStyleSheet("QLabel{font-size:24px;font-family:微软雅黑;font-weight:bold;letter-spacing:1px;}");
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(30,20,30,20);
    mainLayout->addWidget(title);
    mainLayout->addWidget(scrollArea);
    QHBoxLayout * buttonLayoutTotal = new QHBoxLayout();
    buttonLayoutTotal->addWidget(selectConfirm);
    buttonLayoutTotal->addWidget(add);
    buttonLayoutTotal->addWidget(returnButton);
    mainLayout->addLayout(buttonLayoutTotal);
    setLayout(mainLayout);

    connect(selectConfirm,&QPushButton::clicked,this,&closet::selectClothes);
    connect(add,&QPushButton::clicked,this,&closet::addClothes);
    connect(returnButton,&QPushButton::clicked,this,&closet::returnMainPage);

    setWindowTitle("码上穿衣-我的衣橱");
    QIcon* icon=new QIcon(":/images/icon.png");
    setWindowIcon(*icon);

}
closet::showClothes::showClothes(closet *parent,const Cloth &cloth):parentCloset(parent),m_cloth(cloth){
    //这个是衣橱里每个衣服展示的类

    parentCloset=parent;
    QVBoxLayout *total = new QVBoxLayout();//三
    checkBox->setChecked(false);
    select=false;
    QPixmap image(cloth.path());
    if(image.isNull()) {
        qDebug() << "Failed to load image";
    }

    labelName->setText(cloth.name());
    labelName->setStyleSheet("QLabel{font-size:16px;font-family:宋体;font-weight:bold;letter-spacing:1px;}");
    //确定衣服类型
    QString typeStr;
    switch(cloth.type()) {
    case Cloth::Top: typeStr = "上衣"; break;
    case Cloth::Under: typeStr = "下衣"; break;
    case Cloth::Dress: typeStr = "裙子"; break;
    case Cloth::Shoes: typeStr = "鞋子"; break;
    case Cloth::Accessory: typeStr = "配饰"; break;
    }

    labelType->setText("类型："+typeStr);
    labelStyle->setText("风格："+cloth.style());
    labelPattern->setText("图案："+cloth.pattern());
    labelMaterial->setText("材质："+cloth.material());
    labelThickness->setText("厚度："+cloth.thickness());
    labelSeason->setText("适宜季节："+cloth.season());
    labelPosition->setText("放置位置："+cloth.position());

    //TODO：加载图片

    //以上7个label描述特征
    total->addWidget(labelName);
    QHBoxLayout * imageLayout = new QHBoxLayout();
    labelSet->addWidget(labelType,0,0);
    labelSet->addWidget(labelStyle,0,1);
    labelSet->addWidget(labelPattern,1,0);
    labelSet->addWidget(labelMaterial,1,1);
    labelSet->addWidget(labelThickness,2,0);
    labelSet->addWidget(labelSeason,2,1);
    labelSet->addWidget(labelPosition,3,0);
    frame->setLayout(labelSet);
    frame->setFixedSize(QSize(240,180));
    imageLayout->addWidget(frame);
    QLabel *imageLabel = new QLabel;
    imageLabel->setPixmap(image);
    imageLabel->setScaledContents(true);
    imageLabel->setFixedSize(QSize(100,170));
    imageLayout->addWidget(imageLabel);
    total->addLayout(imageLayout);
    QHBoxLayout * buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(checkBox);
    buttonLayout->addWidget(cancel);
    total->addLayout(buttonLayout);
    setLayout(total);
    setObjectName("singleCloth");
    setStyleSheet(
        "QWidget#singleCloth{"
        "   border: 2px solid #aaaaaa;"
        "   border-radius: 5px;"
        "   border-color: rgb(0,170,255);"
        "   padding: 1px;"
        "}"
        );
    connect(checkBox, &QCheckBox::clicked,this,&showClothes::selectChange);
    connect(cancel,&QPushButton::clicked,this,&showClothes::deleteClothes);

}
void closet::showClothes::selectChange(){
    if(select==0) select=1;
    else select=0;
}
void closet::showClothes::deleteClothes(){
    Cloth::deleteCloth(parentCloset->userID,m_cloth);
    parentCloset->close();
    closet *mycloset = new closet(parentCloset->userID);
    mycloset->show();
}

void closet::selectClothes(){
    //选择今天衣服穿什么衣服
    QList<Cloth>outfit;
    for (int i=0;i<vectorTop.size();i++){
        if (vectorTop[i]->select==true){
            outfit.append(vectorTop[i]->m_cloth);
        }
    }
    for (int i=0;i<vectorUnder.size();i++){
        if (vectorUnder[i]->select==true){
            outfit.append(vectorUnder[i]->m_cloth);
        }
    }
    for (int i=0;i<vectorDress.size();i++){
        if (vectorDress[i]->select==true){
            outfit.append(vectorDress[i]->m_cloth);
        }
    }
    for (int i=0;i<vectorShoes.size();i++){
        if (vectorShoes[i]->select==true){
            outfit.append(vectorShoes[i]->m_cloth);
        }
    }
    for (int i=0;i<vectorAccessory.size();i++){
        if (vectorAccessory[i]->select==true){
            outfit.append(vectorAccessory[i]->m_cloth);
        }
    }
    Cloth::addDailyOutfit(userID,outfit);
    this->close();
    closet *mycloset = new closet(userID);
    mycloset->show();
}

void closet::addClothes(){
    //添加衣服
    this->close();
    newClothes *myNewClothes = new newClothes(userID);
    myNewClothes->show();
}
void closet::returnMainPage(){
    //添加衣服
    this->close();
    MainWindow *myMainWindow = new MainWindow(userID);
    myMainWindow->show();
}

closet::~closet()
{
    delete ui;
}

void closet::loadClothesFromSettings()
{
    QSettings settings("magicCloset", "UserContent");
    settings.beginGroup("id_"+QString::number(userID));

    m_clothes.clear();
    int size = settings.beginReadArray("clothes");
    for (int i = 0; i < size; ++i) {
        settings.setArrayIndex(i);

        Cloth cloth;
        cloth=cloth.loadFromSettings(settings);

        m_clothes.append(cloth);
    }
    settings.endArray();

    settings.endGroup();
}
void closet::saveClothesToSettings()
{
    QSettings settings("magicCloset", "UserContent");
    settings.beginGroup("id_"+QString::number(userID));

    settings.beginWriteArray("clothes");
    for (int i = 0; i < m_clothes.size(); ++i) {
        settings.setArrayIndex(i);
        m_clothes[i].saveToSettings(settings, i);
    }
    settings.endArray();

    settings.endGroup();
}

