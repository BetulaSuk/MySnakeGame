#include <iostream>
#include <curses.h>
#include <string>
#include <thread>
#include <chrono>

#include "../snake/snake.h"
#include "../map/map.h"
#include "../blocks/blocks.h"
#include "../items/items.h"
#include "../renders/renders.h"

using namespace std;

int test_x = 20;
int test_y = 40;

void renderMap(Map& map) {
    BaseBlock* ptr_B;
    BaseItem*  ptr_I;
    SnakeBody* ptr_S;
    for (int i = 0; i < test_x; i++) {
        for (int j = 0; j < test_y; j++) {
            ptr_B = map.at(i, j);
            ptr_I = ptr_B->get_item();
            ptr_S = ptr_B->getSnakeBody();

            if (ptr_S) {
                cout << ptr_S->toString();
            }
            else if (ptr_I) {
                cout << ptr_I->toString();
            }
            else {
                cout << ptr_B->toString();
            }
        }
        cout << endl;
    }
}

int main() {
    cout << ">>> to initialize map: " << endl;
    Map map(test_x, test_y);
    cout << ">>> map initailized!" << endl;
    map.init_snake();
    Snake* s = map.get_snake();
    cout << ">>> snake initailized!" << endl;

    char control;
    while (true) {
        cin >> control;

        switch (control) {
            case '\n':
                break;
            case 'm':
                s->moveForward();
                cout << ">>> move finished!" << endl;
                break;
            case 'r':
                renderMap(map);
                break;
            case 'W': case 'w':
                s->changeDir(Direction::UP); break;
            case 'S': case 's': 
                s->changeDir(Direction::DOWN); break;
            case 'A': case 'a': 
                s->changeDir(Direction::LEFT); break;
            case 'D': case 'd': 
                s->changeDir(Direction::RIGHT); break;
            case 'c':
                cout << ">>> snake alive: " << s->checkAlive() << endl;
        }
        if (control == 'q') {break;}
    }
}

