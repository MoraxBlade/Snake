#ifndef COMMON_H
#define COMMON_H
#include <graphics.h> 
#include <vector>
class Snake;//ǰ������
// ����ö��
enum class SnakeDirection { UP, DOWN, LEFT, RIGHT };

// �ϰ����ƶ�����
enum class BarrierDirection { NODIR,UP_LEFT, UP_RIGHT, DOWN_LEFT, DOWN_RIGHT };
inline bool operator==(BarrierDirection a, BarrierDirection b) {
    return static_cast<int>(a) == static_cast<int>(b);
}
inline bool operator!=(BarrierDirection a, BarrierDirection b) {
    return !(a == b);
}
//ʳ��&������ö��
enum class Type { NORMAL, GOLD, WOOD, WATER, FIRE, DIRT };

//�ϰ�������
enum class BarrierType{STATIC,MOVE};
inline bool operator==(BarrierType a, BarrierType b) {
    return static_cast<int>(a) == static_cast<int>(b);
}
inline bool operator!=(BarrierType a, BarrierType b) {
    return !(a == b);
}

// ����ṹ��
struct Point {
    int x;
    int y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}
    bool operator==(const Point& other) const {
        return x == other.x && y == other.y;
    }
};

//ʳ��
//��ײ���
//�������
//����
class Food {
public:
    Type type;
    Point pos;
    

    Food(Type type=Type::NORMAL,Point pos=Point(720,450)):type(type),pos(pos){}
    // ��ȡλ��
    Point getPos() const { return pos; }
    // ��ȡ����
    Type getType() const { return type; }
    //�Ƿ����غ�
    bool IfOverlap(const Point& p, int nodeSize) const;
    //�������
    void generateRandom(int left, int right, int up, int down, int nodeSize,Snake& snake);
    //����
    void draw(PIMAGE foodImg) const;
};


//�ϰ���ṹ��
//�����������
//�ƶ�������Ҫ����ƶ������ƶ�
//�����߼�
//��ײ���
class Barrier {
public:
    BarrierType barrierType;
    Point pos;
    BarrierDirection dir;


    Barrier(BarrierType bType=BarrierType::STATIC,BarrierDirection dir=BarrierDirection::NODIR):
        barrierType(bType),dir(dir),pos(400,400){}
   
   
    // ��ȡλ��
    Point getPos() const { return pos; }
    // ��ȡ����
    BarrierType getType() const { return barrierType; }
    //��ײ
    bool IfOverlap(const Point& p, int nodeSize)const;
    //�������
    void generateRandom(int left, int right, int up, int down,
        int nodeSize, Snake& snake);
    //�ƶ�
    void move(int left, int right, int up, int down, int moveStep, int nodeSize, const std::vector<Barrier>& barriers);
    
    //����
    void draw(PIMAGE foodImg) const;


};

#endif // COMMON_H
