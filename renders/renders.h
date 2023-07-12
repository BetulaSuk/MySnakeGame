#ifndef _RENDERS_H_
#define _RENDERS_H_

#include "../items/items.h"
#include "../blocks/blocks.h"
#include "../map/map.h"
#include "../snake/snake.h"
#include "../special_modes/word_snake_mode/word_snake.h"

#include <iostream>
#include <curses.h>
#include <string>
#include <vector>
#include <chrono>
#include <thread>

using namespace std;

class GameBoard
{
    public:
        GameBoard();
        ~GameBoard();
        bool createWelcomeBoard();

        bool createHelp();
        //bool createSetting();

        int chooseMode();

        void createInformationBoard();
        void renderInformationBoard();

        void createGameBoard();
        //void renderGameBoard() const;

        //创建Logo
        void createLogo();
        void renderLogo();


        void renderMap(WINDOW* win, Map* map);

        void createInstructionBoard();
        void renderInstructionBoard(Snake* snake) const;

        bool renderRestartMenu(Snake* snake) const;


        void startGame(Map* map, Snake* snake);
        void startWord(Map* map, WordSnake* snake);


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


        short MYCOLOR_F = 10, MYCOLOR_H = 11, MYCOLOR_S = 12, MYCOLOR_P = 13, MYCOLOR_B = 14;

};

#endif
