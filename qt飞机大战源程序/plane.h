#ifndef PLANE_H
#define PLANE_H
#include "config.h"
#include "bullet.h"
#include <QPixmap>
#include <QRect>
#include <QWidget>
#include <QTimer>
#include <QDebug>
#include <QBitmap>


class Plane  : public QWidget   //自己的飞机
{
    Q_OBJECT
private:
    int x,y;  //飞机的位置
    QPixmap planePic;  //飞机的图片
    int record;
public:
    Bullet clips[BULLET_CAPACITY];
    Plane();
   QRect planeRect;   //飞机看不见的框 用于碰撞检测 和 子弹射中检测
    //调整飞机位置
    void setXY(int xx,int yy);

    //获取飞机当前位置
    int getX();
    int getY();

    QPixmap & getPlanePic();

    void up();
    void down();
    void left();
    void right();

    //发射子弹调用函数
    void shoot();
};

#endif // PLANE_H
