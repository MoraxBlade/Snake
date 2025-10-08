#include "BarrierSnake.h"

BarrierSnake::BarrierSnake() {
    //初始化
    headUp = newimage();
    headDown = newimage();
    headLeft = newimage();
    headRight = newimage();
    bodyImg = newimage();
    foodImg = newimage();
    Background = newimage();
    staticB = newimage();
    moveB = newimage();

    //蛇
    getimage(headUp, "D:/学习/作业/软工实训/贪吃蛇/image/normalHead_up.png");
    getimage(headDown, "D:/学习/作业/软工实训/贪吃蛇/image/normalHead_down.png");
    getimage(headLeft, "D:/学习/作业/软工实训/贪吃蛇/image/normalHead_left.png");
    getimage(headRight, "D:/学习/作业/软工实训/贪吃蛇/image/normalHead_right.png");
    getimage(bodyImg, "D:/学习/作业/软工实训/贪吃蛇/image/normalBody.png");

    //食物背景
    getimage(foodImg, "D:/学习/作业/软工实训/贪吃蛇/image/food_normal.png");
    getimage(Background, "D:/学习/作业/软工实训/贪吃蛇/image/background.jpg");

    //障碍物
    getimage(staticB, "D:/学习/作业/软工实训/贪吃蛇/image/Barrier_static.png");
    getimage(moveB, "D:/学习/作业/软工实训/贪吃蛇/image/Barrier_move.png");

}

BarrierSnake::~BarrierSnake() {
    delimage(staticB);
    delimage(moveB);
}

// 检查位置是否与障碍物重叠
bool BarrierSnake::isPositionOverlapWithBarriers(const Point& pos) const {
    // 检查与静态障碍物重叠
    for (const auto& b : staticBarriers) {
        if (b.IfOverlap(pos, nodeSize)) {
            return true;
        }
    }

    // 检查与移动障碍物重叠
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
            // 检查与已有静态障碍物重叠
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
            // 检查与已有静态障碍物重叠
            for (const auto& existing : staticBarriers) {
                if (existing.IfOverlap(b.pos, nodeSize)) {
                    valid = false;
                    break;
                }
            }
            // 检查与已有动态障碍物重叠
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
    int oldScore = score; // 记录移动前分数

    // 调用基类移动逻辑
    Snake::move();

    // 每--分增加障碍物
    int controlScore = 400;
    if (score / controlScore > oldScore / controlScore) {
        barrierCount++;
        generateStaticBarrier();
        generateMoveBarrier();
    }

    // 移动障碍物
    for (auto& b : moveBarriers) {
        b.move(left, right, up, down, moveStep, nodeSize, staticBarriers);
    }

    // 定时生成新障碍物
    clock_t currentTime = clock();
    if ((currentTime - lastBarrierCreateTime) / CLOCKS_PER_SEC * 1000 > BARRIER_CREATE_INTERVAL) {
        generateStaticBarrier();
        generateMoveBarrier();
        lastBarrierCreateTime = currentTime;
    }

    // 检查与障碍物碰撞
    const Point& head = body.front();
    if (isPositionOverlapWithBarriers(head)) {
        handleDeath();
        return;
    }


}

void BarrierSnake::draw() const{
    Snake::draw();  // 先绘制基类元素

    // 绘制障碍物
    for (const auto& b : staticBarriers) {
        b.draw(staticB);
    }
    for (const auto& b : moveBarriers) {
        b.draw(moveB);
    }
}