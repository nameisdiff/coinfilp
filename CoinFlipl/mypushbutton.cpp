#include "mypushbutton.h"
#include<QDebug>
#include <QPropertyAnimation>
#include <QRect>
//MyPushButton::MyPushButton(QPushButton *parent)
//    : QWidget{parent}
//{

//}
MyPushButton::MyPushButton(QString normalImg,QString pressImg){
    this->normalImgPath=normalImg;
    this->pressImgPath=pressImg;
    QPixmap pix;
    bool ret=pix.load(normalImg);
    if(!ret){
        qDebug()<<"图片加载失败";
        return;
    }
    //设置按钮大小
    this->setFixedSize(pix.width(),pix.height());

    this->setStyleSheet("QPushButton{border:0px}");

    this->setIcon(pix);
    this->setIconSize(QSize(pix.width(),pix.height()));
}
void MyPushButton::zoom1(){
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry");

    animation->setDuration(300);

    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));

    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));

    animation->setEasingCurve(QEasingCurve::OutBounce);

    animation->start();

}
void MyPushButton::zoom2(){
    QPropertyAnimation *animation = new QPropertyAnimation(this,"geometry");

    animation->setDuration(300);

    animation->setStartValue(QRect(this->x(),this->y()-10,this->width(),this->height()));

    animation->setEndValue(QRect(this->x(),this->y(),this->width(),this->height()));

    animation->setEasingCurve(QEasingCurve::OutBounce);

    animation->start();
}
