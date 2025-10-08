#pragma once
#include "Snake.h"
class BarrierSnake :
    public Snake
{
public:
    //�ϰ����̬+�ƶ���
    vector<Barrier> staticBarriers;
    vector<Barrier> moveBarriers;
    int barrierCount=0;
    clock_t lastBarrierCreateTime=0;//�ϴ��ϰ�������ʱ���
    //�ϰ���ͼƬ
    PIMAGE staticB;
    PIMAGE moveB;
    const int BARRIER_CREATE_INTERVAL = 10000;  // �ϰ������ɼ��

    // ���λ���Ƿ����ϰ����ص�
    bool isPositionOverlapWithBarriers(const Point& pos) const;
    // ���캯��
    BarrierSnake();

    // ��������
    ~BarrierSnake();

    //������ɾ�̬�ϰ�
    void generateStaticBarrier();

    //������ɶ�̬�ϰ�
    void generateMoveBarrier();


    // ��ʼ����Ϸ
    void init() override;

    //�����ƶ��߼�
    void move() override;

    //���ػ����߼�
    void draw()const override;

};

