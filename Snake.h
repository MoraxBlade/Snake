#pragma once

#include <graphics.h>
#include <vector>
#include <ctime>
#include <cmath>
#include "Common.h"
#include "Menu.h"
using namespace std;



class Snake {
protected:
    SnakeDirection dir;               // 当前移动方向
    
    Type SnakeType;                   //蛇类型
    int moveStep;
    bool isAlive;                // 蛇的存活状态
    bool isSpeeding;             // 是否处于加速状态
    clock_t speedStartTime;      // 加速开始时间戳
    clock_t lastTailReduceTime;  // 上次蛇尾缩短时间戳
    PIMAGE headUp, headDown, headLeft, headRight;  // 不同方向的蛇头图片
    PIMAGE bodyImg;              // 蛇身图片
    PIMAGE foodImg;              // 食物图片
    PIMAGE Background;                // 背景图片

    int score;                   // 当前分数
    int highScore;               // 最高分记录
    const int nodeSize = 30;     // 蛇头/蛇身/食物的尺寸（30x30像素）
    //窗口的大小
    int left = 93;
    int up = 123;
    int right = 1346;
    int down = 840;



    // 检测是否撞墙
    bool checkWallCollision() const;

    // 检测是否撞到自身
    bool checkSelfCollision() const;

    // 处理加速状态下的蛇尾缩短逻辑
    virtual void handleSpeedTailReduce();

    //控制死亡最高分记录
    void handleDeath();

public:
    vector<Point> body;          // 蛇身坐标容器（头部在front，(方便）
    Food food;                   //普通食物
    vector<Food> TailFood;            //加速时掉落的食物


    // 构造函数：初始化移动步长和基础速度
    Snake();

    // 析构函数：释放图片资源
    virtual ~Snake();

    // 纯虚函数：初始化蛇（子类必须实现）
    virtual void init() = 0;

    // 绘制游戏元素
    virtual void draw() const;

    //游玩时的键盘逻辑
    void handleInput();

    // 改变移动方向（防止180度反向）
    void setDirection(SnakeDirection newDir);


    // 切换加速状态
    void toSpeed();

    // 蛇的移动逻辑
    virtual void move();


    // 获取当前存活状态
    bool getIsAlive() const;




    // 获取当前分数
    int getScore() const;

    // 获取最高分
    int getHighScore() const;

    // 重置分数
    void resetScore();

    // 绘制背景
    virtual void drawBackground() const;
};