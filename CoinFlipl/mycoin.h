#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>
#include <QTimer>
class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    //explicit MyCoin(QWidget *parent = nullptr);
    MyCoin(QString btnImg);


    //金币属性
    int posX;
    int posY;
    bool flag;//正反

    //实现金币翻转动画
    void changeFlag();
    QTimer *timer1;
    QTimer *timer2;
    int min=1;
    int max=8;
    //执行动画标志
    bool isAnimation=false;

    void mousePressEvent(QMouseEvent *e);

    bool isWin=false;
signals:

};

#endif // MYCOIN_H
