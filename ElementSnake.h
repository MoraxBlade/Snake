#pragma once
#include "BarrierSnake.h"
#include "Common.h"
#include <map>


class ElementSnake : public BarrierSnake {
protected:
    // ������ϵ�жϣ�����ˮ��ˮ��ľ��ľ���𡢻�������������
    static bool isGenerating(Type a, Type b) {
        return(a == Type::WATER && b == Type::GOLD) ||
            (a == Type::WOOD && b == Type::WATER) ||
            (a == Type::FIRE && b == Type::WOOD) ||
            (a == Type::DIRT && b == Type::FIRE) ||
            (a == Type::GOLD && b == Type::DIRT);
    }

    // ��˹�ϵ�жϣ����ľ��ľ����������ˮ��ˮ�˻𡢻�˽�
    static bool isRestraining(Type a, Type b) {
        return (a == Type::WOOD && b == Type::GOLD) ||
            (a == Type::DIRT && b == Type::WOOD) ||
            (a == Type::WATER && b == Type::DIRT) ||
            (a == Type::FIRE && b == Type::WATER) ||
            (a == Type::GOLD && b == Type::FIRE);
    }

    std::vector<Food> eleFoods;  // Ԫ��ʳ�Ｏ��
    PIMAGE eleFoodImgs[6];        // �洢��Ԫ��ʳ��ͼƬ��������ӦTypeö��
    map<Type, vector<PIMAGE>> EleSnake;//��ͬ���͵���ͼƬ�����������ֱ�Ϊ����������
    PIMAGE EleBackground;  //Ԫ��ģʽ����ͼƬ

    // ����Ԫ��Ч��
    void handleElementEffect(Type foodType, bool isSpeeding);

    // ����Ƿ���Ԫ��ʳ����ײ
    bool ifEaten();



public:
    ElementSnake();
    ~ElementSnake();

    void genrateElementFood();    // �����µ�Ԫ��ʳ��
    void drawBackground() const override;//��������ģʽ�ı�������������
    void init() override;
    void move() override;
    void draw() const override;


};