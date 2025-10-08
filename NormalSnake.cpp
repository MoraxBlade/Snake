#include "NormalSnake.h"

NormalSnake::NormalSnake() {
    //初始化
    headUp = newimage();
    headDown = newimage();
    headLeft = newimage();
    headRight = newimage(); 
    bodyImg = newimage();
    foodImg = newimage();
    Background = newimage();

    //蛇
	getimage(headUp, "D:/学习/作业/软工实训/贪吃蛇/image/normalHead_up.png");
    getimage(headDown, "D:/学习/作业/软工实训/贪吃蛇/image/normalHead_down.png");
    getimage(headLeft, "D:/学习/作业/软工实训/贪吃蛇/image/normalHead_left.png");
    getimage(headRight, "D:/学习/作业/软工实训/贪吃蛇/image/normalHead_right.png");
    getimage(bodyImg, "D:/学习/作业/软工实训/贪吃蛇/image/normalBody.png");

    //食物背景
    getimage(foodImg, "D:/学习/作业/软工实训/贪吃蛇/image/food_normal.png");
    getimage(Background, "D:/学习/作业/软工实训/贪吃蛇/image/background.jpg");

}

NormalSnake::~NormalSnake() {
    
}

void NormalSnake::init() {
    body.clear();
    TailFood.clear();

    dir = SnakeDirection::UP;
    
    for (int i = 0;i < 10;i++) {
        body.push_back({ 720,450 + moveStep * i });
    }

    dir = SnakeDirection::UP;
    isAlive = true;
    isSpeeding = false;
    resetScore();
    food.generateRandom(left,right,up,down,nodeSize,*this);
}




