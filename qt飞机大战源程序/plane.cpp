#include "plane.h"


Plane::Plane()
{
    //加载飞机的图片
    planePic.load(PLANEPIC_PATH);
    QBitmap mask =  planePic.createMaskFromColor(QColor(0,0,0),Qt::MaskInColor);  //设计一个遮罩 把黑色部分弄没
    planePic.setMask(mask);   //图片添加遮罩


    //初始化飞机的位置
    setXY((WINDOW_WIDTH - PLANE_WIDTH) *0.5 , WINDOW_HEIGHT + PLANE_HEIGHT );

    //初始化矩形边框
    planeRect.setWidth(PLANE_WIDTH);
    planeRect.setHeight(PLANE_HEIGHT);
    planeRect.moveTo(getX(),getY());

    //默认先发射一枚子弹
    this->record = BULLET_FREQUENCY;



}

void Plane::setXY(int xx, int yy)
{
    x = xx;
    y = yy;
}

int Plane::getX()
{
    return x;
}

int Plane::getY()
{
    return y;
}

QPixmap &Plane::getPlanePic()
{
    return planePic;
}

void Plane::up()
{
    setXY(getX(),getY() - PLANE_SPEED);
    planeRect.moveTo(getX() ,getY() -PLANE_SPEED);
}

void Plane::down()
{
    setXY(getX() ,getY() +2 );
    planeRect.moveTo(getX() ,getY() +PLANE_SPEED );
}

void Plane::left()
{
    setXY(getX() -PLANE_SPEED,getY() );
    planeRect.moveTo(getX() -PLANE_SPEED ,getY() );
}

void Plane::right()
{
    setXY(getX() + PLANE_SPEED,getY() );
    planeRect.moveTo(getX() +PLANE_SPEED ,getY());
}

void Plane::shoot()
{
    record ++;

    if(record < BULLET_FREQUENCY)
        return;
    {
        record = 0;
        for(int i=0;i<BULLET_CAPACITY;i++){
            //如果是空闲子弹 就发射出去
            if(clips[i].isFreeOrNot()){
                //将空闲状态改为假
                clips[i].setFree(false);
                //设置子弹坐标
                clips[i].setXY(getX()  + 0.5*PLANE_WIDTH - 0.5* BULLET_WIDTH,getY());  //子弹应该偏移一下 因为子弹是根据飞机的位置确定的
                break;  //找到子弹后停止寻找
            }
        }
    }
}
