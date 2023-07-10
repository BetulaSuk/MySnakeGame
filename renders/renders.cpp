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
    noecho();
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
    if (index == 3) {
        this -> createSetting();
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


//Create Setting board
//(Unfinished)
bool GameBoard:: createSetting() {
    int width = this->mGameBoardWidth * 0.5;
    int height = this->mGameBoardHeight * 0.5;
    int startX = this->mGameBoardWidth * 0.25;
    int startY = this->mGameBoardHeight * 0.25;

    WINDOW* menu;
    menu = newwin(height, width, startY, startX);
    box(menu, 0, 0);

    mvwprintw(menu, 1, 1, "Modify Game Settings");

    std::vector<std::string> menuItems = {"Save"};
    
    //下面实现选项切换
    wattron(menu, A_STANDOUT);
    mvwprintw(menu, 9, 1, menuItems[0].c_str());
    //wattroff(menu, A_STANDOUT);

    wrefresh(menu);

    int key;
    while (true)
    {
        key = getch();
        if (key == ' ' || key == 10) break;
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
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
    mvwprintw(this->mWindows[0], 2, 1, "Author: TZY, WHY");
    mvwprintw(this->mWindows[0], 3, 1, "Website: https://github.com/leimao/");
    mvwprintw(this->mWindows[0], 4, 1, "Implemented using C++ and libncurses library.");
    //wrefresh(this->mWindows[0]);
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

void GameBoard::renderInstructionBoard(Snake* snake) const
{
    mvwprintw(this->mWindows[2], 1, 1, "Manual");

    mvwprintw(this->mWindows[2], 3, 1, "Up: W");
    mvwprintw(this->mWindows[2], 4, 1, "Down: S");
    mvwprintw(this->mWindows[2], 5, 1, "Left: A");
    mvwprintw(this->mWindows[2], 6, 1, "Right: D");

    mvwprintw(this->mWindows[2], 8, 1, "Difficulty");
    mvwprintw(this->mWindows[2], 9, 1, "NOT YET!");

    mvwprintw(this->mWindows[2], 11, 1, "Points");
    string pointString = to_string(snake -> get_point());
    mvwprintw(this->mWindows[2], 12, 1, pointString.c_str());

    mvwprintw(this -> mWindows[2], 14, 1, "Heart");
    string heartStr = to_string(snake -> get_heart());
    mvwprintw(this -> mWindows[2], 15, 1, heartStr.c_str());

    //wrefresh(this->mWindows[2]);
}


bool GameBoard::renderRestartMenu(Snake* snake) const
{
    WINDOW * menu;
    int width = this->mGameBoardWidth * 0.5;
    int height = this->mGameBoardHeight * 0.5;
    int startX = this->mGameBoardWidth * 0.25;
    int startY = this->mGameBoardHeight * 0.25 + this->mInformationHeight;

    menu = newwin(height, width, startY, startX);
    //box(): decorate the screen with frame(vertical and horizontal)
    box(menu, 0, 0);
    std::vector<std::string> menuItems = {"Restart", "Quit"};

    int index = 0;
    int offset = 4;
    mvwprintw(menu, 1, 1, "Your Final Score:");
    std::string pointString = std::to_string(snake -> get_point());
    mvwprintw(menu, 2, 1, pointString.c_str());
    //wattron(): here turns on the highlighting mode of the screen
    wattron(menu, A_STANDOUT);
    mvwprintw(menu, 0 + offset, 1, menuItems[0].c_str());
    //wattroff(): here turns off the highlighting mode of the screen
    wattroff(menu, A_STANDOUT);
    mvwprintw(menu, 1 + offset, 1, menuItems[1].c_str());

    wrefresh(menu);

    int key;
    while (true)
    {
        key = getch();
        switch(key)
        {
            case 'W':
            case 'w':
            case KEY_UP:
            {
                mvwprintw(menu, index + offset, 1, menuItems[index].c_str());
                index --;
                index = (index < 0) ? menuItems.size() - 1 : index;
                wattron(menu, A_STANDOUT);
                mvwprintw(menu, index + offset, 1, menuItems[index].c_str());
                wattroff(menu, A_STANDOUT);
                break;
            }
            case 'S':
            case 's':
            case KEY_DOWN:
            {
                mvwprintw(menu, index + offset, 1, menuItems[index].c_str());
                index ++;
                index = (index > menuItems.size() - 1) ? 0 : index;
                wattron(menu, A_STANDOUT);
                mvwprintw(menu, index + offset, 1, menuItems[index].c_str());
                wattroff(menu, A_STANDOUT);
                break;
            }
        }
        wrefresh(menu);
        if (key == ' ' || key == 10)
        {
            break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    delwin(menu);

    if (index == 0)
    {
        return true;
    }
    else
    {
        return false;
    }

}


void GameBoard::renderAllBoards(Map& map)
{
    for (int i = 0; i < this->mWindows.size(); i++)
    {
        werase(this->mWindows[i]);
    }
    this->renderInformationBoard();

    renderMap(mWindows[1], map);
    //this->renderGameBoard();

    this->renderInstructionBoard(map.get_snake());

    for (int i = 0; i < this->mWindows.size(); i++)
    {
        box(this->mWindows[i], 0, 0);
        wrefresh(this->mWindows[i]);
    }
}



void GameBoard::renderMap(WINDOW* win, Map& map) {
    werase(win);

    BaseBlock* ptr_B;
    BaseItem*  ptr_I;
    SnakeBody* ptr_S;

    int width = map.get_width(), height = map.get_height();

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            ptr_B = map.at(i, j);
            ptr_I = ptr_B->get_item();
            ptr_S = ptr_B->getSnakeBody();

            if (ptr_S != nullptr) {
                mvwprintw(win, i, j, ptr_S->toString().c_str());
            }
            else if (ptr_I != nullptr) {
                mvwprintw(win, i, j, ptr_I->toString().c_str());
            }
            else {
                mvwprintw(win, i, j, ptr_B->toString().c_str());
            }
        }
    }
    wrefresh(win);
}



void GameBoard::startGame() {
    refresh();

    Map map(mGameBoardHeight, mGameBoardWidth);

    map.init_snake();
    Snake* snake = map.get_snake();

    bool choice;
    int control;

    while (true) {

        choice = this -> createWelcomeBoard();
        //refresh();
        if (!choice) break;


        while (true) {
            this -> renderAllBoards(map);

            control = getch();

            switch (control) {
                case 'W': case 'w': case KEY_UP:
                    snake->changeDir(Direction::UP); break;
                case 'S': case 's': case KEY_DOWN:
                    snake->changeDir(Direction::DOWN); break;
                case 'A': case 'a': case KEY_LEFT:
                    snake->changeDir(Direction::LEFT); break;
                case 'D': case 'd': case KEY_RIGHT:
                    snake->changeDir(Direction::RIGHT); break;
            }

            snake->moveForward();
            if (!snake->checkAlive()) {break;}

            this_thread::sleep_for(chrono::milliseconds(100));
        }
        //if (control == ' ' || control == 10) {break;}

        choice = this->renderRestartMenu(snake);
        if (choice == false) break;
        snake -> revive();
        clear();
        refresh();
    }
}