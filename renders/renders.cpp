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

    erase();
    refresh();
    //正中间生成Welcome界面
    noecho();
    int width = this->mScreenWidth * 0.75;
    int height = this->mScreenHeight * 0.5;
    int startX = this->mScreenWidth * 0.125;
    int startY = this->mScreenHeight * 0.375;

    WINDOW* menu;
    WINDOW* title;

    menu = newwin(height, width, startY, startX);
    //box(menu, 0, 0);

    title = newwin(7, width, mScreenHeight*0.125, startX);
    

    mvwprintw(menu, 2, width*0.5 - 13, "Welcome to The Snake Game!");
    mvwprintw(menu, 3, width*0.5 - 8, "Author: TZY, WHY");
    mvwprintw(menu, 4, width*0.5 - 22, "Implemented using C++ and libncurses library");

    start_color();
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    wattron(title, COLOR_PAIR(1));

    string s1 = "  ____              _         ____                      ";
    string s2 = " / ___| _ __   __ _| | _____ / ___| __ _ _ __ ___   ___ ";
    string s3 = " \\___ \\| '_ \\ / _` | |/ / _ \\ |  _ / _` | '_ ` _ \\ / _ \\";
    string s4 = "  ___) | | | | (_| |   <  __/ |_| | (_| | | | | | |  __/";
    string s5 = " |____/|_| |_|\\__,_|_|\\_\\___|\\____|\\__,_|_| |_| |_|\\___|";

    mvwprintw(title, 1, width*0.5 - 28, "%s", s1.c_str());
    mvwprintw(title, 2, width*0.5 - 28, "%s", s2.c_str());
    mvwprintw(title, 3, width*0.5 - 28, "%s", s3.c_str());
    mvwprintw(title, 4, width*0.5 - 28, "%s", s4.c_str());
    mvwprintw(title, 5, width*0.5 - 28, "%s", s5.c_str());
    wattroff(title, COLOR_PAIR(1));
    //wrefresh(title);


    //这里可以加入更多选项
    vector<string> menuItems = {"Start", "Quit", "Help", "Settings"};
    int index = 0;
    int offset = width * 0.25;
    
    //下面实现选项切换
    wattron(menu, A_STANDOUT);
    mvwprintw(menu, 8, offset*0.5 - 2, menuItems[0].c_str());
    wattroff(menu, A_STANDOUT);
    mvwprintw(menu, 8, offset*1.5 - 2, menuItems[1].c_str());
    mvwprintw(menu, 8, offset*2.5 - 2, menuItems[2].c_str());
    mvwprintw(menu, 8, offset*3.5 - 2, menuItems[3].c_str());

    wrefresh(menu);
    wrefresh(title);

    int key;
    while (true)
    {
        key = getch();
        switch (key)
        {
            case 'A':
            case 'a':
            case KEY_LEFT:
                mvwprintw(menu, 8, offset*(index+0.5) - 2, menuItems[index].c_str());
                index --;
                index = (index < 0) ? menuItems.size() - 1 : index;
                wattron(menu, A_STANDOUT);
                mvwprintw(menu, 8, offset*(index+0.5) - 2, menuItems[index].c_str());
                wattroff(menu, A_STANDOUT);
                break;
            case 'D':
            case 'd':
            case KEY_RIGHT:
                mvwprintw(menu, 8, offset*(index+0.5) - 2, menuItems[index].c_str());
                index ++;
                index = (index > menuItems.size() - 1) ? 0 : index;
                wattron(menu, A_STANDOUT);
                mvwprintw(menu, 8, offset*(index+0.5) - 2, menuItems[index].c_str());
                wattroff(menu, A_STANDOUT);
                break;
        }
        wrefresh(menu);
        if (key == ' ' || key == 10) break;
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    delwin(menu);
    delwin(title);

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

    int width = this->mScreenWidth * 0.5;
    int height = this->mScreenHeight * 0.5;
    int startX = this->mScreenWidth * 0.25;
    int startY = this->mScreenHeight * 0.25;

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
    int width = this->mScreenWidth * 0.5;
    int height = this->mScreenHeight * 0.5;
    int startX = this->mScreenWidth * 0.25;
    int startY = this->mScreenHeight * 0.25;

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


//选择游戏模式
int GameBoard::chooseMode() {
    erase();
    refresh();
    //正中间生成Welcome界面
    noecho();
    int width = this->mScreenWidth * 0.75;
    int height = this->mScreenHeight * 0.5;
    int startX = this->mScreenWidth * 0.125;
    int startY = this->mScreenHeight * 0.375;

    WINDOW* menu;
    WINDOW* title;

    title = newwin(7, width, mScreenHeight*0.125, startX);
    start_color();
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    wattron(title, COLOR_PAIR(1));

    string s1 = "  ____              _         ____                      ";
    string s2 = " / ___| _ __   __ _| | _____ / ___| __ _ _ __ ___   ___ ";
    string s3 = " \\___ \\| '_ \\ / _` | |/ / _ \\ |  _ / _` | '_ ` _ \\ / _ \\";
    string s4 = "  ___) | | | | (_| |   <  __/ |_| | (_| | | | | | |  __/";
    string s5 = " |____/|_| |_|\\__,_|_|\\_\\___|\\____|\\__,_|_| |_| |_|\\___|";

    mvwprintw(title, 1, width*0.5 - 28, "%s", s1.c_str());
    mvwprintw(title, 2, width*0.5 - 28, "%s", s2.c_str());
    mvwprintw(title, 3, width*0.5 - 28, "%s", s3.c_str());
    mvwprintw(title, 4, width*0.5 - 28, "%s", s4.c_str());
    mvwprintw(title, 5, width*0.5 - 28, "%s", s5.c_str());
    wattroff(title, COLOR_PAIR(1));

    menu = newwin(height, width, startY, startX);
    //box(menu, 0, 0);

    mvwprintw(menu, 3, width*0.5 - 20, "Choose the Game Mode and Start Playing!");


    //这里可以加入更多选项
    vector<string> menuItems = {"CLASSIC", "WORD", "PVP", "Mode4"};
    int index = 0;
    int offset = width * 0.25;
    
    //下面实现选项切换
    wattron(menu, A_STANDOUT);
    mvwprintw(menu, 8, offset*0.5 - 2, menuItems[0].c_str());
    wattroff(menu, A_STANDOUT);
    mvwprintw(menu, 8, offset*1.5 - 2, menuItems[1].c_str());
    mvwprintw(menu, 8, offset*2.5 - 2, menuItems[2].c_str());
    mvwprintw(menu, 8, offset*3.5 - 2, menuItems[3].c_str());

    wrefresh(menu);
    wrefresh(title);

    int key;
    while (true)
    {
        key = getch();
        switch (key)
        {
            case 'A':
            case 'a':
            case KEY_LEFT:
                mvwprintw(menu, 8, offset*(index+0.5) - 2, menuItems[index].c_str());
                index --;
                index = (index < 0) ? menuItems.size() - 1 : index;
                wattron(menu, A_STANDOUT);
                mvwprintw(menu, 8, offset*(index+0.5) - 2, menuItems[index].c_str());
                wattroff(menu, A_STANDOUT);
                break;
            case 'D':
            case 'd':
            case KEY_RIGHT:
                mvwprintw(menu, 8, offset*(index+0.5) - 2, menuItems[index].c_str());
                index ++;
                index = (index > menuItems.size() - 1) ? 0 : index;
                wattron(menu, A_STANDOUT);
                mvwprintw(menu, 8, offset*(index+0.5) - 2, menuItems[index].c_str());
                wattroff(menu, A_STANDOUT);
                break;
        }
        wrefresh(menu);
        if (key == ' ' || key == 10) break;
        this_thread::sleep_for(chrono::milliseconds(100));
    }
    delwin(menu);
    delwin(title);

    //根据选项不同返回不同值
    return index;
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

    //PVP
    Snake* snake = map.get_snake();
    /*Snake* snake2 = map.get_snake2();
    if (snake2 != nullptr) {
        //TODO
    }*/
    this->renderInstructionBoard(snake);


    //box(this -> mWindows[0], 0, 0);
    //box(this -> mWindows[2], 0, 0);
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

            start_color();
            //改变预设颜色！！
            //灰色
            init_color(COLOR_RED, 800, 800, 800);
            init_pair(1, COLOR_BLACK, COLOR_RED);
            init_pair(2, COLOR_GREEN, COLOR_RED);
            init_pair(3, COLOR_WHITE, COLOR_RED);
            init_pair(4, COLOR_MAGENTA, COLOR_RED);
            

            if (ptr_S != nullptr) {
                //渲染蛇的身体
                wattron(win, COLOR_PAIR(1));
                mvwprintw(win, i, j, ptr_S->toString().c_str());
                wattroff(win, COLOR_PAIR(1));
            }
            //BaseItem(FOOD, HEART, SNAKEBODY)
            else if (ptr_I != nullptr) {
                if (ptr_I -> type() == ItemType::FOOD) {
                    wattron(win, COLOR_PAIR(2));
                    mvwprintw(win, i, j, ptr_I->toString().c_str());
                    wattroff(win, COLOR_PAIR(2));
                }
                else if (ptr_I -> type() == ItemType::HEART) {
                    wattron(win, COLOR_PAIR(4));
                    mvwprintw(win, i, j, ptr_I->toString().c_str());
                    wattroff(win, COLOR_PAIR(4));
                }
            }
            else {
                //渲染地图方块
                wattron(win, COLOR_PAIR(3));
                mvwprintw(win, i, j, ptr_B->toString().c_str());
                if (ptr_B -> type() == BlockType::PORTAL) {
                    Portal* entrance = reinterpret_cast<Portal*>(ptr_B);
                    int exit_x = entrance->get_ex();
                    int exit_y = entrance->get_ey();
                    //map.at(exit_x, exit_y) -> setString("O");
                }
                wattroff(win, COLOR_PAIR(3));
            }
        }
    }
    wrefresh(win);
}



void GameBoard::startGame(Map& map, Snake* snake) {
    refresh();
    int control;

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
}


/*void GameBoard::startPvp(Pvp_Map& map) {
    refresh();
    int control1;
    int control2;

        while (true) {
            this -> renderAllBoards(map);

            control1 = getch();
            control2 = getch();

            switch (control1) {
                case 'W': case 'w':
                    snake1->changeDir(Direction::UP); break;
                case 'S': case 's':
                    snake1->changeDir(Direction::DOWN); break;
                case 'A': case 'a':
                    snake1->changeDir(Direction::LEFT); break;
                case 'D': case 'd':
                    snake1->changeDir(Direction::RIGHT); break;
            }
            switch (control2) {
                case KEY_UP:
                    snake2->changeDir(Direction::UP); break;
                case KEY_DOWN:
                    snake2->changeDir(Direction::DOWN); break;
                case KEY_LEFT:
                    snake2->changeDir(Direction::LEFT); break;
                case KEY_RIGHT:
                    snake2->changeDir(Direction::RIGHT); break;
            }

            snake1->moveForward();
            snake2->moveForward();
            if (!snake1->checkAlive()) {break;}
            if (!snake2->checkAlive()) {break;}

            this_thread::sleep_for(chrono::milliseconds(100));
        }
}*/