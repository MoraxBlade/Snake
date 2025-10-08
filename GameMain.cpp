#include "Menu.h"
#include "NormalSnake.h"
#include "BarrierSnake.h"
#include "ElementSnake.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <conio.h>
using namespace std;
// 游戏状态枚举
enum GameState { MENU, NORMAL_GAME,BARRIER_GAME,ELEMENTS_GAME, EXIT };

int main() {
    srand((unsigned int)time(nullptr));
    initgraph(1440, 900);
    setcaption("贪吃蛇");

    bool running = true;
    GameState currentState = MENU;
    Menu menu;
    NormalSnake normalSnake;  // 普通模式蛇实例
    BarrierSnake barrierSnake;//障碍模式实例
    ElementSnake elementSnake;//元素模式实例
    // 初始绘制菜单
    menu.draw(0);

    while (running) {
        if (currentState == MENU) {
            // 处理菜单输入
            bool needRedraw = menu.handleInput(running);
            if (needRedraw) {
                menu.draw(0);
                Sleep(1);
            }

            // 检测模式选择菜单的确认
            if (menu.currentState == Menu::MODE_SELECTION) {
                if (kbhit() && getch() == 13) {  // 按Enter确认选择
                    switch (menu.selectedBtn) {
                    case 0:  // 普通模式
                        currentState = NORMAL_GAME;
                        normalSnake.init();  // 初始化普通蛇
                        break;
                    case 1:  // 障碍模式
                        currentState = BARRIER_GAME;
                        barrierSnake.init();
                        // 后续添加障碍模式蛇的初始化
                        break;
                    case 2:  // 元素模式
                        currentState = ELEMENTS_GAME;
                        elementSnake.init();
                        break;
                    }
                }
            }
        }
        else if (currentState == NORMAL_GAME) {
            // 处理游戏输入（优先于移动，避免输入延迟）
            normalSnake.handleInput();

            // 移动蛇并绘制
            normalSnake.move();
            normalSnake.draw();

            // 检测蛇是否死亡
            if (!normalSnake.getIsAlive()) {
                // 显示死亡信息和分数
                settextcolor(RED);
                setfont(-60, 0, "微软雅黑");
                outtextxy(500, 400, "游戏结束！按ESC后回车返回菜单");

                // 显示最终分数
                settextcolor(RED);
                setfont(-40, 0, "微软雅黑");
                char scoreText[100];
                sprintf(scoreText, "最终分数: %d  最高分: %d",
                    normalSnake.getScore(), normalSnake.getHighScore());
                outtextxy(500, 500, scoreText);

                // 等待ESC键返回菜单
                while (true) {
                    if (kbhit() && getch() == 27) {
                        currentState = MENU;
                        menu.enterMainMenu();
                        menu.draw(0);
                        break;
                    }
                    Sleep(5);
                }
            }
        }
        
        else if (currentState == BARRIER_GAME) {
            // 障碍模式游戏逻辑
            barrierSnake.handleInput();
            barrierSnake.move();
            barrierSnake.draw();



            // 检查游戏是否结束
            if (!barrierSnake.getIsAlive()) {
                // 显示死亡信息和分数
                settextcolor(RED);
                setfont(-60, 0, "微软雅黑");
                outtextxy(500, 400, "游戏结束！按ESC后回车返回菜单");

                // 显示最终分数
                settextcolor(RED);
                setfont(-40, 0, "微软雅黑");
                char scoreText[100];
                sprintf(scoreText, "最终分数: %d  最高分: %d",
                    barrierSnake.getScore(), barrierSnake.getHighScore());
                outtextxy(500, 500, scoreText);

                // 等待ESC键返回菜单
                while (true) {
                    if (kbhit() && getch() == 27) {
                        currentState = MENU;
                        menu.enterMainMenu();
                        menu.draw(0);
                        break;
                    }
                    Sleep(5);
                }
            }

        }
        else if (currentState == ELEMENTS_GAME) {
            // 元素模式游戏逻辑
            elementSnake.handleInput();
            elementSnake.move();
            elementSnake.draw();



            // 检查游戏是否结束
            if (!elementSnake.getIsAlive()) {
                // 显示死亡信息和分数
                settextcolor(RED);
                setfont(-60, 0, "微软雅黑");
                outtextxy(500, 400, "游戏结束！按ESC后回车返回菜单");

                // 显示最终分数
                settextcolor(RED);
                setfont(-40, 0, "微软雅黑");
                char scoreText[100];
                sprintf(scoreText, "最终分数: %d  最高分: %d",
                    elementSnake.getScore(), elementSnake.getHighScore());
                outtextxy(500, 500, scoreText);

                // 等待ESC键返回菜单
                while (true) {
                    if (kbhit() && getch() == 27) {
                        currentState = MENU;
                        menu.enterMainMenu();
                        menu.draw(0);
                        break;
                    }
                    Sleep(5);
                }
            }

        }
        else if (currentState == EXIT) {
            running = false;
        }

    }

    closegraph();
    return 0;
}