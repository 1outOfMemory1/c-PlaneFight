#include "enemyPlane.h"
#include <ctime>
#include <cstdlib>

EnemyPlane::EnemyPlane()
{




}

void EnemyPlane::EnemyPlaneInit()
{
    srand((unsigned int)time(0));  // 产生随机种子  把0换成NULL也行
    initPosition = rand()%2;  //随机产生0和1 0代表敌机从上方进入 1 表示敌机从下方进入

    if(initPosition) //1 表示敌机从下方进入
        enemyPlanePic.load(ENEMY_FROM_DOWN_PATH);
    else
        enemyPlanePic.load(ENEMY_FROM_UP_PATH);

    speedType = rand()%2;   //0是低速飞机   1是高速飞机
    if(speedType)  // 1是高速飞机
        speed = SPEED_OF_FASTER_ENEMYPLANE;
    else
        speed = SPEED_OF_SLOWER_ENEMYPLANE;


    //敌机的矩形框(碰撞检测)
    enemyPlaneRect.setWidth(enemyPlanePic.width());
    enemyPlaneRect.setHeight(enemyPlanePic.height());
    enemyPlaneRect.moveTo(getX(),getY());
}

void EnemyPlane::setXY(int xx, int yy)
{
    x = xx;
    y = yy;
}

int EnemyPlane::getX()
{
    return  x;
}

int EnemyPlane::getY()
{
    return y;
}

int EnemyPlane::getInitPosition()
{
    return initPosition;
}

bool EnemyPlane::isFreeOrNot()
{
    return isFree;
}

void EnemyPlane::setFree(bool b)
{
    isFree = b;
}

QPixmap &EnemyPlane::getEnemyPlanePic()
{
    return enemyPlanePic;
}

void EnemyPlane::updatePosition()
{
    //如果超出屏幕外 那么重置
    if(getY() <=0 || getY()>=WINDOW_HEIGHT){
        isFree = true;
    }

    //空闲的敌机不计算位置
    if(isFree)
        return;

    if(initPosition)  ////1 表示敌机从下方进入
        setXY(getX(),getY() - speed);
    else
        setXY(getX(),getY() + speed);
    enemyPlaneRect.moveTo(getX(),getY());
}
