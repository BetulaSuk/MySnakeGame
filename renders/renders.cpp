#include "renders.h"

GameBoard::GameBoard()
{
    // Separate the screen to three windows
    this->mWindows.resize(4);
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

    start_color();
    init_color(MYCOLOR_F, 800, 800, 0);
    init_color(MYCOLOR_H, 1000, 400, 200);
    init_color(MYCOLOR_S, 100, 800, 100);
    init_color(MYCOLOR_P, 100, 800, 800);
    init_color(MYCOLOR_B, 800, 200, 200);

    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    init_pair(2, COLOR_WHITE, COLOR_BLACK);
    init_pair(3, MYCOLOR_F, COLOR_BLACK);
    init_pair(4, MYCOLOR_H, COLOR_BLACK);
    init_pair(5, MYCOLOR_S, COLOR_BLACK);
    init_pair(6, MYCOLOR_P, COLOR_BLACK);
    init_pair(7, MYCOLOR_B, COLOR_BLACK);
    init_pair(8, COLOR_RED, COLOR_BLACK);

    // Get screen and board parameters
    getmaxyx(stdscr, this->mScreenHeight, this->mScreenWidth);
    this->mGameBoardWidth = this->mScreenWidth - this->mInstructionWidth;
    this->mGameBoardHeight = this->mScreenHeight - this->mInformationHeight;

    this->createInformationBoard();
    this -> createLogo();
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

    //start_color();
    //init_pair(1, COLOR_CYAN, COLOR_BLACK);
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
    vector<string> menuItems = {"Start", "Quit", "Help", "...."};
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
    /*
    if (index == 3) {
        this -> createSetting();
        return this -> createWelcomeBoard();
    }
    */
    if (index == 1 || index == 3) return false;
}

bool GameBoard::createHelp() {

    int width = this->mScreenWidth * 0.5;
    int height = this->mScreenHeight * 0.5;
    int startX = this->mScreenWidth * 0.25;
    int startY = this->mScreenHeight * 0.25;

    WINDOW* menu;
    menu = newwin(height, width, startY, startX);
    box(menu, 0, 0);

    mvwprintw(menu, 2, width*0.5 - 11, "This is the Help page:");
    mvwprintw(menu, 3, width*0.5 - 15, "1. Using WASD to control snake");
    mvwprintw(menu, 4, width*0.5 - 26, "2. Eating food to get score and increase Difficulty");
    mvwprintw(menu, 5, width*0.5 - 27, "3. Heart will be generated, eat it to get more hearts");
    mvwprintw(menu, 6, width*0.5 - 21, "4. Go through walls at the cost of hearts");

    /*start_color();
    short MYCOLOR_F = 10, MYCOLOR_H = 11, MYCOLOR_S = 12, MYCOLOR_P = 13, MYCOLOR_B = 14;
    init_color(MYCOLOR_F, 800, 800, 0);
    init_color(MYCOLOR_H, 1000, 400, 200);
    init_color(MYCOLOR_S, 100, 800, 100);
    init_color(MYCOLOR_P, 100, 800, 800);
    init_color(MYCOLOR_B, 800, 200, 200);

    init_pair(3, MYCOLOR_F, COLOR_BLACK);
    init_pair(4, MYCOLOR_H, COLOR_BLACK);
    init_pair(5, MYCOLOR_S, COLOR_BLACK);
    init_pair(6, MYCOLOR_P, COLOR_BLACK);
    init_pair(7, MYCOLOR_B, COLOR_BLACK);*/


    mvwprintw(menu, 8, width*0.5 - 26, "SnakeBody     Food     Heart     Portal     Barrier");


    wattron(menu, COLOR_PAIR(5));
    mvwprintw(menu, 9, width*0.5 - 22, "@");
    wattroff(menu, COLOR_PAIR(5));

    wattron(menu, COLOR_PAIR(3));
    mvwprintw(menu, 9, width*0.5 - 10, "#");
    wattroff(menu, COLOR_PAIR(3));

    wattron(menu, COLOR_PAIR(4));
    mvwprintw(menu, 9, width*0.5, "+");
    wattroff(menu, COLOR_PAIR(4));

    wattron(menu, COLOR_PAIR(6));
    mvwprintw(menu, 9, width*0.5 + 10, "P");
    wattroff(menu, COLOR_PAIR(6));
    
    wattron(menu, COLOR_PAIR(7));
    mvwprintw(menu, 9, width*0.5 + 22, "=");
    wattroff(menu, COLOR_PAIR(7));

    vector<string> menuItems = {"Back"};
    
    //下面实现选项切换
    wattron(menu, A_STANDOUT);
    mvwprintw(menu, 11, width*0.5 - 2, menuItems[0].c_str());
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

    mvwprintw(menu, 3, width*0.5 - 20, "Choose the Game Mode and Start Playing!");


    //这里可以加入更多选项
    vector<string> menuItems = {"CLASSIC", "  WORD  ", "SAND BOX", "  ....  "};
    int index = 0;
    int offset = width * 0.25;
    
    //下面实现选项切换
    wattron(menu, A_STANDOUT);
    mvwprintw(menu, 8, offset*0.5 - 4, menuItems[0].c_str());
    wattroff(menu, A_STANDOUT);
    mvwprintw(menu, 8, offset*1.5 - 4, menuItems[1].c_str());
    mvwprintw(menu, 8, offset*2.5 - 4, menuItems[2].c_str());
    mvwprintw(menu, 8, offset*3.5 - 4, menuItems[3].c_str());

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
                mvwprintw(menu, 8, offset*(index+0.5) - 4, menuItems[index].c_str());
                index --;
                index = (index < 0) ? menuItems.size() - 1 : index;
                wattron(menu, A_STANDOUT);
                mvwprintw(menu, 8, offset*(index+0.5) - 4, menuItems[index].c_str());
                wattroff(menu, A_STANDOUT);
                break;
            case 'D':
            case 'd':
            case KEY_RIGHT:
                mvwprintw(menu, 8, offset*(index+0.5) - 4, menuItems[index].c_str());
                index ++;
                index = (index > menuItems.size() - 1) ? 0 : index;
                wattron(menu, A_STANDOUT);
                mvwprintw(menu, 8, offset*(index+0.5) - 4, menuItems[index].c_str());
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
    this->mWindows[0] = newwin(this->mInformationHeight, this->mScreenWidth - 65, startY, startX);
}


void GameBoard::renderInformationBoard()
{
    werase(mWindows[0]);
    mvwprintw(this->mWindows[0], 1, 1, "Welcome to The Snake Game!");
    mvwprintw(this->mWindows[0], 2, 1, "Author: TZY, WHY");
    mvwprintw(this->mWindows[0], 3, 1, "Website:");
    mvwprintw(this->mWindows[0], 4, 1, "Implemented using C++ and libncurses library.");

    box(mWindows[0], 0, 0);
    wrefresh(mWindows[0]);
}



void GameBoard::createLogo() {
    int startY = 0;
    int startX = this -> mScreenWidth - 65;
    this->mWindows[3] = newwin(this->mInformationHeight, 65, startY, startX);
    //box(mWindows[3], 0, 0);
}


void GameBoard::renderLogo() {
    string s1 = "  ____              _         ____";
    string s2 = " / ___| _ __   __ _| | _____ / ___| __ _ _ __ ___   ___";
    string s3 = " \\___ \\| '_ \\ / _` | |/ / _ \\ |  _ / _` | '_ ` _ \\ / _ \\";
    string s4 = "  ___) | | | | (_| |   <  __/ |_| | (_| | | | | | |  __/";
    string s5 = " |____/|_| |_|\\__,_|_|\\_\\___|\\____|\\__,_|_| |_| |_|\\___|";
    
    int width = this->mScreenWidth;
    //start_color();
    //init_pair(1, COLOR_CYAN, COLOR_BLACK);
    wattron(this->mWindows[3], COLOR_PAIR(1));
    
    mvwprintw(this->mWindows[3], 1, 3, "%s", s1.c_str());
    mvwprintw(this->mWindows[3], 2, 3, "%s", s2.c_str());
    mvwprintw(this->mWindows[3], 3, 3, "%s", s3.c_str());
    mvwprintw(this->mWindows[3], 4, 3, "%s", s4.c_str());
    mvwprintw(this->mWindows[3], 5, 3, "%s", s5.c_str());

    wattroff(this->mWindows[3], COLOR_PAIR(1));

    //box(mWindows[3], 0, 0);

    wrefresh(mWindows[3]);
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
    werase(mWindows[2]);
    mvwprintw(this->mWindows[2], 1, 1, "Manual");

    mvwprintw(this->mWindows[2], 3, 1, "Up: W");
    mvwprintw(this->mWindows[2], 4, 1, "Down: S");
    mvwprintw(this->mWindows[2], 5, 1, "Left: A");
    mvwprintw(this->mWindows[2], 6, 1, "Right: D");

    mvwprintw(this->mWindows[2], 8, 1, "Difficulty");

    string dif = to_string(Difficulty);
    mvwprintw(this->mWindows[2], 9, 1, dif.c_str());

    mvwprintw(this->mWindows[2], 11, 1, "Points");
    string pointString = to_string(snake -> get_point());
    mvwprintw(this->mWindows[2], 12, 1, pointString.c_str());

    mvwprintw(this -> mWindows[2], 14, 1, "Heart");
    string heartStr = to_string(snake -> get_heart());
    mvwprintw(this -> mWindows[2], 15, 1, heartStr.c_str());

    box(mWindows[2], 0, 0);
    wrefresh(mWindows[2]);
}


bool GameBoard::renderRestartMenu(Snake* snake) const
{
    WINDOW * menu;
    int width = this->mGameBoardWidth * 0.75;
    int height = this->mGameBoardHeight * 0.75;
    int startX = this->mGameBoardWidth * 0.125;
    int startY = this->mGameBoardHeight * 0.125 + this->mInformationHeight;

    menu = newwin(height, width, startY, startX);
    //box(): decorate the screen with frame(vertical and horizontal)
    box(menu, 0, 0);
    std::vector<std::string> menuItems = {"Restart", " Quit  "};

    std::string s1 = "   ____                         ___";
    std::string s2 = "  / ___| __ _ _ __ ___   ___   / _ \\__   _____ _ __";
    std::string s3 = " | |  _ / _` | '_ ` _ \\ / _ \\ | | | \\ \\ / / _ \\ '__|";
    std::string s4 = " | |_| | (_| | | | | | |  __/ | |_| |\\ V /  __/ |";
    std::string s5 = "  \\____|\\__,_|_| |_| |_|\\___|  \\___/  \\_/ \\___|_|";

    //start_color();
    //init_pair(8, COLOR_RED, COLOR_BLACK);
    wattron(menu, COLOR_PAIR(8));

    mvwprintw(menu, 1, width*0.5 - 25, "%s", s1.c_str());
    mvwprintw(menu, 2, width*0.5 - 25, "%s", s2.c_str());
    mvwprintw(menu, 3, width*0.5 - 25, "%s", s3.c_str());
    mvwprintw(menu, 4, width*0.5 - 25, "%s", s4.c_str());
    mvwprintw(menu, 5, width*0.5 - 25, "%s", s5.c_str());

    wattroff(menu, COLOR_PAIR(8));

    int index = 0;
    int offset = 4;
    mvwprintw(menu, 8, width*0.5 - 8, "Your Final Score:");
    std::string pointString = std::to_string(snake -> get_point());
    mvwprintw(menu, 9, width*0.5 - 1, pointString.c_str());
    //wattron(): here turns on the highlighting mode of the screen
    wattron(menu, A_STANDOUT);
    mvwprintw(menu, 8 + offset, width*0.5 - 4, menuItems[0].c_str());
    //wattroff(): here turns off the highlighting mode of the screen
    wattroff(menu, A_STANDOUT);
    mvwprintw(menu, 9 + offset, width*0.5 - 4, menuItems[1].c_str());

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
                mvwprintw(menu, 8 + index + offset, width*0.5 - 4, menuItems[index].c_str());
                index --;
                index = (index < 0) ? menuItems.size() - 1 : index;
                wattron(menu, A_STANDOUT);
                mvwprintw(menu, 8 + index + offset, width*0.5 - 4, menuItems[index].c_str());
                wattroff(menu, A_STANDOUT);
                break;
            }
            case 'S':
            case 's':
            case KEY_DOWN:
            {
                mvwprintw(menu, 8 + index + offset, width*0.5 - 4, menuItems[index].c_str());
                index ++;
                index = (index > menuItems.size() - 1) ? 0 : index;
                wattron(menu, A_STANDOUT);
                mvwprintw(menu, 8 + index + offset, width*0.5 - 4, menuItems[index].c_str());
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



void GameBoard::renderMap(WINDOW* win, Map& map) {
    werase(win);

    BaseBlock* ptr_B;
    BaseItem*  ptr_I;
    SnakeBody* ptr_S;

    int width = map.get_width(), height = map.get_height();
    int startY = mGameBoardHeight*0.5 - height*0.5;
    int startX = mGameBoardWidth*0.5 - width*0.5;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            ptr_B = map.at(i, j);
            ptr_I = ptr_B->get_item();
            ptr_S = ptr_B->getSnakeBody();

            if (ptr_S != nullptr) {
                //渲染蛇的身体

                wattron(win, COLOR_PAIR(5));
                mvwprintw(win, i + startY, j + startX, ptr_S->toString().c_str());
                wattroff(win, COLOR_PAIR(5));

            }
            //BaseItem(FOOD, HEART, SNAKEBODY)
            else if (ptr_I != nullptr) {
                if (ptr_I -> type() == ItemType::FOOD) {
                    wattron(win, COLOR_PAIR(3));
                    mvwprintw(win, i + startY, j + startX, ptr_I->toString().c_str());
                    wattroff(win, COLOR_PAIR(3));
                }
                else if (ptr_I -> type() == ItemType::HEART) {
                    wattron(win, COLOR_PAIR(4));
                    mvwprintw(win, i + startY, j + startX, ptr_I->toString().c_str());
                    wattroff(win, COLOR_PAIR(4));
                }
                else if (ptr_I -> type() == ItemType::SNAKEBODY) {
                    wattron(win, COLOR_PAIR(4));
                    mvwprintw(win, i + startY, j + startX, ptr_I->toString().c_str());
                    wattroff(win, COLOR_PAIR(4));
                }
            }
            else {
                //渲染地图方块
                if (ptr_B->type() == BlockType::WALL) {
                    wattron(win, COLOR_PAIR(2));
                    mvwprintw(win, i + startY, j + startX, ptr_B->toString().c_str());
                    wattroff(win, COLOR_PAIR(2));
                }
                else if (ptr_B->type() == BlockType::PORTAL) {
                    wattron(win, COLOR_PAIR(6));
                    mvwprintw(win, i + startY, j + startX, ptr_B->toString().c_str());
                    wattroff(win, COLOR_PAIR(6));
                }
                else if (ptr_B->type() == BlockType::BARRIER) {
                    wattron(win, COLOR_PAIR(7));
                    mvwprintw(win, i + startY, j + startX, ptr_B->toString().c_str());
                    wattroff(win, COLOR_PAIR(7));
                }
                else mvwprintw(win, i + startY, j + startX, ptr_B->toString().c_str());
                /*暂时不需要渲染传送门出口
                if (ptr_B -> type() == BlockType::PORTAL) {
                    Portal* entrance = reinterpret_cast<Portal*>(ptr_B);
                    int exit_x = entrance->get_ex();
                    int exit_y = entrance->get_ey();
                    //map.at(exit_x, exit_y) -> setString("O");
                }*/ 
            }
        }
    }
    box(win, 0, 0);
    wrefresh(win);
}



void GameBoard::startGame(Map& map, Snake* snake) {
    curs_set(0);
    int control;

        while (true) {
            renderMap(mWindows[1], map);
            renderInstructionBoard(snake);


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

            //调整难度
            int point = snake->get_point();
            Difficulty = point/5;
            int delay = base_delay * pow(0.75, Difficulty);


            if (control == ' ' || control == 10) break;

            this_thread::sleep_for(chrono::milliseconds(delay));
        }
}


void GameBoard::startWord(Map& map, WordSnake* snake) {
    //MYDE::win = mWindows[1];
    
    curs_set(0);
    int control;

    vector<Entity*> * en_list = map.get_entity_list();

        while (true) {
            renderMap(mWindows[1], map);
            renderInstructionBoard(snake);

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
            
            for (auto it = en_list->begin(); it != en_list->end(); it++) {
                (*it)->moveForward();
                //mvwprintw(mWindows[0], 5, 1, "%d", mark);
                //mvwprintw(mWindows[0], 5, 5, "%d", (*it)->get_len());
                //wrefresh(mWindows[0]);
            }

            if (control == ' ' || control == 10) break;

            this_thread::sleep_for(chrono::milliseconds(base_delay));

            /*if (en_list->size() != 0) {
                mvwprintw(mWindows[0], 5, 7, "size!"); wrefresh(mWindows[0]); // debug
            }*/
        }
}