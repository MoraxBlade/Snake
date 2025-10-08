#pragma once
#include "Snake.h"

class NormalSnake :
    public Snake
{
public:
    // 构造函数
    NormalSnake();

    // 析构函数
    ~NormalSnake() override;

    // 初始化游戏
    void init() override;


};

