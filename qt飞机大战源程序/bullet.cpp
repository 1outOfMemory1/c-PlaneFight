#include "bullet.h"
#include <QBitmap>

Bullet::Bullet()
{
     //加载子弹的资源
    planeBulletPic.load(BULLET_PATH);
    QBitmap mask =  planeBulletPic.createMaskFromColor(QColor(0,0,0),Qt::MaskInColor);  //设计一个遮罩 把黑色部分弄没
    planeBulletPic.setMask(mask);   //图片添加遮罩

    //设置子弹的速度
    bulletSpeed = BULLET_SPEED;

    //默认设置子弹是空闲的
    setFree(true);



    //子弹边框
    bulletRect.setWidth(BULLET_WIDTH);
    bulletRect.setHeight(BULLET_HEIGHT);
    bulletRect.moveTo(getX()  + 0.5*PLANE_WIDTH - 0.5* BULLET_WIDTH,getY());


}


void Bullet::updatePosition()
{



    if(isFree)
        return;

    setXY(getX(),getY()-bulletSpeed);
    bulletRect.moveTo(getX(),getY()-bulletSpeed);
    //子弹如果超出屏幕就进行回收
    if(getY() <= - BULLET_HEIGHT){
        isFree =  true;
    }

}

void Bullet::setXY(int xx, int yy)
{
  x = xx;
  y = yy;
}

int Bullet::getX()
{
    return x  ;
}

int Bullet::getY()
{
    return y;
}

void Bullet::setFree(bool b)
{
    isFree = b;
}

bool Bullet::isFreeOrNot()
{
    return  isFree;
}

QPixmap &Bullet::getBulletPic()
{
    return planeBulletPic;
}

