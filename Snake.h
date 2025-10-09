#pragma once

#include <graphics.h>
#include <vector>
#include <ctime>
#include <cmath>
#include "Common.h"
#include "Menu.h"
using namespace std;



class Snake {
protected:
    SnakeDirection dir;               // ��ǰ�ƶ�����
    
    Type SnakeType;                   //������
    int moveStep;
    bool isAlive;                // �ߵĴ��״̬
    bool isSpeeding;             // �Ƿ��ڼ���״̬
    clock_t speedStartTime;      // ���ٿ�ʼʱ���
    clock_t lastTailReduceTime;  // �ϴ���β����ʱ���
    PIMAGE headUp, headDown, headLeft, headRight;  // ��ͬ�������ͷͼƬ
    PIMAGE bodyImg;              // ����ͼƬ
    PIMAGE foodImg;              // ʳ��ͼƬ
    PIMAGE Background;                // ����ͼƬ

    int score;                   // ��ǰ����
    int highScore;               // ��߷ּ�¼
    const int nodeSize = 30;     // ��ͷ/����/ʳ��ĳߴ磨30x30���أ�
    //���ڵĴ�С
    int left = 93;
    int up = 123;
    int right = 1346;
    int down = 840;



    // ����Ƿ�ײǽ
    bool checkWallCollision() const;

    // ����Ƿ�ײ������
    bool checkSelfCollision() const;

    // �������״̬�µ���β�����߼�
    virtual void handleSpeedTailReduce();

    //����������߷ּ�¼
    void handleDeath();

public:
    vector<Point> body;          // ��������������ͷ����front��(���㣩
    Food food;                   //��ͨʳ��
    vector<Food> TailFood;            //����ʱ�����ʳ��


    // ���캯������ʼ���ƶ������ͻ����ٶ�
    Snake();

    // �����������ͷ�ͼƬ��Դ
    virtual ~Snake();

    // ���麯������ʼ���ߣ��������ʵ�֣�
    virtual void init() = 0;

    // ������ϷԪ��
    virtual void draw() const;

    //����ʱ�ļ����߼�
    void handleInput();

    // �ı��ƶ����򣨷�ֹ180�ȷ���
    void setDirection(SnakeDirection newDir);


    // �л�����״̬
    void toSpeed();

    // �ߵ��ƶ��߼�
    virtual void move();


    // ��ȡ��ǰ���״̬
    bool getIsAlive() const;




    // ��ȡ��ǰ����
    int getScore() const;

    // ��ȡ��߷�
    int getHighScore() const;

    // ���÷���
    void resetScore();

    // ���Ʊ���
    virtual void drawBackground() const;
};