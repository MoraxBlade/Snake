#pragma once
#include "BarrierSnake.h"
#include "Common.h"
#include <map>


class ElementSnake : public BarrierSnake {
protected:
    // 相生关系判断（金生水、水生木、木生火、火生土、土生金）
    static bool isGenerating(Type a, Type b) {
        return(a == Type::WATER && b == Type::GOLD) ||
            (a == Type::WOOD && b == Type::WATER) ||
            (a == Type::FIRE && b == Type::WOOD) ||
            (a == Type::DIRT && b == Type::FIRE) ||
            (a == Type::GOLD && b == Type::DIRT);
    }

    // 相克关系判断（金克木、木克土、土克水、水克火、火克金）
    static bool isRestraining(Type a, Type b) {
        return (a == Type::WOOD && b == Type::GOLD) ||
            (a == Type::DIRT && b == Type::WOOD) ||
            (a == Type::WATER && b == Type::DIRT) ||
            (a == Type::FIRE && b == Type::WATER) ||
            (a == Type::GOLD && b == Type::FIRE);
    }

    std::vector<Food> eleFoods;  // 元素食物集合
    PIMAGE eleFoodImgs[6];        // 存储各元素食物图片（索引对应Type枚举
    map<Type, vector<PIMAGE>> EleSnake;//不同类型的蛇图片，按照索引分别为上下左右身
    PIMAGE EleBackground;  //元素模式背景图片

    // 处理元素效果
    void handleElementEffect(Type foodType, bool isSpeeding);

    // 检查是否与元素食物碰撞
    bool ifEaten();



public:
    ElementSnake();
    ~ElementSnake();

    void genrateElementFood();    // 生成新的元素食物
    void drawBackground() const override;//绘制五行模式的背景（包含规则）
    void init() override;
    void move() override;
    void draw() const override;


};