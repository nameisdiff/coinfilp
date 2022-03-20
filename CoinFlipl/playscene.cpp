#include "playscene.h"
#include<QDebug>
#include<QAction>
#include<QMenuBar>
#include<QPainter>
#include"mypushbutton.h"
#include<QTimer>
#include<QLabel>
#include"mycoin.h"
#include"dataconfig.h"
#include<QPropertyAnimation>
//PlayScene::PlayScene(QWidget *parent)
//    : QMainWindow{parent}
//{

//}

PlayScene::PlayScene(int levelNum){
    //QString str=QString("进入了第%1关").arg(levelNum);
    //qDebug()<<str;
    this->levelIndex=levelNum;
    //初始化游戏场景
    this->setFixedSize(320,588);
    this->setWindowIcon(QPixmap(":/res/Coin0001.png"));
    this->setWindowTitle("翻金币场景");
    //设置菜单栏
    QMenuBar *bar=menuBar();
    setMenuBar(bar);
    QMenu *startMenu=bar -> addMenu("开始");
    QAction * quitAction=startMenu->addAction("退出");
    connect(quitAction,&QAction::triggered,[=](){
        this->close();
    });
    //back按钮
    MyPushButton *backBtn =new MyPushButton(":/res/BackButton.png",":/res/BackButtonSelected.png");
    backBtn->setParent(this);
    backBtn->move(this->width()-backBtn->width(),this->height()-backBtn->height());

    connect(backBtn,&MyPushButton::clicked,[=](){
        //qDebug()<<"点击返回按钮";
        //延时发送信号
        QTimer::singleShot(200,this,[=](){
            emit this->chooseSceneBack();
        });
    });
    //显示当前关卡数
    QLabel *label=new QLabel;
    label->setParent(this);
    QFont font;
    font.setFamily("华文新魏");
    font.setPointSize(20);
    label->setFont(font);
    QString str1 =QString("Level:%1").arg(this->levelIndex);
    label->setText(str1);
    label->setGeometry(30,this->height()-50,120,50);
    dataConfig config;
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
           this->gameArray[i][j]=config.mData[this->levelIndex][i][j];
        }
    }
    //胜利图片设置
    QLabel *winLabel= new QLabel;
    QPixmap tmpPix;
    tmpPix.load(":/res/LevelCompletedDialogBg.png");
    winLabel->setGeometry(0,0,tmpPix.width(),tmpPix.height());
    winLabel->setPixmap(tmpPix);
    winLabel->setParent(this);
    winLabel->move((this->width()-tmpPix.width())*0.5,-tmpPix.height());
    //显示金币背景
    for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
            QLabel * label=new QLabel;
            label->setGeometry(0,0,50,50);
            label->setPixmap(QPixmap(":/res/BoardNode.png"));
            label->setParent(this);
            label->move(57+i*50,200+j*50);
            //初始化金币
            QString str2;
            if(gameArray[i][j]==1){
                str2=":/res/Coin0001.png";
            }else{
                str2=":/res/Coin0008.png";
            }

            MyCoin *coin=new MyCoin(str2);
            coin->setParent(this);
            coin->move(59+i*50,204+j*50);
            coin->posX=i;
            coin->posY=j;
            coin->flag=gameArray[i][j];
            coinBtn[i][j]=coin;
            connect(coin,&MyCoin::clicked,[=](){
                coin->changeFlag();
                this->gameArray[i][j]=gameArray[i][j]==0?1:0;
                //翻转周围
                QTimer::singleShot(300,this,[=](){
                    if(coin->posX+1<4){
                        coinBtn[coin->posX+1][coin->posY]->changeFlag();
                        gameArray[coin->posX+1][coin->posY]=gameArray[coin->posX+1][coin->posY]==0?1:0;
                    }
                    if(coin->posX-1>-1){
                        coinBtn[coin->posX-1][coin->posY]->changeFlag();
                        gameArray[coin->posX-1][coin->posY]=gameArray[coin->posX-1][coin->posY]==0?1:0;
                    }
                    if(coin->posY-1>-1){
                        coinBtn[coin->posX][coin->posY-1]->changeFlag();
                        gameArray[coin->posX][coin->posY-1]=gameArray[coin->posX][coin->posY-1]==0?1:0;
                    }
                    if(coin->posY+1<4){
                        coinBtn[coin->posX][coin->posY+1]->changeFlag();
                        gameArray[coin->posX][coin->posY+1]=gameArray[coin->posX][coin->posY+1]==0?1:0;
                    }
                });
                QTimer::singleShot(500,this,[=](){
                    this->isWin =true;
                    for(int n=0;n<4;n++){
                        for(int m=0;m<4;m++){
                            if(coinBtn[n][m]->flag == false){
                                //qDebug()<<n<<m;
                                this->isWin=false;
                                break;
                            }
                        }
                    }
                    if(this->isWin==true){
                        qDebug()<<"胜利";
                        for(int p=0;p<4;p++){
                            for(int q=0;q<4;q++){
                                coinBtn[p][q]->isWin=true;
                            }
                        }
                        //胜利动画
                        QPropertyAnimation *animation =new QPropertyAnimation(winLabel,"geometry");
                        animation->setDuration(1000);
                        animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
                        animation->setEndValue(QRect(winLabel->x(),winLabel->y()+114,winLabel->width(),winLabel->height()));
                        animation->setEasingCurve(QEasingCurve::OutBounce);
                        animation->start();
                    }

                });

            });
        }
    }


}
void PlayScene::paintEvent(QPaintEvent *){
    //创建背景
    QPainter painter(this);
    QPixmap pix;
    pix.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pix);
    //创建标题
    pix.load(":/res/Title.png");
    pix=pix.scaled(pix.width()*0.5,pix.height()*0.5);
    painter.drawPixmap(10,30,pix.width(),pix.height(),pix);


}
