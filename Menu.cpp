#include "Menu.h"
#include <fstream>
#include <string>
#include <iostream>
using namespace std;
ImageButton::ImageButton(double x, double y, PIMAGE& nor, PIMAGE& sel)
	: x(x), y(y), normalImg(nor),selectedImg(sel),isSelected(false) {}

ImageButton::~ImageButton() {
	// �ͷ�ͼƬ��Դ

	
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
	// ������а�ť��ѡ��״̬
	for (auto& btn : mainButtons) {
		btn.isSelected = false;
	}
	for (auto& btn : modeButtons) {
		btn.isSelected = false;
	}

	// ���õ�ǰѡ�еİ�ť
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
	getimage(menu, "./image/menu.jpg");//�˵�
	getimage(GuideImg, "./image/GuideImg.jpg");//����
	getimage(ModeMenu, "./image/ModeMenu.jpg");//ģʽѡ��

	//ģʽѡ��ť
	PIMAGE GameMode_unchoose = newimage();
	getimage(GameMode_unchoose, "./image/GameMode_unchoose.png");
	PIMAGE GameMode_choose = newimage();
	getimage(GameMode_choose, "./image/GameMode_choose.png");
	ImageButton GameMode (594.5, 267.5, GameMode_unchoose, GameMode_choose);
	mainButtons.push_back(GameMode);
	
	// �����ֲᰴť
	PIMAGE Guide_unchoose = newimage();
	getimage(Guide_unchoose, "./image/Guide_unchoose.png");
	PIMAGE Guide_choose = newimage();
	getimage(Guide_choose, "./image/Guide_choose.png");
	ImageButton Guide(594.5, 421.5, Guide_unchoose, Guide_choose);
	mainButtons.push_back(Guide);

	// �رհ�ť
	PIMAGE Close_unchoose = newimage();
	getimage(Close_unchoose, "./image/close_unchoose.png");
	PIMAGE Close_choose = newimage();
	getimage(Close_choose, "./image/close_choose.png");
	ImageButton Close(594.5, 575.5, Close_unchoose, Close_choose);
	mainButtons.push_back(Close);

	// ��ͨģʽ��ť
	PIMAGE Normal_unchoose = newimage();
	getimage(Normal_unchoose, "./image/normal_unchoose.png");
	PIMAGE Normal_choose = newimage();
	getimage(Normal_choose, "./image/normal_choose.png");
	ImageButton Normal(594.5, 267.5, Normal_unchoose, Normal_choose);
	modeButtons.push_back(Normal);

	// �ϰ�ģʽ��ť
	PIMAGE Barrier_unchoose = newimage();
	getimage(Barrier_unchoose, "./image/barrier_unchoose.png");
	PIMAGE Barrier_choose = newimage();
	getimage(Barrier_choose, "./image/barrier_choose.png");
	ImageButton Barrier(594.5, 421.5, Barrier_unchoose, Barrier_choose);
	modeButtons.push_back(Barrier);

	// ����ģʽ��ť
	PIMAGE Elements_unchoose = newimage();
	getimage(Elements_unchoose, "./image/elements_unchoose.png");
	PIMAGE Elements_choose = newimage();
	getimage(Elements_choose, "./image/elements_choose.png");
	ImageButton Elements(594.5, 575.5, Elements_unchoose, Elements_choose);
	modeButtons.push_back(Elements);


	updateButtonSelection();//���µ�ǰ��ť״̬
}

Menu::~Menu() {
	delimage(menu);
	delimage(GuideImg);
	delimage(ModeMenu);
}

bool Menu::handleInput(bool& running) {
	bool needRedraw = false; // ����Ƿ���Ҫ�ػ����

	if (kbhit()) { // �����м�������ʱִ��
		char key = getch();

		if (currentState == HELP_SCREEN) {
			// �������棺��Enter/ESC�������˵���״̬�仯����Ҫ�ػ棩
			if (key == 13 || key == 27) {
				enterMainMenu();
				needRedraw = true;
			}
		}
		else {
			// �˵���������W/S�л���ť��ѡ��״̬�仯����Ҫ�ػ棩
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
			else if (key == 13) { // Enterȷ�ϣ�״̬�仯����Ҫ�ػ棩
				if (currentState == MAIN_MENU) {
					switch (selectedBtn) {
					case 0: enterModeSelection(); break; // ����ģʽѡ��
					case 1: enterHelpScreen(); break;    // �����������
					case 2: running = false; break;      // �˳��������ػ棩
					}
					if (selectedBtn != 2) needRedraw = true; // �����˳�����Ҫ�ػ�
				}
				else { // ģʽѡ�����
					switch (selectedBtn) {
					case 0: cout << "ѡ����ͨģʽ" << endl; break;
					case 1: cout << "ѡ���ϰ�ģʽ" << endl; break;
					case 2: cout << "ѡ������ģʽ" << endl; break;
					}
					enterMainMenu(); // �������˵�����Ҫ�ػ�
					needRedraw = true;
				}
			}
			else if (key == 27) { // ESC���أ�״̬�仯����Ҫ�ػ棩
				if (currentState == MODE_SELECTION) {
					enterMainMenu();
					needRedraw = true;
				}
				else {
					running = false; // ���˵���ESC�˳��������ػ�
				}
			}
		}
	}
	return needRedraw;
}

void Menu::draw(int currentMode) {
	cleardevice(); // ������Ҫ�ػ�ʱ������Ļ�����ⷴ����յ�����˸

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