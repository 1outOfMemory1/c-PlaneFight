#include "widget.h"
#include "ui_widget.h"
#include "config.h"
#include "enemyPlane.h"
#include <QIcon>
#include <QImage>
#include <QString>
#include <QPainter>
#include <QKeyEvent>
#include <QDebug>

Widget::Widget(QWidget *parent)   //构造函数
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    initGame();   //调用初始化游戏的函数
    playGame();   //开始游戏


}

Widget::~Widget()   //析构函数
{
    delete ui;
}


void Widget::initGame()   //游戏初始化函数
{
    setWindowTitle(GAME_TITLE);  //设置窗口标题
    setFixedSize(WINDOW_WIDTH,WINDOW_HEIGHT);  //设置窗口的宽和高
    setWindowIcon(QIcon(":/res/favicon.ico"));  //加载图标

    timer.setInterval(GAME_REFRESH_RATE);  //控制背景图运动的定时器
    planeInTimer.setInterval(30);//设置飞机的一个进场效果 的定时器
    keyBoradTimer.setInterval(10);
    enemyPlaneFrequencyRecord = ENEMYPLANE_NUM_FREQUENCY;   //敌机此时的record为 ENEMYPLANE_NUM_FREQUENCY 也就是立刻会出现敌机

}

void Widget::playGame()
{
    timer.start(); //启动定时器
    planeInTimer.start();  // 启动进场定时器
    keyBoradTimer.start();


    //设置飞机的一个进场效果
    connect(&planeInTimer,&QTimer::timeout,[&](){
        if(WINDOW_HEIGHT -  2 * PLANE_HEIGHT >= myPlane.getY() ){  //飞机距离底部一段距离的时候停下
            planeInTimer.stop();
        }
        myPlane.setXY(myPlane.getX(),myPlane.getY() - 5);
        myPlane.planeRect.moveTo(myPlane.getX() ,myPlane.getY() -5);
    }); //监听定时器的发送信号  使用信号槽来进行连接


    connect(&timer,&QTimer::timeout,[=](){

        enemyToMainWindow(); //敌机出场
        updatePosition(); //更新游戏中所有元素的坐标
        update();   //绘制到屏幕中
        collisionDetection();//检测碰撞

    }); //监听定时器的发送信号  使用信号槽来进行连接

}

void Widget::keyPressEvent(QKeyEvent *event)
{
    //检测上下左右键 或者是 wasd键是否被按下 如果按下 就执行移动选项
    switch (event->key()) {
            case Qt::Key_A:
            case Qt::Key_Left:
                connect(&keyBoradTimer,&QTimer::timeout, &myPlane ,&Plane::left); //监听定时器的发送信号  使用信号槽来进行连接
                break;
            case Qt::Key_W:
            case Qt::Key_Up:
                connect(&keyBoradTimer,&QTimer::timeout, &myPlane ,&Plane::up); //监听定时器的发送信号  使用信号槽来进行连接
                break;
            case Qt::Key_D:
            case Qt::Key_Right:
                connect(&keyBoradTimer,&QTimer::timeout, &myPlane ,&Plane::right ); //监听定时器的发送信号  使用信号槽来进行连接
                break;
            case Qt::Key_S:
            case Qt::Key_Down:
                connect(&keyBoradTimer,&QTimer::timeout,  &myPlane ,&Plane::down); //监听定时器的发送信号  使用信号槽来进行连接
                break;
    }
}

void Widget::keyReleaseEvent(QKeyEvent *event)
{
    //检测上下左右键 或者是 wasd键是否被松开 如果松开 就执行断开连接操作
    switch (event->key()) {
            case Qt::Key_A:
            case Qt::Key_Left:
                disconnect(&keyBoradTimer,&QTimer::timeout, &myPlane ,&Plane::left); //监听定时器的发送信号  使用信号槽来进行连接
                break;
            case Qt::Key_W:
            case Qt::Key_Up:
                disconnect(&keyBoradTimer,&QTimer::timeout, &myPlane ,&Plane::up); //监听定时器的发送信号  使用信号槽来进行连接
                break;
            case Qt::Key_D:
            case Qt::Key_Right:
                disconnect(&keyBoradTimer,&QTimer::timeout, &myPlane ,&Plane::right ); //监听定时器的发送信号  使用信号槽来进行连接
                break;
            case Qt::Key_S:
            case Qt::Key_Down:
                disconnect(&keyBoradTimer,&QTimer::timeout,  &myPlane ,&Plane::down); //监听定时器的发送信号  使用信号槽来进行连接
                break;
    }
}

void Widget::updatePosition()
{
    // 检测是否出现越界的情况 如果出现 立即矫正
    if(myPlane.getX() <= 0 )
        myPlane.setXY(0,myPlane.getY());
    if(myPlane.getY() <= 0 )
        myPlane.setXY(myPlane.getX(),0);
    if(myPlane.getX() >= WINDOW_WIDTH -PLANE_WIDTH )
        myPlane.setXY(WINDOW_WIDTH -PLANE_WIDTH ,myPlane.getY());
    if(myPlane.getY() >= WINDOW_HEIGHT -PLANE_HEIGHT )
        myPlane.setXY(myPlane.getX(), WINDOW_HEIGHT -PLANE_HEIGHT);
    map.mapPosition(); //更新地图的坐标


    //敌机出场
    for(int i=0;i<ENEMYPLANE_NUM;i++){
        if(enmeyPlaneArray[i].isFreeOrNot() == false) {// 说明非空闲
           enmeyPlaneArray[i].updatePosition();
        }
    }


    //发射子弹
    myPlane.shoot();

    //计算所有非空闲子弹的当前坐标
    for(int i=0;i<BULLET_CAPACITY;i++){
        //如果非空闲 , 计算发射位置
        if(myPlane.clips[i] .isFreeOrNot() == false){
            myPlane.clips[i].updatePosition();
        }
    }


    //爆炸效果
    for(int i=0;i<BOMB_NUM ;i++){
        if(bombs[i].isFreeOrnot() == false){
            bombs[i].updateInfo();
        }
    }

//    planeBullet.setFree( false);
//    planeBullet.updatePosition();

}

void Widget::enemyToMainWindow()
{
    enemyPlaneFrequencyRecord++;
    if(enemyPlaneFrequencyRecord < ENEMYPLANE_NUM_FREQUENCY)
        return;

    enemyPlaneFrequencyRecord = 0;
    for(int i=0;i<ENEMYPLANE_NUM ;i++){
        EnemyPlane *enemy = &enmeyPlaneArray[i] ;
        //如果是空闲的敌机  那就出场
        if(enemy->isFreeOrNot()){
            enemy->setFree(false);

            //坐标
            if(enemy->getInitPosition())  //1 是从底部出发的飞机
              {
                enemy->EnemyPlaneInit();
               enemy->setXY(rand()%(WINDOW_WIDTH -  enemy->enemyPlaneRect.width()),WINDOW_HEIGHT-1);}
            else
            {
                enemy->EnemyPlaneInit();
               enemy->setXY(rand()%(WINDOW_WIDTH -  enemy->enemyPlaneRect.width()),1);
            }
            break;
        }

    }
}

void Widget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);


    //两张背景图片 绘制
    painter.drawPixmap(0,map.getMap1YPosition(1),map.getMapById(1));  //绘制第一张图
    painter.drawPixmap(0,map.getMap1YPosition(2),map.getMapById(2));  //绘制第二张图

    painter.drawPixmap(myPlane.getX(),myPlane.getY(), myPlane.getPlanePic());  //绘制自己的飞机图


    //绘制所有非空闲的子弹
    for(int i=0;i<BULLET_CAPACITY;i++){
        //如果非空闲 , 画出来
        if(myPlane.clips[i] .isFreeOrNot() == false){
           painter.drawPixmap(myPlane.clips[i].getX()
                              ,myPlane.clips[i].getY()
                              ,myPlane.clips[i].getBulletPic()) ;
//           painter.setPen(QColor(255,255,255));
//           painter.drawRect(myPlane.clips[i].bulletRect);


        }

    }
    //绘制每个非空闲的敌机r
    for(int i=0;i<ENEMYPLANE_NUM;i++){
        //如果非空闲 , 画出来
        if(enmeyPlaneArray[i].isFreeOrNot() == false){
           painter.drawPixmap(enmeyPlaneArray[i].getX()
                              ,enmeyPlaneArray[i].getY()
                              ,enmeyPlaneArray[i].getEnemyPlanePic()) ;
//           painter.setPen(QColor(255,255,255));
//           painter.drawRect(enmeyPlaneArray[i].enemyPlaneRect);
        }


    //绘制爆炸的图
    for(int i=0;i<BOMB_NUM;i++) {
        if(bombs[i].isFreeOrnot() == false)
            painter.drawPixmap(bombs[i].getX(),bombs[i].getY(),bombs[i].pix_arr[bombs[i].getIndex()]);

    }

    }

//    painter.drawPixmap(planeBullet.getX(),planeBullet.getY(), planeBullet.getBulletPic());  //绘制子弹

}

void Widget::collisionDetection()  //碰撞检测
{

    for(int i=0;i<BULLET_CAPACITY;i++){  //遍历所有子弹

        if(myPlane.clips[i].isFreeOrNot())  //子弹当前空闲
            continue;

        for(int j =0;j<ENEMYPLANE_NUM;j++){
            if(enmeyPlaneArray[j].isFreeOrNot() )  //当前的敌机空闲
                continue;
            if(myPlane.clips[i].bulletRect.intersects(enmeyPlaneArray[j].enemyPlaneRect)){
                myPlane.clips[i].setFree(true);
                enmeyPlaneArray[j].setFree(true);


                //播放爆炸的效果
                for(int k =0;k<BOMB_NUM;k++){
                    if(bombs[k].isFreeOrnot() ) //空闲状态
                    {
                        //空闲的爆炸
                       bombs[k].setFree(false);
                       //更新爆炸坐标
                       bombs[k].setXY(enmeyPlaneArray[j].getX(),enmeyPlaneArray[j].getY());
                       break;
                    }
                }
            }
        }

    }
}

