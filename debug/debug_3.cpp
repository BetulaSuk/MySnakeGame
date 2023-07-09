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

int main() {
    Random::resetRandomEngine();

    for (int i = 0; i < 100; i++) {
        std::cout << ">>> " << Random::randInt(0, 100) << std:: endl;
    }

    return 0;
}
