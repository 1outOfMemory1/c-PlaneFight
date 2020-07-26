#include "bomb.h"
#include <QString>
#include <QBitmap>

Bomb::Bomb()
{
    //加载8张图片
    for(int i=1;i<=BOMB_MAX_INDEXS;i++){
        QString str = QString(BOMB_PIC_PATH).arg(i);
        QPixmap pic;
        pic.load(str);
        QBitmap mask =  pic.createMaskFromColor(QColor(0,0,0),Qt::MaskInColor);  //设计一个遮罩 把黑色部分弄没
        pic.setMask(mask);   //图片添加遮罩
        pix_arr.push_back(str);
    }

    //坐标
    setXY(0,0);

    //空闲状态
    setFree(true);

    bombFrequancyRecord = BOMB_INTERVAL;
    index = 0;

}

void Bomb::updateInfo()
{
    bombFrequancyRecord++;

    //空闲状态下的爆炸或者未到爆炸间隔时间 直接return
    if(isFreeOrnot() == true || bombFrequancyRecord < BOMB_INTERVAL)
        return ;

    index ++;
    if(index > BOMB_MAX_INDEXS -1){
        index =0;
        setFree(true);
    }


}

void Bomb::setXY(int xx,int yy)
{
    x = xx;
    y = yy;
}

int Bomb::getX()
{
    return x;
}

int Bomb::getY()
{
    return  y;
}

bool Bomb::isFreeOrnot()
{
    return isFree;
}

void Bomb::setFree(bool b)
{
    isFree = b;
}

int Bomb::getIndex()
{
    return index;
}
