#pragma once
#include "Snake.h"

class NormalSnake :
    public Snake
{
public:
    // ���캯��
    NormalSnake();

    // ��������
    ~NormalSnake() override;

    // ��ʼ����Ϸ
    void init() override;


};

