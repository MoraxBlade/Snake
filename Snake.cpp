#include "Snake.h"
#include "Common.h"
#include <random>
#include <cstdlib>

// 检测是否撞墙
bool Snake::checkWallCollision() const {
    const Point& head = body.front();
    return head.x < left || head.x + nodeSize > right|| head.y < up || head.y + nodeSize > down;
}

// 检测是否撞到自身
bool Snake::checkSelfCollision() const {
    if (body.size() == 1)return false;
    const Point& head = body.front();
    for (auto it = body.begin() + 3;it != body.end();it++) {
        const Point& p = *it;
        bool xOverlap = (head.x < p.x + nodeSize) && (head.x + nodeSize > p.x);
        bool yOverlap = (head.y < p.y + nodeSize) && (head.y + nodeSize > p.y);
        if (xOverlap && yOverlap) {
            return true;
        }
    }
    return false;
}

// 加速蛇尾缩短
void Snake::handleSpeedTailReduce() {
    if (!isSpeeding) return;
    clock_t now = clock();
    if (now - lastTailReduceTime >= 800 && body.size() > 3) {
        body.pop_back();
        Food current(SnakeType, body.back());

        switch (dir) {
        case SnakeDirection::UP:    current.pos.y += nodeSize; break;
        case SnakeDirection::DOWN:  current.pos.y -= nodeSize; break;
        case SnakeDirection::LEFT:  current.pos.x += nodeSize; break;
        case SnakeDirection::RIGHT: current.pos.x -= nodeSize; break;
        }

        TailFood.push_back(current);
        //如果在这里绘制，掉落的食物会被刷掉
        //统一在draw中绘制

        lastTailReduceTime = now;
    }
}

//控制死亡最高分记录
void Snake::handleDeath() {
    isAlive = false;
    if (score > highScore) {
        highScore = score;
    }
}

    // 构造函数：初始化移动步长和基础速度
Snake::Snake() :moveStep(20),dir(SnakeDirection::UP),SnakeType(Type::NORMAL),
isAlive(true), isSpeeding(false), score(0), highScore(0), speedStartTime(0), lastTailReduceTime(0) {
    headUp = headDown = headLeft = headRight = nullptr;
    bodyImg = foodImg = Background = nullptr;
}

    // 析构函数：释放图片资源
Snake::~Snake() {
    if (headUp) delimage(headUp);
    if (headDown) delimage(headDown);
    if (headLeft) delimage(headLeft);
    if (headRight) delimage(headRight);
    if (bodyImg) delimage(bodyImg);
    if (foodImg) delimage(foodImg);
    if (Background) delimage(Background);
}


    // 改变移动方向（防止180度反向）
void Snake::setDirection(SnakeDirection newDir) {
    if (isAlive) {
        if ((dir == SnakeDirection::UP && newDir != SnakeDirection::DOWN)
            || (dir == SnakeDirection::DOWN && newDir != SnakeDirection::UP)
            || (dir == SnakeDirection::LEFT && newDir != SnakeDirection::RIGHT)
            || (dir == SnakeDirection::RIGHT && newDir != SnakeDirection::LEFT)) {
            dir = newDir;
        }
    }
}

//游玩键盘

void Snake::handleInput() {
    if (!isAlive) return;

    if (kbhit()) {
        char key = getch();
        switch (key) {
        case 'w': case 'W':
            setDirection(SnakeDirection::UP);
            break;
        case 's': case 'S':
            setDirection(SnakeDirection::DOWN);
            break;
        case 'a': case 'A':
            setDirection(SnakeDirection::LEFT);
            break;
        case 'd': case 'D':
            setDirection(SnakeDirection::RIGHT);
            break;
        case 'j': case 'J':
            toSpeed();
            break;
        case 27:  
            // 由外部处理状态切换，这里只做标记或通知
            break;
        }
    }
}

void Snake::draw() const {
    if (!isAlive) return;
    drawBackground();

    // 绘制分数1060-70
    settextcolor(BLACK);
    setfont(-40, 0, "微软雅黑");//负数表示像素
    setbkmode(0);
    char scoreText[10000];
    sprintf(scoreText, "%d", score);
    outtextxy(1060, 60, scoreText);

    const Point& head = body.front();
    switch (dir) {
    case SnakeDirection::UP:    putimage(head.x, head.y, headUp);    break;
    case SnakeDirection::DOWN:  putimage(head.x, head.y, headDown);  break;
    case SnakeDirection::LEFT:  putimage(head.x, head.y, headLeft);  break;
    case SnakeDirection::RIGHT: putimage(head.x, head.y, headRight); break;
    }

    // 绘制蛇身
    for (size_t i = 1; i < body.size(); ++i) {
        putimage(body[i].x, body[i].y, bodyImg);
    }

    // 绘制食物

    food.draw(foodImg);
    for (const auto& tailFood : TailFood) {
        tailFood.draw(foodImg);  
    }

}

// 切换加速状态
void Snake::toSpeed() {
    if (!isAlive)return;

    isSpeeding = !isSpeeding;

        //回到原速度或者切换到加速


    if (isSpeeding) {
        if (body.size() > 3) {
            speedStartTime = clock();
            lastTailReduceTime = clock();
        }
        else {
            isSpeeding = false;
        }
    }

}

    // 蛇的移动逻辑
void Snake::move() {
    if (!isAlive) return;
    //计算加速时间，大于6秒即结束
    if (isSpeeding && (clock() - speedStartTime) >= 6000) {
        toSpeed();
    }
    if (isSpeeding) {
        Sleep(60);
    }
    else {
        Sleep(80);
    }
    // 计算新蛇头位置
    Point newHead = body.front();
    switch (dir) {
    case SnakeDirection::UP:    newHead.y -= moveStep; break;
    case SnakeDirection::DOWN:  newHead.y += moveStep; break;
    case SnakeDirection::LEFT:  newHead.x -= moveStep; break;
    case SnakeDirection::RIGHT: newHead.x += moveStep; break;
    }

    // 检测碰撞（边界/自身）
    if (checkWallCollision() || checkSelfCollision()) {
        handleDeath();
        return;
    }

    // 蛇身移动
    body.insert(body.begin(), newHead);
    bool eatFood = false;

    // 检测是否吃到食物
    int tailFoodIndex = -1;  // 记录吃到的尾部食物索引

    // 优先检测是否吃到尾部产生的食物
    for (size_t i = 0; i < TailFood.size(); ++i) {
        if (TailFood[i].IfOverlap(newHead, nodeSize)) {
            eatFood = true;
            tailFoodIndex = i;
            
            if (isSpeeding) score += 200;
            else score += 100;

            break;
        }
    }
    //检测是否吃到随机食物

    if (eatFood == false && food.IfOverlap(newHead, nodeSize)) {
        eatFood = true;
        if (isSpeeding) score += 200;
        else score += 100;

        food.generateRandom(left, right, up, down, nodeSize, *this);
    }

    if (tailFoodIndex != -1 && tailFoodIndex < TailFood.size()) {
        TailFood.erase(TailFood.begin() + tailFoodIndex);
    }
    
    // 没吃到食物则移除尾
    if (!eatFood) {
        // 确保删除后蛇长度≥2
        if (body.size() > 2) {
            body.pop_back();
        }
        else {
            // 长度不足时，强制标记为“吃到食物”（避免删除尾部）
            eatFood = true;
        }
    }

    // 加速蛇尾缩短处理
    handleSpeedTailReduce();
}



    // 获取当前存活状态
bool Snake::getIsAlive() const { return isAlive; }

    // 获取当前速度

    // 获取当前分数
int Snake::getScore() const { return score; }

    // 获取最高分
int Snake::getHighScore() const { return highScore; }

    // 重置分数
void Snake::resetScore() {
    score = 0;
}

    // 绘制背景
void Snake::drawBackground() const {
    if (Background != nullptr){
        putimage(0, 0, Background);
    }
    else {
        setbkcolor(WHITE);
        cleardevice();
    }
}
