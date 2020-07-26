#ifndef BOMB_H
#define BOMB_H
#include <QVector>
#include <QPixmap>
#include "config.h"

class Bomb
{
private:

    int x,y;  //爆炸的位置
    bool isFree;
    unsigned int index; //爆炸时的下标
    int bombFrequancyRecord;
public:
    QVector<QPixmap> pix_arr;  //存放所有的图
    Bomb();
    void updateInfo();
    void setXY(int xx, int yy);
    int getX();
    int getY();
    bool isFreeOrnot();
    void setFree(bool b);
    int getIndex();



};

#endif // BOMB_H
