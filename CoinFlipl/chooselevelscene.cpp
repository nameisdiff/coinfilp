#include "chooselevelscene.h"
#include<QMenuBar>
#include<QPainter>
#include "mypushbutton.h"
#include"mainscene.h"
#include<QTimer>
#include<QLabel>
ChooseLevelScene::ChooseLevelScene(QWidget *parent)
    : QMainWindow{parent}
{
    this->setFixedSize(320,588);

    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));

    this->setWindowTitle("选择关卡场景");

    QMenuBar *bar=menuBar();
    setMenuBar(bar);
    QMenu *startMenu=bar -> addMenu("开始");
    QAction * quitAction=startMenu->addAction("退出");

    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });

    //返回按钮
    MyPushButton *backBtn =new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");

    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());
    //点击back按钮返回信号给主场景
    connect(backBtn,&MyPushButton::clicked,[=](){
        //qDebug()<<"点击返回按钮";
        //延时发送信号

        QTimer::singleShot(310,this,[=](){
            emit this->chooseSceneBack();
        });
    });

    for(int i=0;i<20;i++){
        MyPushButton *menuBtn =new MyPushButton(":/res/LevelIcon.png");
        //label->setAlignment(Qt::WA_TransparentForMouseEvents);穿透鼠标事件
        //设置关卡按钮
        menuBtn->setParent(this);
        menuBtn->move(25+i%4*70,130+i/4*70);
        connect(menuBtn,&MyPushButton::clicked,[=](){
            //qDebug()<<"你点击了关卡"<<i+1;           
            this->hide();
            play=new PlayScene(i+1);
            play->setGeometry(this->geometry());
            play->show();
            connect(play,&PlayScene::chooseSceneBack,[=](){
                this->show();
                delete play;
                play=NULL;
            });
        });
        //设置关卡数字
        QLabel *label=new QLabel;
        label->setParent(this);
        label->setFixedSize(menuBtn->width(),menuBtn->height());
        label->setText(QString::number(i+1));
        label->move(25+i%4*70,130+i/4*70);
        label->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        label->setAttribute(Qt::WA_TransparentForMouseEvents);
    }
}
void ChooseLevelScene::paintEvent(QPaintEvent *){
    //创建背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //创建标题
    pix.load(":/res/Title.png");
    painter.drawPixmap((this->width()-pix.width())*0.5,30,pix.width(),pix.height(),pix);

}
