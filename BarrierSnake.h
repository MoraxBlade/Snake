#pragma once
#include "Snake.h"
class BarrierSnake :
    public Snake
{
public:
    //障碍物（静态+移动）
    vector<Barrier> staticBarriers;
    vector<Barrier> moveBarriers;
    int barrierCount=0;
    clock_t lastBarrierCreateTime=0;//上次障碍物生成时间戳
    //障碍物图片
    PIMAGE staticB;
    PIMAGE moveB;
    const int BARRIER_CREATE_INTERVAL = 10000;  // 障碍物生成间隔

    // 检查位置是否与障碍物重叠
    bool isPositionOverlapWithBarriers(const Point& pos) const;
    // 构造函数
    BarrierSnake();

    // 析构函数
    ~BarrierSnake();

    //随机生成静态障碍
    void generateStaticBarrier();

    //随机生成动态障碍
    void generateMoveBarrier();


    // 初始化游戏
    void init() override;

    //重载移动逻辑
    void move() override;

    //重载绘制逻辑
    void draw()const override;

};

