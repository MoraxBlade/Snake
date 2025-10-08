#include "Menu.h"
#include <fstream>
#include <string>
#include <iostream>
using namespace std;
ImageButton::ImageButton(double x, double y, PIMAGE& nor, PIMAGE& sel)
	: x(x), y(y), normalImg(nor),selectedImg(sel),isSelected(false) {}

ImageButton::~ImageButton() {
	// 释放图片资源

	
}

void ImageButton::draw() {
	if (isSelected) {
		putimage(x, y, selectedImg);
	}
	else {
		putimage(x, y, normalImg);
	}
	
}
void Menu::updateButtonSelection() {
	// 清除所有按钮的选中状态
	for (auto& btn : mainButtons) {
		btn.isSelected = false;
	}
	for (auto& btn : modeButtons) {
		btn.isSelected = false;
	}

	// 设置当前选中的按钮
	if (currentState == MAIN_MENU && selectedBtn < mainButtons.size()) {
		mainButtons[selectedBtn].isSelected = true;
	}
	else if (currentState == MODE_SELECTION && selectedBtn < modeButtons.size()) {
		modeButtons[selectedBtn].isSelected = true;
	}
}

Menu::Menu() :selectedBtn(0), showHelp(false), currentState(MAIN_MENU) {
	menu = newimage();
	GuideImg = newimage();
	ModeMenu = newimage();
	getimage(menu, "./image/menu.jpg");//菜单
	getimage(GuideImg, "./image/GuideImg.jpg");//帮助
	getimage(ModeMenu, "./image/ModeMenu.jpg");//模式选择

	//模式选择按钮
	PIMAGE GameMode_unchoose = newimage();
	getimage(GameMode_unchoose, "./image/GameMode_unchoose.png");
	PIMAGE GameMode_choose = newimage();
	getimage(GameMode_choose, "./image/GameMode_choose.png");
	ImageButton GameMode (594.5, 267.5, GameMode_unchoose, GameMode_choose);
	mainButtons.push_back(GameMode);
	
	// 操作手册按钮
	PIMAGE Guide_unchoose = newimage();
	getimage(Guide_unchoose, "./image/Guide_unchoose.png");
	PIMAGE Guide_choose = newimage();
	getimage(Guide_choose, "./image/Guide_choose.png");
	ImageButton Guide(594.5, 421.5, Guide_unchoose, Guide_choose);
	mainButtons.push_back(Guide);

	// 关闭按钮
	PIMAGE Close_unchoose = newimage();
	getimage(Close_unchoose, "./image/close_unchoose.png");
	PIMAGE Close_choose = newimage();
	getimage(Close_choose, "./image/close_choose.png");
	ImageButton Close(594.5, 575.5, Close_unchoose, Close_choose);
	mainButtons.push_back(Close);

	// 普通模式按钮
	PIMAGE Normal_unchoose = newimage();
	getimage(Normal_unchoose, "./image/normal_unchoose.png");
	PIMAGE Normal_choose = newimage();
	getimage(Normal_choose, "./image/normal_choose.png");
	ImageButton Normal(594.5, 267.5, Normal_unchoose, Normal_choose);
	modeButtons.push_back(Normal);

	// 障碍模式按钮
	PIMAGE Barrier_unchoose = newimage();
	getimage(Barrier_unchoose, "./image/barrier_unchoose.png");
	PIMAGE Barrier_choose = newimage();
	getimage(Barrier_choose, "./image/barrier_choose.png");
	ImageButton Barrier(594.5, 421.5, Barrier_unchoose, Barrier_choose);
	modeButtons.push_back(Barrier);

	// 五行模式按钮
	PIMAGE Elements_unchoose = newimage();
	getimage(Elements_unchoose, "./image/elements_unchoose.png");
	PIMAGE Elements_choose = newimage();
	getimage(Elements_choose, "./image/elements_choose.png");
	ImageButton Elements(594.5, 575.5, Elements_unchoose, Elements_choose);
	modeButtons.push_back(Elements);


	updateButtonSelection();//更新当前按钮状态
}

Menu::~Menu() {
	delimage(menu);
	delimage(GuideImg);
	delimage(ModeMenu);
}

bool Menu::handleInput(bool& running) {
	bool needRedraw = false; // 标记是否需要重绘界面

	if (kbhit()) { // 仅在有键盘输入时执行
		char key = getch();

		if (currentState == HELP_SCREEN) {
			// 帮助界面：按Enter/ESC返回主菜单（状态变化，需要重绘）
			if (key == 13 || key == 27) {
				enterMainMenu();
				needRedraw = true;
			}
		}
		else {
			// 菜单导航：按W/S切换按钮（选中状态变化，需要重绘）
			if (key == 'w' || key == 'W') {
				selectedBtn = (selectedBtn - 1 + 3) % 3;
				updateButtonSelection();
				needRedraw = true;
			}
			else if (key == 's' || key == 'S') {
				selectedBtn = (selectedBtn + 1) % 3;
				updateButtonSelection();
				needRedraw = true;
			}
			else if (key == 13) { // Enter确认（状态变化，需要重绘）
				if (currentState == MAIN_MENU) {
					switch (selectedBtn) {
					case 0: enterModeSelection(); break; // 进入模式选择
					case 1: enterHelpScreen(); break;    // 进入帮助界面
					case 2: running = false; break;      // 退出（无需重绘）
					}
					if (selectedBtn != 2) needRedraw = true; // 除了退出，都要重绘
				}
				else { // 模式选择界面
					switch (selectedBtn) {
					case 0: cout << "选择普通模式" << endl; break;
					case 1: cout << "选择障碍模式" << endl; break;
					case 2: cout << "选择五行模式" << endl; break;
					}
					enterMainMenu(); // 返回主菜单，需要重绘
					needRedraw = true;
				}
			}
			else if (key == 27) { // ESC返回（状态变化，需要重绘）
				if (currentState == MODE_SELECTION) {
					enterMainMenu();
					needRedraw = true;
				}
				else {
					running = false; // 主菜单按ESC退出，无需重绘
				}
			}
		}
	}
	return needRedraw;
}

void Menu::draw(int currentMode) {
	cleardevice(); // 仅在需要重绘时清理屏幕，避免反复清空导致闪烁

	if (currentState == MAIN_MENU && menu != NULL) {
		putimage(0, 0, menu);
		for (auto& btn : mainButtons) btn.draw();
	}
	else if (currentState == MODE_SELECTION && ModeMenu != NULL) {
		putimage(0, 0, ModeMenu);
		for (auto& btn : modeButtons) btn.draw();
	}
	else if (currentState == HELP_SCREEN && GuideImg != NULL) {
		putimage(0, 0, GuideImg);
	}
}