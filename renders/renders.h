#ifndef _RENDERS_H_
#define _RENDERS_H_

#include "../items/items.h"
#include "../blocks/blocks.h"
#include "../map/map.h"
#include "../snake/snake.h"

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
        bool createSetting();

        int chooseMode();

        void createInformationBoard();
        void renderInformationBoard();

        void createGameBoard();
        void renderGameBoard() const;

        //创建Logo
        void createLogo();
        void renderLogo();


        void renderMap(WINDOW* win, Map& map);

        void createInstructionBoard();
        void renderInstructionBoard(Snake* snake) const;

        bool renderRestartMenu(Snake* snake) const;

        void renderAllBoards(Map& map, Snake* snake);

        void startGame(Map& map, Snake* snake);


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
};

#endif
