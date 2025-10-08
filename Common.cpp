#include "Common.h"
#include "Snake.h"
#include "BarrierSnake.h"
#include <vector>

bool Food::IfOverlap(const Point& p, int nodeSize) const {
    bool xOverlap = (pos.x < p.x + nodeSize) && (pos.x + nodeSize > p.x);
    bool yOverlap = (pos.y < p.y + nodeSize) && (pos.y + nodeSize > p.y);

    return xOverlap && yOverlap;
}

void Food::generateRandom(int left, int right, int up, int down, int nodeSize, Snake& snake) {
    
    bool onSnake;
    do {
        onSnake = false;

        int foodR = right - nodeSize;
        int foodD = down - nodeSize;
        int foodU = up + nodeSize;
        int foodL = left + nodeSize;

        // 随机生成食物坐标rand() % (b - a + 1) + a
        pos.x = rand() % (foodR - foodL + 1) + foodL;
        pos.y = rand() % (foodD - foodU + 1) + foodU;

        // 检查是否与蛇身重叠
        for (const auto& p : snake.body) {
            if (IfOverlap(p, nodeSize)) {
                onSnake = true;
                break;
            }
        }
        
        if (!onSnake) {
            BarrierSnake* barrierSnake = dynamic_cast<BarrierSnake*>(&snake);
            if (barrierSnake) {
                onSnake = barrierSnake->isPositionOverlapWithBarriers(pos);
            }
        }
    } while (onSnake);
    
}

void Food::draw(PIMAGE foodImg) const {
    if (foodImg) {  // 确保图片有效
        putimage_withalpha(NULL, foodImg, pos.x, pos.y);
    }
}


bool Barrier::IfOverlap(const Point& p, int nodeSize) const {
    bool xOverlap = (pos.x < p.x + nodeSize) && (pos.x + nodeSize > p.x);
    bool yOverlap = (pos.y < p.y + nodeSize) && (pos.y + nodeSize > p.y);

    return xOverlap && yOverlap;
}

void Barrier::generateRandom(int left, int right, int up, int down,
    int nodeSize, Snake& snake) {

    bool onItem;
    do {
        onItem = false;

        int foodR = right - nodeSize;
        int foodD = down - nodeSize;
        int foodU = up + nodeSize;
        int foodL = left + nodeSize;

        // 随机生成坐标rand() % (b - a + 1) + a
        pos.x = rand() % (foodR - foodL + 1) + foodL;
        pos.y = rand() % (foodD - foodU + 1) + foodU;

        // 检查是否与蛇身重叠
        for (const auto& p : snake.body) {
            if (IfOverlap(p, nodeSize)) {
                onItem = true;
                break;
            }
        }

        //检查是否与食物重叠
        if (IfOverlap(snake.food.pos, nodeSize)) {
            onItem = true;
            break;
        }

        //检查是否与尾部食物重叠
        for (const auto& f : snake.TailFood) {
            if (IfOverlap(f.pos, nodeSize)) {
                onItem = true;
                break;
            }
        }

       

    } while (onItem);

}

//移动
void Barrier::move(int left, int right, int up, int down,int moveStep, int nodeSize,const vector<Barrier>& barriers ){
    if (barrierType == BarrierType::MOVE) {

        Point oldPos = pos;
            //根据方向更新位置s
            switch (dir) {
            case BarrierDirection::UP_LEFT:
                pos.x -= moveStep;
                pos.y -= moveStep;
                break;
            case BarrierDirection::UP_RIGHT:
                pos.x += moveStep;
                pos.y -= moveStep;
                break;
            case BarrierDirection::DOWN_LEFT:
                pos.x -= moveStep;
                pos.y += moveStep;
                break;
            case BarrierDirection::DOWN_RIGHT:
                pos.x += moveStep;
                pos.y += moveStep;
                break;
            default:
                break;
            }

            // 检测与静态障碍物的碰撞
            //左右
            for (const auto& b : barriers) {
                if (b.barrierType == BarrierType::STATIC && b.IfOverlap(pos, nodeSize)) {
                    // 发生碰撞，回退
                    pos = oldPos;
                    // 反弹逻辑：根据当前方向反向
                    switch (dir) {
                    case BarrierDirection::UP_LEFT:    dir = BarrierDirection::UP_RIGHT; break;
                    case BarrierDirection::UP_RIGHT:   dir = BarrierDirection::UP_LEFT;  break;
                    case BarrierDirection::DOWN_LEFT:  dir = BarrierDirection::DOWN_RIGHT;   break;
                    case BarrierDirection::DOWN_RIGHT: dir = BarrierDirection::DOWN_LEFT;    break;
                    }
                    break;
                }
            }
            //上下
            for (const auto& b : barriers) {
                if (b.barrierType == BarrierType::STATIC && b.IfOverlap(pos, nodeSize)) {
                    // 发生碰撞，回退
                    pos = oldPos;
                    // 反弹逻辑，根据当前方向反向
                    switch (dir) {
                    case BarrierDirection::UP_LEFT: dir = BarrierDirection::DOWN_LEFT; break;
                    case BarrierDirection::UP_RIGHT: dir = BarrierDirection::DOWN_RIGHT; break;
                    case BarrierDirection::DOWN_LEFT: dir = BarrierDirection::UP_LEFT; break;
                    case BarrierDirection::DOWN_RIGHT: dir = BarrierDirection::UP_RIGHT; break;
                    }
                    break;
                }
            }


         

            // 检查左边界碰撞
            if (pos.x < left) {
                pos.x = left;  // 修正位置
                // 左右方向反转
                if (dir == BarrierDirection::UP_LEFT) {
                    dir = BarrierDirection::UP_RIGHT;
                }
                else if (dir == BarrierDirection::DOWN_LEFT) {
                    dir = BarrierDirection::DOWN_RIGHT;
                }
            }
            // 检查右边界碰撞
            else if (pos.x > right - nodeSize) {
                pos.x = right - nodeSize;  // 修正位置
                // 左右方向反转
                if (dir == BarrierDirection::UP_RIGHT) {
                    dir = BarrierDirection::UP_LEFT;
                }
                else if (dir == BarrierDirection::DOWN_RIGHT) {
                    dir = BarrierDirection::DOWN_LEFT;
                }
            }

            // 检查上边界碰撞
            if (pos.y < up) {
                pos.y = up;  // 修正位置
                // 上下方向反转
                if (dir == BarrierDirection::UP_LEFT) {
                    dir = BarrierDirection::DOWN_LEFT;
                }
                else if (dir == BarrierDirection::UP_RIGHT) {
                    dir = BarrierDirection::DOWN_RIGHT;
                }
            }
            // 检查下边界碰撞
            else if (pos.y > down - nodeSize) {
                pos.y = down - nodeSize;  // 修正位置
                // 上下方向反转
                if (dir == BarrierDirection::DOWN_LEFT) {
                    dir = BarrierDirection::UP_LEFT;
                }
                else if (dir == BarrierDirection::DOWN_RIGHT) {
                    dir = BarrierDirection::UP_RIGHT;
                }
            }
    }
}

void Barrier::draw(PIMAGE foodImg) const {
    if (foodImg) {  // 确保图片有效
        putimage_withalpha(NULL, foodImg, pos.x, pos.y);
    }
}