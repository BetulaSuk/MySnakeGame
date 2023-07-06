/**
 * definitions for map.h
*/

#include "map.h"

#include <iostream>

void nextPos(int x, int y, int& next_x, int& next_y, Direction dir) {
    switch (dir) {
        case UP:    next_x = x - 1; break;
        case RIGHT: next_y = y + 1; break;
        case DOWN:  next_x = x + 1; break;
        case LEFT:  next_y = y - 1; break;
    }
}

BaseBlock* nextBlock(Map& map, BaseBlock* block, Direction dir) {
    int init_x = block->get_x(),
        init_y = block->get_y();
    BaseBlock* nextBlock = nullptr;

    if (not map.onMap(block)) {return nextBlock;}

    int next_x = 0,
        next_y = 0;
    nextPos(init_x, init_y, next_x, next_y, dir);

    if (not map.inRange(next_x, next_y)) {return nextBlock;}

    nextBlock = map.at(next_x, next_y);
    return nextBlock;
}

// 初始化: 创建并储存方块, 创建并绑定蛇
Map::Map(int input_width, int input_height) {
    data.resize(input_height);

    for (int i = 0; i < input_height; i++) {
        data[i].resize(input_width);

        for (int j = 0; j < input_width; j++) {
            // 边缘是墙
            if (i == 0 || i == input_height -1 ||
                j == 0 || j == input_height -1) {
                    data[i][j] = new Wall(i, j);
            }
            else {data[i][j] = new BaseBlock(i, j);}
        }
    }

    ptrSnake = new Snake(*this, input_height/2, input_width/2, 2);
}

Map::Map(std::string fileDir) {
    loadMap(fileDir);
}

bool Map::loadMap(std::string fileDir) {
    /* TODO */
}

bool Map::writeMap(std::string fileDir) {
    /* TODO */
}

bool Map::onMap(BaseBlock* block) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (block == data[i][j]) {
                return true;
            }
        }
    }
    return false;
}

