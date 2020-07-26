#ifndef ENEMY_H
#define ENEMY_H
#include "config.h"
#include "bullet.h"
#include <QRect>
#include <QPixmap>


class EnemyPlane  //敌机
{
private:
    int x,y;  //敌机的位置
    QPixmap enemyPlanePic;  //敌机的图片
    int initPosition;    //初始的飞机位置  从上从下两种选择  0是上 1是下
    int speedType;      //0是低速飞机   1是高速飞机
    int speed;

    bool isFree;
public:
    EnemyPlane();
    void EnemyPlaneInit();
    QRect planeRect;   //飞机看不见的框 用于碰撞检测 和 子弹射中检测
    //调整敌机位置
    void setXY(int xx,int yy);
    QRect enemyPlaneRect;
    //获取敌机当前位置
    int getX();
    int getY();


    int getInitPosition();

    bool isFreeOrNot();
    void setFree(bool b);

    //返回图片
    QPixmap & getEnemyPlanePic();

    //更新位置函数
    void updatePosition();
    //发射子弹调用函数
    void shoot();
};

#endif // ENEMY_H
