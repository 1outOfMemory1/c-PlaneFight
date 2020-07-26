#include "map.h"


Map::Map()
{
    //初始化地图
    map1.load(MAP_PATH);
    map2.load(MAP_PATH);

    //初始化y轴坐标
    map1YPosition = - WINDOW_HEIGHT;  //第一张图在下边  第二张图正好显示在图中
    map2YPosition = 0;

    //地图的滚动速度
    scrollSpeed = MAP_SCROLL_SPEED;
}

void Map::mapPosition()
{
    map1YPosition += scrollSpeed;
    map2YPosition += scrollSpeed;

    if(map1YPosition >= 0){
        map1YPosition = - WINDOW_HEIGHT;  //第一张图在下边  第二张图正好显示在图中
        map2YPosition = 0;
    }
}

int Map::getMap1YPosition(int num)  //根据序号得到当前图片的y坐标
{
    return num == 1?map1YPosition:map2YPosition;
}

QPixmap &Map::getMapById(int num)  //根据序号得到当前图片
{
    return num == 1? map1: map2;
}
