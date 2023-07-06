#ifndef _RENDERS_H_
#define _RENDERS_H_

#include <iostream>
#include <ncurses.h>
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

        void createInformationBoard();
        void renderInformationBoard() const;

        void createGameBoard();
        void renderGameBoard() const;

        void createInstructionBoard();
        void renderInstructionBoard() const;

        void renderAllBoards() const;

        void startGame();

    private:
        int mScreenWidth;
        int mScreenHeight;
        int mGameBoardWidth;
        int mGameBoardHeight;
        const int mInformationHeight = 6;
        const int mInstructionWidth = 18;
        vector<WINDOW*> mWindows;

        vector<int> mLeaderBoard;
        const int mNumLeaders = 3;
};

#endif
