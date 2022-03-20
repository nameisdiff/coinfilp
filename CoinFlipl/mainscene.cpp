#include "mainscene.h"
#include "ui_mainscene.h"
#include<QPainter>
#include "mypushbutton.h"
#include<QDebug>
#include<QTimer>

MainScene::MainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainScene)
{
    ui->setupUi(this);
    //主场景设置
    setFixedSize(320,588);
    setWindowIcon(QIcon(":/res/Coin0001.png"));
    setWindowTitle("翻金币的主场景");

    connect(ui->actionexit,&QAction::triggered,[=](){
        this->close();
    });

    //开始按钮
    MyPushButton* startBtn=new MyPushButton(":/res/MenuSceneStartButton.png");
    startBtn->setParent(this);
    startBtn->move(this->width()*0.5-startBtn->width()*0.5,this->height()*0.7);

    chooseScene =new ChooseLevelScene;
    connect(chooseScene,&ChooseLevelScene::chooseSceneBack,[=](){

        chooseScene->hide();
        this->show();
    });


    connect(startBtn,&MyPushButton::clicked,[=](){
        //qDebug()<<"鼠标点击了按钮";
        //按钮弹起动画
        startBtn->zoom1();
        startBtn->zoom2();
        //延时
        QTimer::singleShot(310,this,[=](){
            //隐藏主场景

            this->hide();
            //显示关卡选择场景

            chooseScene->setGeometry(this->geometry());
            chooseScene->show();
        });

    });
}

MainScene::~MainScene()
{
    delete ui;
}
void MainScene::paintEvent(QPaintEvent*){
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    pix.load(":/res/Title.png");
    pix=pix.scaled(pix.width()*0.7,pix.height()*0.7);
    painter.drawPixmap(10,30,pix);
}
