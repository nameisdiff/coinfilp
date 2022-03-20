#include "mycoin.h"
#include<QDebug>
#include<QTimer>
//MyCoin::MyCoin(QWidget *parent)
//    : QWidget{parent}
//{

//}
MyCoin::MyCoin(QString btnImg){
    QPixmap pix;
    bool ret =pix.load(btnImg);
    if(!ret){
        QString str=QString("图片%1加载失败").arg(btnImg);
        qDebug()<<str;
    }
    this->setFixedSize(pix.width(),pix.height());
    this->setStyleSheet("QPushButton{border:0px}");
    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));

    timer1 = new QTimer(this);
    timer2 = new QTimer(this);
    //监听timer1，timer2实现金币翻转
    connect(timer1,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str1=QString(":/res/Coin000%1.png").arg(this->min++);
        pix.load(str1);

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        if(this->min>this->max){
            this->min=1;
            isAnimation=0;
            timer1->stop();
        }
    });
    connect(timer2,&QTimer::timeout,[=](){
        QPixmap pix;
        QString str1=QString(":/res/Coin000%1.png").arg(this->max--);
        pix.load(str1);

        this->setFixedSize(pix.width(),pix.height());
        this->setStyleSheet("QPushButton{border:0px}");
        this->setIcon(pix);
        this->setIconSize(QSize(pix.width(),pix.height()));
        if(this->min>this->max){
            this->max=8;
            isAnimation=0;
            timer2->stop();
        }
    });
}


void MyCoin::changeFlag(){
    if(this->flag){
        //发送翻转信号
        timer1 ->start(30);
        isAnimation=1;
        this->flag=0;
    }else{
        //发送翻转信号
        timer2 ->start(30);
        isAnimation=1;
        this->flag=1;
    }
}
void MyCoin::mousePressEvent(QMouseEvent *e){
    if(this->isAnimation||this->isWin==true){
        return;
    }else{
        QPushButton::mousePressEvent(e);
    }
}
