#ifndef MENU_H
#define MENU_H

#include <graphics.h>
#include <vector>
#include <string>
using namespace std;
// ��ť�� - ʹ��ͼƬ
class ImageButton {
public:
    int x, y;
    bool isSelected;
    PIMAGE normalImg;   // ����״̬ͼƬ
    PIMAGE selectedImg; // ѡ��״̬ͼƬ

    ImageButton(double x, double y, PIMAGE& nor, PIMAGE& sel);

    ~ImageButton();

    // ���ư�ť
    void draw();
};

// �˵���
class Menu {
public:


    int selectedBtn;
    bool showHelp;
    PIMAGE menu;
    PIMAGE GuideImg;    // ˵��ͼƬ
    PIMAGE ModeMenu;//ģʽѡ��ı���

    // �˵�״̬ö��
    enum MenuState { MAIN_MENU, MODE_SELECTION, HELP_SCREEN };
    MenuState currentState;

    // ���°�ťѡ��״̬
    void updateButtonSelection();

    // ���ذ���ͼƬ


    // ���˵���ť
    std::vector<ImageButton> mainButtons;
    // ģʽѡ��ť
    std::vector<ImageButton> modeButtons;

    // �˵�ѡ��ö��
    enum MenuOption {
        MENU,SELECT_MODE, GAME_HELP, EXIT_GAME,
        MODE_NORMAL, MODE_BARRIER, MODE_ELEMENTS
    };

    Menu();
    ~Menu();

    // ����˵�����
    bool handleInput(bool& running);

    // ���Ʋ˵�
    void draw(int currentMode);

    // �л���ģʽѡ�����
    void enterModeSelection() {
        currentState = MODE_SELECTION;
        selectedBtn = 0;
        updateButtonSelection();
    }

    // �л������˵�
    void enterMainMenu() {
        currentState = MAIN_MENU;
        selectedBtn = 0;
        updateButtonSelection();
    }

    // �л�����������
    void enterHelpScreen() {
        currentState = HELP_SCREEN;
    }


};

#endif // MENU_H
