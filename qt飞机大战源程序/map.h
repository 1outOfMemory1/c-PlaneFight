#ifndef MAP_H
#define MAP_H
#include <QPixmap>
#include <QWidget>
#include "config.h"

class Map : public QWidget
{
    Q_OBJECT
private:
    QPixmap  map1,map2;
    int map1YPosition,map2YPosition;
    int scrollSpeed;
public:
    //构造函数
    Map();
    void mapPosition();
    int getMap1YPosition(int num);  //根据序号得到当前图片的y坐标
    QPixmap & getMapById(int num);  //根据序号得到当前图片

};

#endif // MAP_H
