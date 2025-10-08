#ifndef MENU_H
#define MENU_H

#include <graphics.h>
#include <vector>
#include <string>
using namespace std;
// 按钮类 - 使用图片
class ImageButton {
public:
    int x, y;
    bool isSelected;
    PIMAGE normalImg;   // 正常状态图片
    PIMAGE selectedImg; // 选中状态图片

    ImageButton(double x, double y, PIMAGE& nor, PIMAGE& sel);

    ~ImageButton();

    // 绘制按钮
    void draw();
};

// 菜单类
class Menu {
public:


    int selectedBtn;
    bool showHelp;
    PIMAGE menu;
    PIMAGE GuideImg;    // 说明图片
    PIMAGE ModeMenu;//模式选择的背景

    // 菜单状态枚举
    enum MenuState { MAIN_MENU, MODE_SELECTION, HELP_SCREEN };
    MenuState currentState;

    // 更新按钮选择状态
    void updateButtonSelection();

    // 加载帮助图片


    // 主菜单按钮
    std::vector<ImageButton> mainButtons;
    // 模式选择按钮
    std::vector<ImageButton> modeButtons;

    // 菜单选项枚举
    enum MenuOption {
        MENU,SELECT_MODE, GAME_HELP, EXIT_GAME,
        MODE_NORMAL, MODE_BARRIER, MODE_ELEMENTS
    };

    Menu();
    ~Menu();

    // 处理菜单输入
    bool handleInput(bool& running);

    // 绘制菜单
    void draw(int currentMode);

    // 切换到模式选择界面
    void enterModeSelection() {
        currentState = MODE_SELECTION;
        selectedBtn = 0;
        updateButtonSelection();
    }

    // 切换到主菜单
    void enterMainMenu() {
        currentState = MAIN_MENU;
        selectedBtn = 0;
        updateButtonSelection();
    }

    // 切换到帮助界面
    void enterHelpScreen() {
        currentState = HELP_SCREEN;
    }


};

#endif // MENU_H
