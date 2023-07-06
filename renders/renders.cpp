#include "renders.h"


GameBoard::GameBoard()
{
    // Separate the screen to three windows
    this->mWindows.resize(3);
    initscr();
    // 将所有键盘输入导入程序, 包括终止和Fn
    raw();
    // If there wasn't any key pressed don't wait for keypress
    nodelay(stdscr, true);
    // Turn on keypad control
    keypad(stdscr, true);
    // No echo for the key pressed
    noecho();
    // No cursor show
    curs_set(0);
    // Get screen and board parameters
    getmaxyx(stdscr, this->mScreenHeight, this->mScreenWidth);
    this->mGameBoardWidth = this->mScreenWidth - this->mInstructionWidth;
    this->mGameBoardHeight = this->mScreenHeight - this->mInformationHeight;

    this->createInformationBoard();
    this->createGameBoard();
    this->createInstructionBoard();

    // Initialize the leader board to be all zeros
    this->mLeaderBoard.assign(this->mNumLeaders, 0);
}

GameBoard::~GameBoard()
{
    for (int i = 0; i < this->mWindows.size(); i ++)
    {
        delwin(this->mWindows[i]);
    }
    endwin();
}


bool GameBoard::createWelcomeBoard() {

    //正中间生成Welcome界面
    int width = this->mGameBoardWidth * 0.5;
    int height = this->mGameBoardHeight * 0.5;
    int startX = this->mGameBoardWidth * 0.25;
    int startY = this->mGameBoardHeight * 0.25;

    WINDOW* menu;
    menu = newwin(height, width, startY, startX);
    box(menu, 0, 0);

    mvwprintw(menu, 1, 1, "Welcome to The Snake Game!");
    mvwprintw(menu, 2, 1, "Author: TZY, WHY");
    mvwprintw(menu, 3, 1, "Implemented using C++ and libncurses library.");

    //这里可以加入更多选项
    vector<string> menuItems = {"Start", "Quit", "Help", "Settings"};
    int index = 0;
    int offset = 5;
    
    //下面实现选项切换
    wattron(menu, A_STANDOUT);
    mvwprintw(menu, 0 + offset, 1, menuItems[0].c_str());
    wattroff(menu, A_STANDOUT);
    mvwprintw(menu, 1 + offset, 1, menuItems[1].c_str());
    wattroff(menu, A_STANDOUT);
    mvwprintw(menu, 2 + offset, 1, menuItems[2].c_str());
    wattroff(menu, A_STANDOUT);
    mvwprintw(menu, 3 + offset, 1, menuItems[3].c_str());

    wrefresh(menu);

    int key;
    while (true)
    {
        key = getch();
        switch (key)
        {
            case 'W':
            case 'w':
            case KEY_UP:
                mvwprintw(menu, index + offset, 1, menuItems[index].c_str());
                index --;
                index = (index < 0) ? menuItems.size() - 1 : index;
                wattron(menu, A_STANDOUT);
                mvwprintw(menu, index + offset, 1, menuItems[index].c_str());
                wattroff(menu, A_STANDOUT);
                break;
            case 'S':
            case 's':
            case KEY_DOWN:
                mvwprintw(menu, index + offset, 1, menuItems[index].c_str());
                index ++;
                index = (index > menuItems.size() - 1) ? 0 : index;
                wattron(menu, A_STANDOUT);
                mvwprintw(menu, index + offset, 1, menuItems[index].c_str());
                wattroff(menu, A_STANDOUT);
                break;
        }
        wrefresh(menu);
        if (key == ' ' || key == 10) break;
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    delwin(menu);

    //根据选项不同返回不同值
    if (index == 0) return true;
    if (index == 2) {
        this -> createHelp();
        return this -> createWelcomeBoard();
    }
    if (index == 1) return false;
}

bool GameBoard::createHelp() {

    int width = this->mGameBoardWidth * 0.5;
    int height = this->mGameBoardHeight * 0.5;
    int startX = this->mGameBoardWidth * 0.25;
    int startY = this->mGameBoardHeight * 0.25;

    WINDOW* menu;
    menu = newwin(height, width, startY, startX);
    box(menu, 0, 0);

    mvwprintw(menu, 1, 1, "This is the Help page");
    mvwprintw(menu, 2, 1, "Using WASD to control snake");
    mvwprintw(menu, 3, 1, "Eating food to get score");

    vector<string> menuItems = {"Back"};
    
    //下面实现选项切换
    wattron(menu, A_STANDOUT);
    mvwprintw(menu, 7, 1, menuItems[0].c_str());
    //wattroff(menu, A_STANDOUT);

    wrefresh(menu);

    int key;
    while (true)
    {
        key = getch();
        if (key == ' ' || key == 10) break;
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    delwin(menu);
    return true;
}



void GameBoard::createInformationBoard()
{
    int startY = 0;
    int startX = 0;
    this->mWindows[0] = newwin(this->mInformationHeight, this->mScreenWidth, startY, startX);
}

void GameBoard::renderInformationBoard() const
{
    mvwprintw(this->mWindows[0], 1, 1, "Welcome to The Snake Game!");
    mvwprintw(this->mWindows[0], 2, 1, "Author: WHY");
    mvwprintw(this->mWindows[0], 3, 1, "Website: https://github.com/leimao/");
    mvwprintw(this->mWindows[0], 4, 1, "Implemented using C++ and libncurses library.");
    wrefresh(this->mWindows[0]);
}

void GameBoard::createGameBoard()
{
    int startY = this->mInformationHeight;
    int startX = 0;
    this->mWindows[1] = newwin(this->mScreenHeight - this->mInformationHeight, this->mScreenWidth - this->mInstructionWidth, startY, startX);
}

void GameBoard::renderGameBoard() const
{
    wrefresh(this->mWindows[1]);
}

void GameBoard::createInstructionBoard()
{
    int startY = this->mInformationHeight;
    int startX = this->mScreenWidth - this->mInstructionWidth;
    this->mWindows[2] = newwin(this->mScreenHeight - this->mInformationHeight, this->mInstructionWidth, startY, startX);
}

void GameBoard::renderInstructionBoard() const
{
    mvwprintw(this->mWindows[2], 1, 1, "Manual");

    mvwprintw(this->mWindows[2], 3, 1, "Up: W");
    mvwprintw(this->mWindows[2], 4, 1, "Down: S");
    mvwprintw(this->mWindows[2], 5, 1, "Left: A");
    mvwprintw(this->mWindows[2], 6, 1, "Right: D");

    mvwprintw(this->mWindows[2], 8, 1, "Difficulty");
    mvwprintw(this->mWindows[2], 11, 1, "Points");

    wrefresh(this->mWindows[2]);
}


void GameBoard::renderAllBoards() const
{
    for (int i = 0; i < this->mWindows.size(); i ++)
    {
        werase(this->mWindows[i]);
    }
    this->renderInformationBoard();
    this->renderGameBoard();
    this->renderInstructionBoard();
    for (int i = 0; i < this->mWindows.size(); i ++)
    {
        box(this->mWindows[i], 0, 0);
        wrefresh(this->mWindows[i]);
    }


}


void GameBoard::startGame() {
    refresh();
    bool choice = this -> createWelcomeBoard();
    //Map gameMap(15,15);
    //Snake* snakePtr = gameMap.get_snake();
    int temp = 0;
    this -> renderAllBoards();
    Map map(15, 15);
    Snake* snakePtr = map.get_snake();
    while (choice) {
        //snakePtr -> moveForward();
        snakePtr -> moveForward();
        wrefresh(this -> mWindows[1]);
        temp++;
        this_thread::sleep_for(chrono::milliseconds(100));
    }
}