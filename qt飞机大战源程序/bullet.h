#ifndef BULLET_H
#define BULLET_H
#include "config.h"
#include <QPixmap>
#include <QRect>
#include <QObject>


class Bullet
{
private:
    QPixmap planeBulletPic;  //子弹的资源位置
    int x,y;   //子弹的位置

    bool isFree; //用于回收子弹
    int bulletSpeed;
public:
    QRect bulletRect;  //子弹的边框  用于碰撞检测
    Bullet();
    void updatePosition();
    void setXY(int xx,int yy);
    int getX();
    int getY();
    void setFree(bool b);
    bool isFreeOrNot();
    QPixmap & getBulletPic();


};

#endif // BULLET_H
