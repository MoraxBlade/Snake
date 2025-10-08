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

        // �������ʳ������rand() % (b - a + 1) + a
        pos.x = rand() % (foodR - foodL + 1) + foodL;
        pos.y = rand() % (foodD - foodU + 1) + foodU;

        // ����Ƿ��������ص�
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
    if (foodImg) {  // ȷ��ͼƬ��Ч
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

        // �����������rand() % (b - a + 1) + a
        pos.x = rand() % (foodR - foodL + 1) + foodL;
        pos.y = rand() % (foodD - foodU + 1) + foodU;

        // ����Ƿ��������ص�
        for (const auto& p : snake.body) {
            if (IfOverlap(p, nodeSize)) {
                onItem = true;
                break;
            }
        }

        //����Ƿ���ʳ���ص�
        if (IfOverlap(snake.food.pos, nodeSize)) {
            onItem = true;
            break;
        }

        //����Ƿ���β��ʳ���ص�
        for (const auto& f : snake.TailFood) {
            if (IfOverlap(f.pos, nodeSize)) {
                onItem = true;
                break;
            }
        }

       

    } while (onItem);

}

//�ƶ�
void Barrier::move(int left, int right, int up, int down,int moveStep, int nodeSize,const vector<Barrier>& barriers ){
    if (barrierType == BarrierType::MOVE) {

        Point oldPos = pos;
            //���ݷ������λ��s
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

            // ����뾲̬�ϰ������ײ
            //����
            for (const auto& b : barriers) {
                if (b.barrierType == BarrierType::STATIC && b.IfOverlap(pos, nodeSize)) {
                    // ������ײ������
                    pos = oldPos;
                    // �����߼������ݵ�ǰ������
                    switch (dir) {
                    case BarrierDirection::UP_LEFT:    dir = BarrierDirection::UP_RIGHT; break;
                    case BarrierDirection::UP_RIGHT:   dir = BarrierDirection::UP_LEFT;  break;
                    case BarrierDirection::DOWN_LEFT:  dir = BarrierDirection::DOWN_RIGHT;   break;
                    case BarrierDirection::DOWN_RIGHT: dir = BarrierDirection::DOWN_LEFT;    break;
                    }
                    break;
                }
            }
            //����
            for (const auto& b : barriers) {
                if (b.barrierType == BarrierType::STATIC && b.IfOverlap(pos, nodeSize)) {
                    // ������ײ������
                    pos = oldPos;
                    // �����߼������ݵ�ǰ������
                    switch (dir) {
                    case BarrierDirection::UP_LEFT: dir = BarrierDirection::DOWN_LEFT; break;
                    case BarrierDirection::UP_RIGHT: dir = BarrierDirection::DOWN_RIGHT; break;
                    case BarrierDirection::DOWN_LEFT: dir = BarrierDirection::UP_LEFT; break;
                    case BarrierDirection::DOWN_RIGHT: dir = BarrierDirection::UP_RIGHT; break;
                    }
                    break;
                }
            }


         

            // �����߽���ײ
            if (pos.x < left) {
                pos.x = left;  // ����λ��
                // ���ҷ���ת
                if (dir == BarrierDirection::UP_LEFT) {
                    dir = BarrierDirection::UP_RIGHT;
                }
                else if (dir == BarrierDirection::DOWN_LEFT) {
                    dir = BarrierDirection::DOWN_RIGHT;
                }
            }
            // ����ұ߽���ײ
            else if (pos.x > right - nodeSize) {
                pos.x = right - nodeSize;  // ����λ��
                // ���ҷ���ת
                if (dir == BarrierDirection::UP_RIGHT) {
                    dir = BarrierDirection::UP_LEFT;
                }
                else if (dir == BarrierDirection::DOWN_RIGHT) {
                    dir = BarrierDirection::DOWN_LEFT;
                }
            }

            // ����ϱ߽���ײ
            if (pos.y < up) {
                pos.y = up;  // ����λ��
                // ���·���ת
                if (dir == BarrierDirection::UP_LEFT) {
                    dir = BarrierDirection::DOWN_LEFT;
                }
                else if (dir == BarrierDirection::UP_RIGHT) {
                    dir = BarrierDirection::DOWN_RIGHT;
                }
            }
            // ����±߽���ײ
            else if (pos.y > down - nodeSize) {
                pos.y = down - nodeSize;  // ����λ��
                // ���·���ת
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
    if (foodImg) {  // ȷ��ͼƬ��Ч
        putimage_withalpha(NULL, foodImg, pos.x, pos.y);
    }
}