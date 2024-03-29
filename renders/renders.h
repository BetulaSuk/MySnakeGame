#ifndef _RENDERS_H_
#define _RENDERS_H_

#include "../items/items.h"
#include "../blocks/blocks.h"
#include "../map/map.h"
#include "../snake/snake.h"
#include "../special_modes/word_snake_mode/word_snake.h"


#include <curses.h>
#include <string>
#include <vector>
#include <chrono>
#include <thread>

using namespace std;


//GameBoard类，整合所有渲染
class GameBoard
{
    public:
        GameBoard();
        ~GameBoard();
        bool createWelcomeBoard();

        //帮助界面
        bool createHelp();

        //选择模式
        int chooseMode();

        //信息栏
        void createInformationBoard();
        void renderInformationBoard();

        //游戏主窗口
        void createGameBoard();

        //创建Logo
        void createLogo();
        void renderLogo();

        //渲染地图！！！
        void renderMap(WINDOW* win, Map* map);


        //右侧计分板
        void createInstructionBoard();
        void renderInstructionBoard(Snake* snake) const;


        //结束界面
        bool renderRestartMenu(Snake* snake) const;

        //经典模式主循环
        void startGame(Map* map, Snake* snake);
        //文字蛇模式主循环
        void startWord(Map* map, WordSnake* snake);

        /* 工具函数 */
        int getGameBoardWidth() {return mGameBoardWidth;}
        int getGameBoardHeight() {return mGameBoardHeight;}

    private:
        int mScreenWidth;
        int mScreenHeight;
        int mGameBoardWidth;
        int mGameBoardHeight;
        const int mInformationHeight = 7;
        const int mInstructionWidth = 18;
        vector<WINDOW*> mWindows;

        vector<int> mLeaderBoard;
        const int mNumLeaders = 3;

        int base_delay = 100;
        int Difficulty = 0;

        //自定义颜色
        short MYCOLOR_F = 10, MYCOLOR_H = 11, MYCOLOR_S = 12, MYCOLOR_P = 13, MYCOLOR_B = 14;

};


#endif