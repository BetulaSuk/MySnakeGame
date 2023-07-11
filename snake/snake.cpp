/**
 * definitions for snake.h
*/

#include "snake.h"
#include "../map/map.h"
#include "../snake/snake.h"

#include <iostream>
#include <fstream>
#include <sstream>


// 初始化: 蛇身创建, 蛇身绑定方块, 蛇身绑定蛇, 蛇绑定地图
Snake::Snake(Map* map, int start_x, int start_y, int init_len, int init_heart) {
    ptrHead = new SnakeBody();
    bond(map->at(start_x, start_y), ptrHead);
    ptrHead->ptrSnake = this;
    ptrHead->setString("@");

    if (not map->inRange(start_x, start_y)) {exit(1);}

    int x = start_x,
        y = start_y;

    SnakeBody* ptr = ptrHead;
    for (int i = 1; i < init_len; i++) {
        nextPos(x, y, x, y, Direction::DOWN);

        if (not map->inRange(x, y)) {exit(1);}

        ptr->ptrNext = new SnakeBody();
        ptr = ptr->ptrNext;

        bond(map->at(x, y), ptr);

        ptr->ptrSnake = this;
        ptr->setString("@");
    }

    length = init_len;
    ptrMap = map;
    heart = init_heart;
    dir = Direction::UP;
}

Snake::Snake(Map* map, SnakeBody* head, int init_heart, Direction init_dir) {
    ptrMap  = map;
    ptrHead = head;
    heart   = init_heart;
    dir     = init_dir;

    int count = 0; SnakeBody* ptr_S = ptrHead;
    while (ptr_S) {
        ptr_S->ptrSnake = this;
        count++;
        ptr_S = ptr_S->next();
    }
    length = count;
}

Snake::~Snake() {
    SnakeBody* ptrSbody_1 = ptrHead;
    SnakeBody* ptrSbody_2 = ptrHead;

    for (int i = 0; i < length; i++) {
        ptrSbody_2 = ptrSbody_2->ptrNext;
        delete ptrSbody_1;
        ptrSbody_1 = ptrSbody_2;
    }
}

/* 行动 */

void Snake::changeDir(Direction new_dir) {
    switch (dir) {
        case Direction::UP:
        case Direction::DOWN:
            if (new_dir == Direction::UP || new_dir == Direction::DOWN) {
                return;
            } else {dir = new_dir; break;}
        case Direction::LEFT:
        case Direction::RIGHT:
            if (new_dir == Direction::LEFT || new_dir == Direction::RIGHT) {
                return;
            } else {dir = new_dir; break;}
    }
}

bool Snake::moveForward() {
    // 检查蛇是否死亡
    if (isAlive == false) {return false;}

    // std::cout << ">>> head pos: " << ptrHead->get_x() << ' ' << ptrHead->get_y() << std::endl; //debug
    
    BaseBlock* blockAhead = nextBlock(ptrMap, ptrHead->get_block(), dir);
    BlockType  typeBlock  = blockAhead->type();

    // 检查是否超出地图边界
    if ( ! blockAhead) {return false;}

    // std::cout << ">>> next block pos: " << blockAhead->get_x() << ' ' << blockAhead->get_y() << std::endl; //debug

    // 检查前方方块是否可踏足
    switch (typeBlock) {
        case BlockType::WALL:
            isAlive = false;
            heart = 0;
            return false;
        // TODO 添加更多方块类型时此处可能要增加判定
        default:
            break;
    }

    // 检查前方方块是否有蛇身
    SnakeBody* ptrSAhead = blockAhead->getSnakeBody();

    if (ptrSAhead) {
        // std::cout << ">>> hit self!" << std::endl; //debug
        isAlive = false;
        heart = 0;
        return false;
    }

    BaseItem* itemAhead = blockAhead->get_item();
    ItemType typeItem = ItemType::EMPTY;
    if (itemAhead) {typeItem = itemAhead->type();}

    // 提前获取此时的尾部坐标, 为可能吃食物的情况做准备
    int oldTail_x, oldTail_y;
    SnakeBody* ptrTail = getTailPtr();
    oldTail_x = ptrTail->get_x();
    oldTail_y = ptrTail->get_y();

    // 向前挪动: 从头开始一点点向前伸
    SnakeBody* ptrSbody = ptrHead;
    BaseBlock* ptrB_1 = ptrHead->get_block();
    BaseBlock* ptrB_2 = nextBlock(ptrMap, ptrB_1, dir);

    // std::cout << ">>> mark!!" << std::endl; // debug

    for (int i = 0; i < length; i++) {
        bond(ptrB_2, ptrSbody);
        ptrB_1->releaseSnakeBody();

        // std::cout << ">>> mark: " << i << std::endl; // debug

        ptrSbody = ptrSbody->ptrNext;
        if ( ! ptrSbody) {break;}
        ptrB_2 = ptrB_1;
        ptrB_1 = ptrSbody->get_block();
    }

    // 因为 eatFood 中有判定, 所以不担心误判为吃食物
    tryEatFood(oldTail_x, oldTail_y);
    tryEatHeart();

    return true;
}

bool Snake::revive() {
    if (heart <= 0 || isAlive == true) {return false;}
    else {
        heart--;
        isAlive = true;
    }
}

/* 判定 */



/* 工具函数 */

SnakeBody* Snake::getTailPtr() {
    SnakeBody* tailPtr = ptrHead;

    for (int i = 1; i < length; i++) {
        tailPtr = tailPtr->ptrNext;
    }
    return tailPtr;
}

bool Snake::tryEatFood(int newTail_x, int newTail_y) {
    // 为了可靠性, 再检测一次头部的是否是食物
    BaseItem* item_atHead = ptrHead->get_block()->get_item();
    if ( ! item_atHead || item_atHead->type() != ItemType::FOOD) {return false;}

    SnakeBody* newTail = new SnakeBody();
    newTail->ptrSnake = this;
    bond(ptrMap->at(newTail_x, newTail_y), newTail);
    newTail->setString("@");

    getTailPtr()->ptrNext = newTail;
    length++;
    ptrHead->get_block()->clear_item();

    point++;

    ptrMap->setRandomItem(ItemType::FOOD, "#");

    return true;
}

bool Snake::tryEatFood(int newTail_x, int newTail_y, std::string newTail_s) {
    bool ret = tryEatFood(newTail_x, newTail_y);
    if (ret) {getTailPtr()->setString(newTail_s);}
    return ret;
}

bool Snake::tryEatHeart() {
    // 先检测是否有心可吃
    BaseItem* item_atHead = ptrHead->get_block()->get_item();

    if ( ! item_atHead || item_atHead->type() != ItemType::HEART) {return false;}

    ptrHead->get_block()->clear_item();
    heart++;

    return true;
}
