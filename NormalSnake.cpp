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
	getimage(headUp, "D:/ѧϰ/��ҵ/��ʵѵ/̰����/image/normalHead_up.png");
    getimage(headDown, "D:/ѧϰ/��ҵ/��ʵѵ/̰����/image/normalHead_down.png");
    getimage(headLeft, "D:/ѧϰ/��ҵ/��ʵѵ/̰����/image/normalHead_left.png");
    getimage(headRight, "D:/ѧϰ/��ҵ/��ʵѵ/̰����/image/normalHead_right.png");
    getimage(bodyImg, "D:/ѧϰ/��ҵ/��ʵѵ/̰����/image/normalBody.png");

    //ʳ�ﱳ��
    getimage(foodImg, "D:/ѧϰ/��ҵ/��ʵѵ/̰����/image/food_normal.png");
    getimage(Background, "D:/ѧϰ/��ҵ/��ʵѵ/̰����/image/background.jpg");

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




