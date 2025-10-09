#include "ElementSnake.h"

ElementSnake::ElementSnake():BarrierSnake(){
    //��ʼ������
    EleBackground = newimage();
    getimage(EleBackground, "./image/EleBackground.jpg");

    // ��ʼ��Ԫ��ʳ��ͼ�񣨰�Typeö��˳���Ӧ��
    eleFoodImgs[0] = newimage(); // NORMAL
    eleFoodImgs[1] = newimage(); // GOLD
    eleFoodImgs[2] = newimage(); // WOOD
    eleFoodImgs[3] = newimage(); // WATER
    eleFoodImgs[4] = newimage(); // FIRE
    eleFoodImgs[5] = newimage(); // DIRT

    // ����Ԫ��ʳ��ͼ��
    getimage(eleFoodImgs[0], "./image/food_normal.png");
    getimage(eleFoodImgs[1], "./image/food_gold.png");
    getimage(eleFoodImgs[2], "./image/food_wood.png");
    getimage(eleFoodImgs[3], "./image/food_water.png");
    getimage(eleFoodImgs[4], "./image/food_fire.png");
    getimage(eleFoodImgs[5], "./image/food_dirt.png");

    //Ҫ����ͨ��Ҳ����
    EleSnake[Type::NORMAL] = { headUp,headDown,headLeft,headRight,bodyImg };


    // ��ʼ����Ԫ����ͼ��0:��, 1:��, 2:��, 3:��, 4:���壩
    vector<PIMAGE> goldImgs(5);
    goldImgs[0] = newimage(); // ͷ����
    goldImgs[1] = newimage(); // ͷ����
    goldImgs[2] = newimage(); // ͷ����
    goldImgs[3] = newimage(); // ͷ����
    goldImgs[4] = newimage(); // ����
    getimage(goldImgs[0], "./image/goldHead_up.png");
    getimage(goldImgs[1], "./image/goldHead_down.png");
    getimage(goldImgs[2], "./image/goldHead_left.png");
    getimage(goldImgs[3], "./image/goldHead_right.png");
    getimage(goldImgs[4], "./image/goldBody.png");
    EleSnake[Type::GOLD] = goldImgs;

    // ��ʼ��ľԪ����ͼ��
    vector<PIMAGE> woodImgs(5);
    woodImgs[0] = newimage();
    woodImgs[1] = newimage();
    woodImgs[2] = newimage();
    woodImgs[3] = newimage();
    woodImgs[4] = newimage();
    getimage(woodImgs[0], "./image/woodHead_up.png");
    getimage(woodImgs[1], "./image/woodHead_down.png");
    getimage(woodImgs[2], "./image/woodHead_left.png");
    getimage(woodImgs[3], "./image/woodHead_right.png");
    getimage(woodImgs[4], "./image/woodBody.png");
    EleSnake[Type::WOOD] = woodImgs;

    // ��ʼ��ˮԪ����ͼ��
    vector<PIMAGE> waterImgs(5);
    waterImgs[0] = newimage();
    waterImgs[1] = newimage();
    waterImgs[2] = newimage();
    waterImgs[3] = newimage();
    waterImgs[4] = newimage();
    getimage(waterImgs[0], "./image/waterHead_up.png");
    getimage(waterImgs[1], "./image/waterHead_down.png");
    getimage(waterImgs[2], "./image/waterHead_left.png");
    getimage(waterImgs[3], "./image/waterHead_right.png");
    getimage(waterImgs[4], "./image/waterBody.png");
    EleSnake[Type::WATER] = waterImgs;

    // ��ʼ����Ԫ����ͼ��
    vector<PIMAGE> fireImgs(5);
    fireImgs[0] = newimage();
    fireImgs[1] = newimage();
    fireImgs[2] = newimage();
    fireImgs[3] = newimage();
    fireImgs[4] = newimage();
    getimage(fireImgs[0], "./image/fireHead_up.png");
    getimage(fireImgs[1], "./image/fireHead_down.png");
    getimage(fireImgs[2], "./image/fireHead_left.png");
    getimage(fireImgs[3], "./image/fireHead_right.png");
    getimage(fireImgs[4], "./image/fireBody.png");
    EleSnake[Type::FIRE] = fireImgs;

    // ��ʼ����Ԫ����ͼ��
    vector<PIMAGE> dirtImgs(5);
    dirtImgs[0] = newimage();
    dirtImgs[1] = newimage();
    dirtImgs[2] = newimage();
    dirtImgs[3] = newimage();
    dirtImgs[4] = newimage();
    getimage(dirtImgs[0], "./image/dirtHead_up.png");
    getimage(dirtImgs[1], "./image/dirtHead_down.png");
    getimage(dirtImgs[2], "./image/dirtHead_left.png");
    getimage(dirtImgs[3], "./image/dirtHead_right.png");
    getimage(dirtImgs[4], "./image/dirtBody.png");
    EleSnake[Type::DIRT] = dirtImgs;
}

ElementSnake::~ElementSnake(){
    // �ͷ�Ԫ��ʳ��ͼ��
    for (int i = 1; i < 6; ++i) {
        if (eleFoodImgs[i]) {
            delimage(eleFoodImgs[i]);
        }
    }

    // �ͷ�Ԫ��������ͼ��
    auto it = EleSnake.begin();
    ++it;
    // �ӵڶ�������ʼ����
    for (; it != EleSnake.end(); ++it) {
        for (auto img : it->second) {
            delimage(img);
            img = nullptr;
        }
    }
}

//����ʳ�����ɣ�һ�������
void ElementSnake::genrateElementFood() {
    eleFoods.clear();
    for (int i = 1; i < 6; ++i) {
        Type foodType = static_cast<Type>(i); // 1-5��Ӧ����
        Food newFood(foodType);

        // ȷ��ʳ�ﲻ�������ϰ����ص�
        bool valid = false;
        do {
            valid = true;
            newFood.generateRandom(left, right, up, down, nodeSize, *this);

            // ���������Ԫ��ʳ����ص�
            for (const auto& f : eleFoods) {
                if (newFood.IfOverlap(f.pos, nodeSize)) {
                    valid = false;
                    break;
                }
            }
        } while (!valid);

        eleFoods.push_back(newFood);
    }
}

void ElementSnake::init(){
    BarrierSnake::init(); // ���ø����ʼ��
    eleFoods.clear();
    genrateElementFood(); // ���ɳ�ʼԪ��ʳ��
    SnakeType = Type::NORMAL; // ��ʼԪ������Ϊ��ͨ
}


bool ElementSnake::ifEaten() {
    const Point& head = body.front();
    //�ȼ��Ԫ��ʳ��
    for (size_t i = 0; i < eleFoods.size(); ++i) {
        if (eleFoods[i].IfOverlap(head, nodeSize)) {
            Type foodType = eleFoods[i].type;
            eleFoods.erase(eleFoods.begin() + i);
            handleElementEffect(foodType,isSpeeding);
            return true;
        }
    }
    return false;
}

void ElementSnake::handleElementEffect(Type foodType, bool isSpeeding) {

    // Ԫ��������ϵ���������Ӹ���
    if (isGenerating(SnakeType, foodType)) {
        score += isSpeeding ? 400 : 200;
        body.push_back(body.back()); // ����2��
        body.push_back(body.back());
    }
    // Ԫ����˹�ϵ���������ٸ���
    else if (isRestraining(SnakeType, foodType)) {
        score = max(0, score - (isSpeeding ? 200 : 100));
        if (body.size() > 3) {
            body.pop_back();
        }
    }
    // ��ͨԪ�أ������ӷ�
    else {
        score += 100;
    }

    // �л��ߵ�Ԫ������Ϊ����ʳ�������
    SnakeType = foodType;
    genrateElementFood(); // �����µ�Ԫ��ʳ��
}

void ElementSnake::move(){
    if (!isAlive) return;
    BarrierSnake::move();//���ø����ƶ��߼�
    ifEaten();

}

void ElementSnake::draw() const{
    if (!isAlive) return;
    drawBackground();

    // ���Ʒ���1060-70
    settextcolor(BLACK);
    setfont(-40, 0, "΢���ź�");//������ʾ����
    setbkmode(0);
    char scoreText[10000];
    sprintf(scoreText, "%d", score);
    outtextxy(1060, 60, scoreText);

    // ��ȡ��ǰԪ�����Ͷ�Ӧ��ͼƬ����
    auto it = EleSnake.find(SnakeType);
    const auto& currentImgs = it->second;
    const Point& head = body.front();

    // ���ݵ�ǰ������ƶ�ӦԪ�ص���ͷ
    switch (dir) {
    case SnakeDirection::UP:    putimage(head.x, head.y, currentImgs[0]); break;
    case SnakeDirection::DOWN:  putimage(head.x, head.y, currentImgs[1]); break;
    case SnakeDirection::LEFT:  putimage(head.x, head.y, currentImgs[2]); break;
    case SnakeDirection::RIGHT: putimage(head.x, head.y, currentImgs[3]); break;
    }

    // ���ƶ�ӦԪ�ص�����
    PIMAGE bodyImg = currentImgs[4];
    for (size_t i = 1; i < body.size(); ++i) {
        putimage(body[i].x, body[i].y, bodyImg);
    }

    // ����Ԫ��ʳ��
    for (const auto& f : eleFoods) {
        int imgIndex = static_cast<int>(f.type);
        f.draw(eleFoodImgs[imgIndex]);
    }

    // ����β��ʳ��
    for (const auto& tailFood : TailFood) {
        int imgIndex = static_cast<int>(tailFood.type);
        tailFood.draw(eleFoodImgs[imgIndex]);
    }

    // �����ϰ���
    for (const auto& b : staticBarriers) {
        b.draw(staticB);
    }
    for (const auto& b : moveBarriers) {
        b.draw(moveB);
    }
}


// ���Ʊ���
void ElementSnake::drawBackground() const {
    if (EleBackground != nullptr) {
        putimage(0, 0, EleBackground);
    }
    else {
        setbkcolor(WHITE);
        cleardevice();
    }
}