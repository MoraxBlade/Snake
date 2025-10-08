#include "BarrierSnake.h"

BarrierSnake::BarrierSnake() {
    //��ʼ��
    headUp = newimage();
    headDown = newimage();
    headLeft = newimage();
    headRight = newimage();
    bodyImg = newimage();
    foodImg = newimage();
    Background = newimage();
    staticB = newimage();
    moveB = newimage();

    //��
    getimage(headUp, "D:/ѧϰ/��ҵ/��ʵѵ/̰����/image/normalHead_up.png");
    getimage(headDown, "D:/ѧϰ/��ҵ/��ʵѵ/̰����/image/normalHead_down.png");
    getimage(headLeft, "D:/ѧϰ/��ҵ/��ʵѵ/̰����/image/normalHead_left.png");
    getimage(headRight, "D:/ѧϰ/��ҵ/��ʵѵ/̰����/image/normalHead_right.png");
    getimage(bodyImg, "D:/ѧϰ/��ҵ/��ʵѵ/̰����/image/normalBody.png");

    //ʳ�ﱳ��
    getimage(foodImg, "D:/ѧϰ/��ҵ/��ʵѵ/̰����/image/food_normal.png");
    getimage(Background, "D:/ѧϰ/��ҵ/��ʵѵ/̰����/image/background.jpg");

    //�ϰ���
    getimage(staticB, "D:/ѧϰ/��ҵ/��ʵѵ/̰����/image/Barrier_static.png");
    getimage(moveB, "D:/ѧϰ/��ҵ/��ʵѵ/̰����/image/Barrier_move.png");

}

BarrierSnake::~BarrierSnake() {
    delimage(staticB);
    delimage(moveB);
}

// ���λ���Ƿ����ϰ����ص�
bool BarrierSnake::isPositionOverlapWithBarriers(const Point& pos) const {
    // ����뾲̬�ϰ����ص�
    for (const auto& b : staticBarriers) {
        if (b.IfOverlap(pos, nodeSize)) {
            return true;
        }
    }

    // ������ƶ��ϰ����ص�
    for (const auto& b : moveBarriers) {
        if (b.IfOverlap(pos, nodeSize)) {
            return true;
        }
    }
    return false;
}

void BarrierSnake::generateStaticBarrier() {
    staticBarriers.clear();
    for (int i = 0; i < barrierCount; i++) {
        Barrier b(BarrierType::STATIC);
        bool valid = false;
        do {
            valid = true;
            b.generateRandom(left, right, up, down, nodeSize, *this);
            // ��������о�̬�ϰ����ص�
            for (const auto& existing : staticBarriers) {
                if (existing.IfOverlap(b.pos, nodeSize)) {
                    valid = false;
                    break;
                }
            }


        } while (!valid);
        staticBarriers.push_back(b);
    }
}

void BarrierSnake::generateMoveBarrier() {
    moveBarriers.clear();
    for (int i = 0; i < barrierCount; i++) {
        int dirCase = rand() % 4;
        BarrierDirection dir;
        switch (dirCase) {
        case 0:dir = BarrierDirection::DOWN_RIGHT;break;
        case 1:dir = BarrierDirection::UP_LEFT;break;
        case 2:dir = BarrierDirection::UP_RIGHT;break;
        case 3:dir = BarrierDirection::DOWN_LEFT;break;
        }
        Barrier b(BarrierType::MOVE, dir);
        bool valid = false;
        do {
            valid = true;
            b.generateRandom(left, right, up, down, nodeSize, *this);
            // ��������о�̬�ϰ����ص�
            for (const auto& existing : staticBarriers) {
                if (existing.IfOverlap(b.pos, nodeSize)) {
                    valid = false;
                    break;
                }
            }
            // ��������ж�̬�ϰ����ص�
            for (const auto& existing : moveBarriers) {
                if (existing.IfOverlap(b.pos, nodeSize)) {
                    valid = false;
                    break;
                }
            }
        } while (!valid);
        moveBarriers.push_back(b);
    }
}


void BarrierSnake::init() {
    body.clear();
    TailFood.clear();
    staticBarriers.clear();
    moveBarriers.clear();

    dir = SnakeDirection::UP;

    for (int i = 0;i < 10;i++) {
        body.push_back({ 720,450 + moveStep * i });
    }

    isAlive = true;
    isSpeeding = false;
    resetScore();

    lastBarrierCreateTime = clock();
    barrierCount = 3;


    food.generateRandom(left, right, up, down, nodeSize, *this);
    generateStaticBarrier();
    generateMoveBarrier();
    
    

}

void BarrierSnake::move() {
    if (!isAlive) return;
    int oldScore = score; // ��¼�ƶ�ǰ����

    // ���û����ƶ��߼�
    Snake::move();

    // ÿ--�������ϰ���
    int controlScore = 400;
    if (score / controlScore > oldScore / controlScore) {
        barrierCount++;
        generateStaticBarrier();
        generateMoveBarrier();
    }

    // �ƶ��ϰ���
    for (auto& b : moveBarriers) {
        b.move(left, right, up, down, moveStep, nodeSize, staticBarriers);
    }

    // ��ʱ�������ϰ���
    clock_t currentTime = clock();
    if ((currentTime - lastBarrierCreateTime) / CLOCKS_PER_SEC * 1000 > BARRIER_CREATE_INTERVAL) {
        generateStaticBarrier();
        generateMoveBarrier();
        lastBarrierCreateTime = currentTime;
    }

    // ������ϰ�����ײ
    const Point& head = body.front();
    if (isPositionOverlapWithBarriers(head)) {
        handleDeath();
        return;
    }


}

void BarrierSnake::draw() const{
    Snake::draw();  // �Ȼ��ƻ���Ԫ��

    // �����ϰ���
    for (const auto& b : staticBarriers) {
        b.draw(staticB);
    }
    for (const auto& b : moveBarriers) {
        b.draw(moveB);
    }
}