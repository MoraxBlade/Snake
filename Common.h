#ifndef COMMON_H
#define COMMON_H
#include <graphics.h> 
#include <vector>
class Snake;//前向声明
// 方向枚举
enum class SnakeDirection { UP, DOWN, LEFT, RIGHT };

// 障碍物移动方向
enum class BarrierDirection { NODIR,UP_LEFT, UP_RIGHT, DOWN_LEFT, DOWN_RIGHT };
inline bool operator==(BarrierDirection a, BarrierDirection b) {
    return static_cast<int>(a) == static_cast<int>(b);
}
inline bool operator!=(BarrierDirection a, BarrierDirection b) {
    return !(a == b);
}
//食物&蛇种类枚举
enum class Type { NORMAL, GOLD, WOOD, WATER, FIRE, DIRT };

//障碍物种类
enum class BarrierType{STATIC,MOVE};
inline bool operator==(BarrierType a, BarrierType b) {
    return static_cast<int>(a) == static_cast<int>(b);
}
inline bool operator!=(BarrierType a, BarrierType b) {
    return !(a == b);
}

// 坐标结构体
struct Point {
    int x;
    int y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

//食物
//碰撞检测
//随机生成
//绘制
class Food {
public:
    Type type;
    Point pos;
    

    Food(Type type=Type::NORMAL,Point pos=Point(720,450)):type(type),pos(pos){}
    // 获取位置
    Point getPos() const { return pos; }
    // 获取类型
    Type getType() const { return type; }
    //是否有重合
    bool IfOverlap(const Point& p, int nodeSize) const;
    //随机生成
    void generateRandom(int left, int right, int up, int down, int nodeSize,Snake& snake);
    //绘制
    void draw(PIMAGE foodImg) const;
};


//障碍物结构体
//随机生成坐标
//移动类型需要随机移动方向并移动
//绘制逻辑
//碰撞检测
class Barrier {
public:
    BarrierType barrierType;
    Point pos;
    BarrierDirection dir;


    Barrier(BarrierType bType=BarrierType::STATIC,BarrierDirection dir=BarrierDirection::NODIR):
        barrierType(bType),dir(dir),pos(400,400){}
   
   
    // 获取位置
    Point getPos() const { return pos; }
    // 获取类型
    BarrierType getType() const { return barrierType; }
    //碰撞
    bool IfOverlap(const Point& p, int nodeSize)const;
    //随机生成
    void generateRandom(int left, int right, int up, int down,
        int nodeSize, Snake& snake);
    //移动
    void move(int left, int right, int up, int down, int moveStep, int nodeSize, const std::vector<Barrier>& barriers);
    
    //绘制
    void draw(PIMAGE foodImg) const;


};

#endif // COMMON_H
