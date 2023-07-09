/**
 * definitions for map.h
*/

#include "map.h"
#include "../snake/snake.h"

#include <iostream>
#include <fstream>

void nextPos(int x, int y, int& next_x, int& next_y, Direction dir) {
    next_x = x;
    next_y = y;
    switch (dir) {
        case Direction::UP:    next_x = x - 1; break;
        case Direction::RIGHT: next_y = y + 1; break;
        case Direction::DOWN:  next_x = x + 1; break;
        case Direction::LEFT:  next_y = y - 1; break;
    }
}

BaseBlock* nextBlock(Map* map, BaseBlock* block, Direction dir) {
    BaseBlock* nextBlock = nullptr;

    if (not map->onMap(block)) {return nextBlock;}

    int init_x = block->get_x(),
        init_y = block->get_y();
    int next_x = 0,
        next_y = 0;
    nextPos(init_x, init_y, next_x, next_y, dir);

    if (not map->inRange(next_x, next_y)) {return nextBlock;}

    nextBlock = map->at(next_x, next_y);
    return nextBlock;
}

// 初始化: 创建并储存方块, 创建并绑定蛇
Map::Map(int input_height, int input_width) {
    height = input_height;
    width  = input_width;

    data.resize(height);

    for (int i = 0; i < height; i++) {
        data[i].resize(width);

        for (int j = 0; j < width; j++) {
            // 边缘是墙
            if (i == 0 || i == height -1 ||
                j == 0 || j == width -1) {
                    data[i][j] = new Wall(i, j);
                    data[i][j]->setString("+");
            }
            else {data[i][j] = new BaseBlock(i, j);}
        }
    }
}

Map::Map(std::string fileDir) {
    loadMap(fileDir);
}

void Map::init_snake() {
    ptrSnake = new Snake(this, height/2, width/2, 2, 3);
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

void Map::setRandomItem(ItemType itType, std::string displayString) {
    int rand_x = 0,
        rand_y = 0;
    BaseBlock* tarBlock;

    do {
        rand_x = Random::randInt(0, height - 1);
        rand_y = Random::randInt(0,  width - 1);
        tarBlock = data[rand_x][rand_y];
    } while (tarBlock->get_item() || tarBlock->getSnakeBody());

    BaseItem* newItem;
    switch (itType) {
        case ItemType::FOOD:
            newItem = new Food();
            break;
        case ItemType::HEART:
            newItem = new Heart();
            break;
    }
    if (newItem) {
        newItem->setString(displayString);
        newItem->set_block(tarBlock);
    }
}


/* definitions of namespace Random */

std::default_random_engine* Random::R_engine;

void Random::resetRandomEngine() {
    std::random_device seed;
    R_engine = new std::default_random_engine(seed());
}

int Random::randInt(int start, int end) {
    std::uniform_int_distribution<int> dis(start, end);
    return dis(*R_engine);
}
