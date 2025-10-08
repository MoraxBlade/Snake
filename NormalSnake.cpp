#include "NormalSnake.h"

NormalSnake::NormalSnake() {
    //��ʼ��
    headUp = newimage();
    headDown = newimage();
    headLeft = newimage();
    headRight = newimage(); 
    bodyImg = newimage();
    foodImg = newimage();
    Background = newimage();

    //��
    getimage(headUp, "./image/normalHead_up.png");
    getimage(headDown, "./image/normalHead_down.png");
    getimage(headLeft, "./image/normalHead_left.png");
    getimage(headRight, "./image/normalHead_right.png");
    getimage(bodyImg, "./image/normalBody.png");

    //ʳ�ﱳ��
    getimage(foodImg, "./image/food_normal.png");
    getimage(Background, "./image/background.jpg");
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




