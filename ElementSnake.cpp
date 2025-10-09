#include "ElementSnake.h"

ElementSnake::ElementSnake():BarrierSnake(){
    //初始化背景
    EleBackground = newimage();
    getimage(EleBackground, "./image/EleBackground.jpg");

    // 初始化元素食物图像（按Type枚举顺序对应）
    eleFoodImgs[0] = newimage(); // NORMAL
    eleFoodImgs[1] = newimage(); // GOLD
    eleFoodImgs[2] = newimage(); // WOOD
    eleFoodImgs[3] = newimage(); // WATER
    eleFoodImgs[4] = newimage(); // FIRE
    eleFoodImgs[5] = newimage(); // DIRT

    // 加载元素食物图像
    getimage(eleFoodImgs[0], "./image/food_normal.png");
    getimage(eleFoodImgs[1], "./image/food_gold.png");
    getimage(eleFoodImgs[2], "./image/food_wood.png");
    getimage(eleFoodImgs[3], "./image/food_water.png");
    getimage(eleFoodImgs[4], "./image/food_fire.png");
    getimage(eleFoodImgs[5], "./image/food_dirt.png");

    //要把普通类也存入
    EleSnake[Type::NORMAL] = { headUp,headDown,headLeft,headRight,bodyImg };


    // 初始化金元素蛇图像（0:上, 1:下, 2:左, 3:右, 4:身体）
    vector<PIMAGE> goldImgs(5);
    goldImgs[0] = newimage(); // 头朝上
    goldImgs[1] = newimage(); // 头朝下
    goldImgs[2] = newimage(); // 头朝左
    goldImgs[3] = newimage(); // 头朝右
    goldImgs[4] = newimage(); // 身体
    getimage(goldImgs[0], "./image/goldHead_up.png");
    getimage(goldImgs[1], "./image/goldHead_down.png");
    getimage(goldImgs[2], "./image/goldHead_left.png");
    getimage(goldImgs[3], "./image/goldHead_right.png");
    getimage(goldImgs[4], "./image/goldBody.png");
    EleSnake[Type::GOLD] = goldImgs;

    // 初始化木元素蛇图像
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

    // 初始化水元素蛇图像
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

    // 初始化火元素蛇图像
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

    // 初始化土元素蛇图像
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
    // 释放元素食物图像
    for (int i = 1; i < 6; ++i) {
        if (eleFoodImgs[i]) {
            delimage(eleFoodImgs[i]);
        }
    }

    // 释放元素蛇身体图像
    auto it = EleSnake.begin();
    ++it;
    // 从第二个键开始遍历
    for (; it != EleSnake.end(); ++it) {
        for (auto img : it->second) {
            delimage(img);
            img = nullptr;
        }
    }
}

//处理食物生成（一次五个）
void ElementSnake::genrateElementFood() {
    eleFoods.clear();
    for (int i = 1; i < 6; ++i) {
        Type foodType = static_cast<Type>(i); // 1-5对应金到土
        Food newFood(foodType);

        // 确保食物不与蛇身、障碍物重叠
        bool valid = false;
        do {
            valid = true;
            newFood.generateRandom(left, right, up, down, nodeSize, *this);

            // 检查与其他元素食物的重叠
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
    BarrierSnake::init(); // 调用父类初始化
    eleFoods.clear();
    genrateElementFood(); // 生成初始元素食物
    SnakeType = Type::NORMAL; // 初始元素类型为普通
}


bool ElementSnake::ifEaten() {
    const Point& head = body.front();
    //先检测元素食物
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

    // 元素相生关系，分数增加更多
    if (isGenerating(SnakeType, foodType)) {
        score += isSpeeding ? 400 : 200;
        body.push_back(body.back()); // 增长2节
        body.push_back(body.back());
    }
    // 元素相克关系，分数减少更多
    else if (isRestraining(SnakeType, foodType)) {
        score = max(0, score - (isSpeeding ? 200 : 100));
        if (body.size() > 3) {
            body.pop_back();
        }
    }
    // 普通元素，正常加分
    else {
        score += 100;
    }

    // 切换蛇的元素属性为所吃食物的属性
    SnakeType = foodType;
    genrateElementFood(); // 生成新的元素食物
}

void ElementSnake::move(){
    if (!isAlive) return;
    BarrierSnake::move();//调用父类移动逻辑
    ifEaten();

}

void ElementSnake::draw() const{
    if (!isAlive) return;
    drawBackground();

    // 绘制分数1060-70
    settextcolor(BLACK);
    setfont(-40, 0, "微软雅黑");//负数表示像素
    setbkmode(0);
    char scoreText[10000];
    sprintf(scoreText, "%d", score);
    outtextxy(1060, 60, scoreText);

    // 获取当前元素类型对应的图片集合
    auto it = EleSnake.find(SnakeType);
    const auto& currentImgs = it->second;
    const Point& head = body.front();

    // 根据当前方向绘制对应元素的蛇头
    switch (dir) {
    case SnakeDirection::UP:    putimage(head.x, head.y, currentImgs[0]); break;
    case SnakeDirection::DOWN:  putimage(head.x, head.y, currentImgs[1]); break;
    case SnakeDirection::LEFT:  putimage(head.x, head.y, currentImgs[2]); break;
    case SnakeDirection::RIGHT: putimage(head.x, head.y, currentImgs[3]); break;
    }

    // 绘制对应元素的身体
    PIMAGE bodyImg = currentImgs[4];
    for (size_t i = 1; i < body.size(); ++i) {
        putimage(body[i].x, body[i].y, bodyImg);
    }

    // 绘制元素食物
    for (const auto& f : eleFoods) {
        int imgIndex = static_cast<int>(f.type);
        f.draw(eleFoodImgs[imgIndex]);
    }

    // 绘制尾部食物
    for (const auto& tailFood : TailFood) {
        int imgIndex = static_cast<int>(tailFood.type);
        tailFood.draw(eleFoodImgs[imgIndex]);
    }

    // 绘制障碍物
    for (const auto& b : staticBarriers) {
        b.draw(staticB);
    }
    for (const auto& b : moveBarriers) {
        b.draw(moveB);
    }
}


// 绘制背景
void ElementSnake::drawBackground() const {
    if (EleBackground != nullptr) {
        putimage(0, 0, EleBackground);
    }
    else {
        setbkcolor(WHITE);
        cleardevice();
    }
}