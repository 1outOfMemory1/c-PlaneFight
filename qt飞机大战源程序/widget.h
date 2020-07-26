#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTimer>
#include "config.h"
#include "map.h"
#include "plane.h"
#include <QKeyEvent>
#include "bullet.h"
#include "enemyPlane.h"
#include "bomb.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
private:
    Ui::Widget *ui;
    QTimer timer;  //设置一个定时器
    QTimer planeInTimer;  //飞机入场的时候的定时器
    QTimer keyBoradTimer;
    Map map;
    Plane myPlane;
    int enemyPlaneFrequencyRecord;   //因为飞机只有一架 但是敌机却有很多架  子弹属于飞机的一部分 这个record只能放在主窗口中
    EnemyPlane enmeyPlaneArray[ENEMYPLANE_NUM];   //构造规定的敌机数组
    Bomb bombs[BOMB_NUM];
//    Bullet planeBullet;

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
    void initGame();  //初始化游戏函数

    void playGame();   //启动游戏

    void keyPressEvent(QKeyEvent *event) override;   //键盘的按下检测
    void keyReleaseEvent(QKeyEvent *event) override;  //键盘的释放检测

    void updatePosition(); //更新游戏中元素的坐标


    void enemyToMainWindow();

    void paintEvent(QPaintEvent *event) override ; //绘制到屏幕上
    void collisionDetection();  //碰撞检测  针对敌机的碰撞检测




};
#endif // WIDGET_H
