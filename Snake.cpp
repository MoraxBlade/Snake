#include "Snake.h"
#include "Common.h"
#include <random>
#include <cstdlib>

// ����Ƿ�ײǽ
bool Snake::checkWallCollision() const {
    const Point& head = body.front();
    return head.x < left || head.x + nodeSize > right|| head.y < up || head.y + nodeSize > down;
}

// ����Ƿ�ײ������
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

// ������β����
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
        //�����������ƣ������ʳ��ᱻˢ��
        //ͳһ��draw�л���

        lastTailReduceTime = now;
    }
}

//����������߷ּ�¼
void Snake::handleDeath() {
    isAlive = false;
    if (score > highScore) {
        highScore = score;
    }
}

    // ���캯������ʼ���ƶ������ͻ����ٶ�
Snake::Snake() :moveStep(20),dir(SnakeDirection::UP),SnakeType(Type::NORMAL),
isAlive(true), isSpeeding(false), score(0), highScore(0), speedStartTime(0), lastTailReduceTime(0) {
    headUp = headDown = headLeft = headRight = nullptr;
    bodyImg = foodImg = Background = nullptr;
}

    // �����������ͷ�ͼƬ��Դ
Snake::~Snake() {
    if (headUp) delimage(headUp);
    if (headDown) delimage(headDown);
    if (headLeft) delimage(headLeft);
    if (headRight) delimage(headRight);
    if (bodyImg) delimage(bodyImg);
    if (foodImg) delimage(foodImg);
    if (Background) delimage(Background);
}


    // �ı��ƶ����򣨷�ֹ180�ȷ���
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

//�������

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
            // ���ⲿ����״̬�л�������ֻ����ǻ�֪ͨ
            break;
        }
    }
}

void Snake::draw() const {
    if (!isAlive) return;
    drawBackground();

    // ���Ʒ���1060-70
    settextcolor(BLACK);
    setfont(-40, 0, "΢���ź�");//������ʾ����
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

    // ��������
    for (size_t i = 1; i < body.size(); ++i) {
        putimage(body[i].x, body[i].y, bodyImg);
    }

    // ����ʳ��

    food.draw(foodImg);
    for (const auto& tailFood : TailFood) {
        tailFood.draw(foodImg);  
    }

}

// �л�����״̬
void Snake::toSpeed() {
    if (!isAlive)return;

    isSpeeding = !isSpeeding;

        //�ص�ԭ�ٶȻ����л�������


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

    // �ߵ��ƶ��߼�
void Snake::move() {
    if (!isAlive) return;
    //�������ʱ�䣬����6�뼴����
    if (isSpeeding && (clock() - speedStartTime) >= 6000) {
        toSpeed();
    }
    if (isSpeeding) {
        Sleep(60);
    }
    else {
        Sleep(80);
    }
    // ��������ͷλ��
    Point newHead = body.front();
    switch (dir) {
    case SnakeDirection::UP:    newHead.y -= moveStep; break;
    case SnakeDirection::DOWN:  newHead.y += moveStep; break;
    case SnakeDirection::LEFT:  newHead.x -= moveStep; break;
    case SnakeDirection::RIGHT: newHead.x += moveStep; break;
    }

    // �����ײ���߽�/����
    if (checkWallCollision() || checkSelfCollision()) {
        handleDeath();
        return;
    }

    // �����ƶ�
    body.insert(body.begin(), newHead);
    bool eatFood = false;

    // ����Ƿ�Ե�ʳ��
    int tailFoodIndex = -1;  // ��¼�Ե���β��ʳ������

    // ���ȼ���Ƿ�Ե�β��������ʳ��
    for (size_t i = 0; i < TailFood.size(); ++i) {
        if (TailFood[i].IfOverlap(newHead, nodeSize)) {
            eatFood = true;
            tailFoodIndex = i;
            
            if (isSpeeding) score += 200;
            else score += 100;

            break;
        }
    }
    //����Ƿ�Ե����ʳ��

    if (eatFood == false && food.IfOverlap(newHead, nodeSize)) {
        eatFood = true;
        if (isSpeeding) score += 200;
        else score += 100;

        food.generateRandom(left, right, up, down, nodeSize, *this);
    }

    if (tailFoodIndex != -1 && tailFoodIndex < TailFood.size()) {
        TailFood.erase(TailFood.begin() + tailFoodIndex);
    }
    
    // û�Ե�ʳ�����Ƴ�β
    if (!eatFood) {
        // ȷ��ɾ�����߳��ȡ�2
        if (body.size() > 2) {
            body.pop_back();
        }
        else {
            // ���Ȳ���ʱ��ǿ�Ʊ��Ϊ���Ե�ʳ�������ɾ��β����
            eatFood = true;
        }
    }

    // ������β���̴���
    handleSpeedTailReduce();
}



    // ��ȡ��ǰ���״̬
bool Snake::getIsAlive() const { return isAlive; }

    // ��ȡ��ǰ�ٶ�

    // ��ȡ��ǰ����
int Snake::getScore() const { return score; }

    // ��ȡ��߷�
int Snake::getHighScore() const { return highScore; }

    // ���÷���
void Snake::resetScore() {
    score = 0;
}

    // ���Ʊ���
void Snake::drawBackground() const {
    if (Background != nullptr){
        putimage(0, 0, Background);
    }
    else {
        setbkcolor(WHITE);
        cleardevice();
    }
}
