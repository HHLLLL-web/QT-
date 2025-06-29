#include "showhistory.h"
#include "ui_showhistory.h"
#include "mainwindow.h"
showHistory::showHistory(int id,QDate d,QWidget *parent)
    : userID(id),date(d),QDialog(parent)
    , ui(new Ui::showHistory)
{
    ui->setupUi(this);
    totalClothes = Cloth::getDailyOutfits(userID, date);
    scrollArea->setWidgetResizable(true);
    resize(900,600);

    // 根据衣物数据创建显示项
    QVector<QGridLayout*> gridLayouts;
    for(int i=0;i<totalClothes.size();i++) {
        const QList<Cloth> &group=totalClothes[i];
        QGridLayout *layoutTop = new QGridLayout();
        gridLayouts.append(layoutTop);
        QString str = QString::number(i+1);
        QLabel * labelTop = new QLabel("第"+str+"套穿搭");
        labelTop->setStyleSheet("QLabel{font-size:18px;font-family:黑体;font-weight:bold;letter-spacing:1px;}");
        layoutTop->setSpacing(15);
        layoutTop->setContentsMargins(2,20,2,20);
        layoutTop->addWidget(labelTop,0,0,1,2);

        QFrame *hLine1 = new QFrame;
        hLine1->setFrameShape(QFrame::HLine);
        layoutTop->addWidget(hLine1,1,0,1,2);
        int j=0;
        for(const Cloth &cloth : group) {
            showClothes *item = new showClothes(userID, cloth);
            layoutTop->addWidget(item,j/2+2,j%2);
            j++;
        }
        scrollLayout->addLayout(layoutTop);
    }
    scrollArea->setWidget(scrollWidget);
    scrollArea->setWidgetResizable(true);
    QLabel * title = new QLabel("穿搭日历");
    title->setStyleSheet("QLabel{font-size:24px;font-family:微软雅黑;font-weight:bold;letter-spacing:1px;}");
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(30,20,30,20);
    mainLayout->addWidget(title);
    mainLayout->addWidget(scrollArea);
    QHBoxLayout * buttonLayoutTotal = new QHBoxLayout();
    buttonLayoutTotal->addWidget(returnButton);
    mainLayout->addLayout(buttonLayoutTotal);
    setLayout(mainLayout);
    connect(returnButton,&QPushButton::clicked,this,&showHistory::returnMainPage);

    setWindowTitle("码上穿衣-穿搭日历");
    QIcon* icon=new QIcon(":/images/icon.png");
    setWindowIcon(*icon);
}

showHistory::~showHistory()
{
    delete ui;
}

showHistory::showClothes::showClothes(int id,Cloth cloth):userID(id){
    mycloth=cloth;
    QVBoxLayout *total = new QVBoxLayout();//三
    QPixmap image(cloth.path());
    if(image.isNull()) {
        qDebug() << "Failed to load image";
    }

    labelName->setText(mycloth.name());
    labelName->setStyleSheet("QLabel{font-size:16px;font-family:宋体;font-weight:bold;letter-spacing:1px;}");
    //确定衣服类型
    QString typeStr;
    switch(mycloth.type()) {
    case Cloth::Top: typeStr = "上衣"; break;
    case Cloth::Under: typeStr = "下衣"; break;
    case Cloth::Dress: typeStr = "裙子"; break;
    case Cloth::Shoes: typeStr = "鞋子"; break;
    case Cloth::Accessory: typeStr = "配饰"; break;
    }

    labelType->setText("类型："+typeStr);
    labelStyle->setText("风格："+mycloth.style());
    labelPattern->setText("图案："+mycloth.pattern());
    labelMaterial->setText("材质："+mycloth.material());
    labelThickness->setText("厚度："+mycloth.thickness());
    labelSeason->setText("适宜季节："+mycloth.season());
    labelPosition->setText("放置位置："+mycloth.position());

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
}
void showHistory::returnMainPage(){
    //添加衣服
    this->close();
    MainWindow *myMainWindow = new MainWindow(userID);
    myMainWindow->show();
}
