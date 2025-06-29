#include "showrecommend.h"
#include "ui_showrecommend.h"
#include "recommend_algorithm.h"
#include "Cloth.h"
#include <QLayout>
#include <QPixmap>
#include "mainwindow.h"


showRecommend::showRecommend(int _userID,QString _occasion,
                             QString _season,QString _weather,int _temperature,
                             QColor _color, QWidget *parent)
    : userID(_userID),occasion(_occasion),season(_season),weather(_weather),
    temperature(_temperature),color(_color),QDialog(parent), ui(new Ui::showRecommend)
{
    ui->setupUi(this);
    scrollArea->setWidgetResizable(true);
    resize(500,600);
    QList<Cloth> recommend_clothes = recommendOutfit(userID,occasion,season,weather,temperature,color);
    for(const auto & item: recommend_clothes){
        if(item.type()==Cloth::Top){
            vectorTop.append(new showClothes(userID, item));
        }
        if(item.type()==Cloth::Under){
            vectorUnder.append(new showClothes(userID, item));
        }
        if(item.type()==Cloth::Dress){
            vectorDress.append(new showClothes(userID, item));
        }
        if(item.type()==Cloth::Shoes){
            vectorShoes.append(new showClothes(userID, item));
        }
        if(item.type()==Cloth::Accessory){
            vectorAccessory.append(new showClothes(userID, item));
        }
    }
    labelTop->setStyleSheet("QLabel{font-size:18px;font-family:黑体;font-weight:bold;letter-spacing:1px;}");
    labelUnder->setStyleSheet("QLabel{font-size:18px;font-family:黑体;font-weight:bold;letter-spacing:1px;}");
    labelDress->setStyleSheet("QLabel{font-size:18px;font-family:黑体;font-weight:bold;letter-spacing:1px;}");
    labelShoes->setStyleSheet("QLabel{font-size:18px;font-family:黑体;font-weight:bold;letter-spacing:1px;}");

    layoutTop->setSpacing(15);
    layoutUnder->setSpacing(15);
    layoutDress->setSpacing(15);
    layoutShoes->setSpacing(15);

    layoutTop->setContentsMargins(2,20,2,20);
    layoutUnder->setContentsMargins(2,20,2,20);
    layoutDress->setContentsMargins(2,20,2,20);
    layoutShoes->setContentsMargins(2,20,2,20);

    layoutTop->addWidget(labelTop,0,0,1,2);
    layoutUnder->addWidget(labelUnder,0,0,1,2);
    layoutDress->addWidget(labelDress,0,0,1,2);
    layoutShoes->addWidget(labelShoes,0,0,1,2);

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

    if(vectorTop.size() != 0){
        layoutTop->addWidget(vectorTop[0],2,0);
        layoutUnder->addWidget(vectorUnder[0],2,0);
        scrollLayout->addLayout(layoutTop);
        scrollLayout->addLayout(layoutUnder);
    }
    else{
        layoutDress->addWidget(vectorDress[0],2,0);
        scrollLayout->addLayout(layoutDress);
    }
    if(vectorShoes.size()!=0){
        layoutShoes->addWidget(vectorShoes[0],2,0);
        scrollLayout->addLayout(layoutShoes);
    }
    // for (int i=0;i<vectorTop.size();i++)
    //     layoutTop->addWidget(vectorTop[i],i/2+1,i%2);
    // for (int i=0;i<vectorUnder.size();i++)
    //     layoutUnder->addWidget(vectorUnder[i],i/2+1,i%2);
    // for (int i=0;i<vectorDress.size();i++)
    //     layoutDress->addWidget(vectorDress[i],i/2+1,i%2);
    // for (int i=0;i<vectorShoes.size();i++)
    //     layoutShoes->addWidget(vectorShoes[i],i/2+1,i%2);

    scrollArea->setWidget(scrollWidget);
    scrollArea->setWidgetResizable(true);
    //主页面加入

    mainLayout->addLayout(ui->Layout1);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(30,90,30,20);

    mainLayout->addWidget(scrollArea);
    setLayout(mainLayout);

    mainLayout->addWidget(returnButton);
    connect(returnButton,&QPushButton::clicked,this,&showRecommend::returnMainPage);

    setWindowTitle("码上穿衣-穿搭推荐");
    QIcon* icon=new QIcon(":/images/icon.png");
    setWindowIcon(*icon);
}

showRecommend::~showRecommend()
{
    delete ui;
}
showRecommend::showClothes::showClothes(int id,Cloth mycloth){
    //这个是衣橱里每个衣服展示的类
    //*参数需要再加一个cloth类
    userID=id;
    QVBoxLayout *total = new QVBoxLayout();//三
    QPixmap image(mycloth.path());
    if(image.isNull()) {
        qDebug() << "Failed to load image";
    }

    labelName->setText(mycloth.name());
    labelName->setStyleSheet("QLabel{font-size:16px;font-family:宋体;font-weight:bold;letter-spacing:1px;}");
    QString typeStr;
    switch(mycloth.type()) {
    case Cloth::Top: typeStr = "上衣"; break;
    case Cloth::Under: typeStr = "下衣"; break;
    case Cloth::Dress: typeStr = "裙子"; break;
    case Cloth::Shoes: typeStr = "鞋子"; break;
    case Cloth::Accessory: typeStr = "配饰"; break;
    }

    labelType->setText("类型："+typeStr);
    QString style=mycloth.style();
    labelStyle->setText("风格："+style);//*
    QString pattern=mycloth.pattern();
    labelPattern->setText("图案："+pattern);//*
    QString material=mycloth.material();
    labelMaterial->setText("材质："+material);//*
    QString thickness=mycloth.thickness();
    labelThickness->setText("厚度："+thickness);//*
    QString season=mycloth.season();
    labelSeason->setText("季节："+season);//*
    QString position=mycloth.position();
    labelPosition->setText("位置："+position);//*
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
    setLayout(total);
}

void showRecommend::returnMainPage(){
    this->close();
    MainWindow *myMainWindow = new MainWindow(userID);
    myMainWindow->show();
}
