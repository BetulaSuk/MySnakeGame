#include <iostream>
#include <curses.h>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <sstream>
#include <filesystem>

#include "../snake/snake.h"
#include "../map/map.h"
#include "../blocks/blocks.h"
#include "../items/items.h"
#include "../renders/renders.h"

using namespace std;

int test_x = 20;
int test_y = 30;

string test_map = "/data/maps/normal_1.map";

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
    Path::setRootPath();

    int wordLen = checkWord("catllshell");

    cout << wordLen << endl;

    return 0;
}

int mainc() {
    Path::setRootPath();
    string mapPath = Path::fullPath(test_map);

    cout << ">>> to initialize map: " << endl;
    Map* map = new Map(test_x, test_y);
    if ( ! map) {
        cout << ">>> failed to load map!!" << endl;
        return 0;
    }
    cout << ">>> map initailized!" << endl;

    Snake* s = new WordSnake(map, 10, 15, 2, 3);
    if ( ! s) {
        cout << ">>> failed to load snake!!" << endl;
        return 0;
    }
    cout << ">>> snake initailized!" << endl;

    vector<Entity*> * en_list = map->get_entity_list();
    Entity* ptr_E;
    char control;
    while (true) {
        cin >> control;

        switch (control) {
            case 'm':
                if (s->moveForward()) {
                    cout << ">>> move finished!" << endl;
                } else {cout << ">>> move failed!" << endl;}

                for (int i = 0; i < en_list->size(); i++) {
                    ptr_E = en_list->at(i);
                    ptr_E->moveForward();
                }



                break;
            case 'r':
                renderMap(*map);
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
            case 'h':
                cout << ">>> snake heart: " << s->get_heart() << endl;
        }
        if (control == 'q') {break;}
    }
}

