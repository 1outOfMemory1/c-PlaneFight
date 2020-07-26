#ifndef CONFIG_H
#define CONFIG_H

/****** 游戏基础配置信息 ******/
#define GAME_TITLE  "飞机大战 by haonan"     //程序标题
#define WINDOW_WIDTH  580       //窗口宽度
#define WINDOW_HEIGHT  900     // 窗口高度
#define GAME_REFRESH_RATE  50 // 定时器刷新时间间隔 游戏刷新频率   单位毫秒


/****** 背景的配置信息 ******/
#define MAP_PATH ":/res/background.jpg"   //背景图片地址
#define MAP_SCROLL_SPEED   10           //滚动速度  单位是像素


/****** 飞机的配置信息 ******/
#define PLANEPIC_PATH ":/res/me.bmp"  //飞机图片的路径
#define PLANE_WIDTH 50   //飞机图片的宽度
#define PLANE_HEIGHT 60  //飞机图片的长度
#define PLANE_SPEED 2   //飞机上下左右的移动速度
#define BULLET_CAPACITY  20 //飞机子弹弹夹的数量


/****** 子弹的配置信息 ******/
#define BULLET_PATH ":/res/bullet.bmp"  //子弹图片的路径
#define BULLET_WIDTH 10   //子弹图片的宽度
#define BULLET_HEIGHT 20  //子弹图片的长度
#define BULLET_SPEED 15    //子弹发射的速度
#define BULLET_FREQUENCY 4 //这里以主时钟timer为基准 当数数到4的时候才发射一枚子弹  50 * 4 = 200  所以每隔200毫秒发射一枚子弹


/****** 敌机的配置信息 ******/
#define ENEMY_FROM_UP_PATH ":/res/enemyFromUp.bmp"     //从上方来的敌机
#define ENEMY_FROM_DOWN_PATH ":/res/enemyFromDown.bmp"   //从下方来的敌机
#define SPEED_OF_FASTER_ENEMYPLANE  8   //高速度敌机的速度
#define SPEED_OF_SLOWER_ENEMYPLANE  4   //低速度敌机的速度
#define ENEMYPLANE_NUM  10  //敌机总数量
#define ENEMYPLANE_INTERVAL 30  //敌机出场的间隔 单位是毫秒
#define ENEMYPLANE_NUM_FREQUENCY 8  //这里以主时钟timer为基准 当数数到4的时候才出现一个敌机  50 * 4 = 200  所以每隔200毫秒出现一个敌机

/****** 爆炸类的配置信息 ******/
#define BOMB_PIC_PATH ":/res/bomb%1.BMP"
#define BOMB_NUM 20  //爆炸数量
#define BOMB_MAX_INDEXS 8 //总共8张图片
#define BOMB_INTERVAL 20 //爆炸切图的时间间隔







#endif // CONFIG_H
