#include <curses.h>
#include <string>
#include <thread>
#include <chrono>

#include "../snake/snake.h"
#include "../map/map.h"
#include "../blocks/blocks.h"
#include "../items/items.h"
#include "../renders/renders.h"

int test_x = 50;
int test_y = 30;

void renderMap(WINDOW* win, Map& map);

int main() {
    initscr();
    raw();
    keypad(stdscr, true);
    nodelay(stdscr, true);
    noecho();
    curs_set(0);

    int max_x, max_y;
    getmaxyx(stdscr, max_y, max_x);

    if (max_x <= test_x || max_y <= test_y) {
        test_x = max_x;
        test_y = max_y;
    }
    int start_x = (max_x == test_x) ? 0 : (max_x - test_x) / 2,
        start_y = (max_y == test_y) ? 0 : (max_y - test_y) / 2;

    Map map(test_y, test_x);
    map.init_snake();
    Snake* snake = map.get_snake();
    
    WINDOW* mainWin = newwin(test_y, test_x, start_y, start_x);
    box(mainWin, 0, 0);

    wrefresh(mainWin);

    int control;
    while (true) {
        renderMap(mainWin, map);

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
        if (control == ' ' || control == 10) {break;}

        snake->moveForward();

        if ( ! snake->checkAlive()) {break;}

        this_thread::sleep_for(chrono::milliseconds(50));
    }

    delwin(mainWin);
    endwin();

    return 0;
}

void renderMap(WINDOW* win, Map& map) {
    werase(win);

    BaseBlock* ptr_B;
    BaseItem*  ptr_I;
    SnakeBody* ptr_S;

    for (int i = 0; i < test_y; i++) {
        for (int j = 0; j < test_x; j++) {
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
