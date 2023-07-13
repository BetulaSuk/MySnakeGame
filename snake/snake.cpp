/**
 * definitions for snake.h
*/

#include "snake.h"
#include "../map/map.h"
#include "../snake/snake.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>


// 初始化: 蛇身创建, 蛇身绑定方块, 蛇身绑定蛇, 蛇绑定地图
Snake::Snake(Map* map, int start_x, int start_y, int init_len, int init_heart) {
    if (not map->inRange(start_x, start_y)) {exit(1);}

    ptrHead = new SnakeBody();
    bond(map->at(start_x, start_y), ptrHead);
    ptrHead->ptrSnake = this;
    ptrHead->setString("@");

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
    map->set_snake(this);
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
        length++;
        ptr_S = ptr_S->next();
    }
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

    BaseBlock* blockAhead = nextBlock(ptrMap, ptrHead->get_block(), dir);
    BlockType  typeBlock  = BlockType::EMPTY;

    // 检查是否超出地图边界
    if ( ! blockAhead) {return false;}
    typeBlock = blockAhead->type();

    // 检查前方方块是否可踏足
    switch (typeBlock) {
        case BlockType::WALL:
            isAlive = false;
            heart = 0;
            return false;
        case BlockType::BARRIER:
            heart--;
            if (heart <= 0) {
                isAlive = false;
                return false;
            }
            break;
        default:
            break;
    }

    // 检查前方方块是否有蛇身
    SnakeBody* ptrSAhead = blockAhead->getSnakeBody();
    if (ptrSAhead) {
        isAlive = false;
        heart = 0;
        return false;
    }

    // 获取前方方块上的物品类型
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

    for (int i = 0; i < length; i++) {
        bond(ptrB_2, ptrSbody);
        ptrB_1->releaseSnakeBody();

        ptrSbody = ptrSbody->ptrNext;
        if (i == length -1) {break;}
        ptrB_2 = ptrB_1;
        ptrB_1 = ptrSbody->get_block();
    }

    // 因为 eatFood 中有判定, 所以不担心误判为吃食物
    tryEatFood(oldTail_x, oldTail_y);
    tryEatHeart();

    return true;
}



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
    //每生成五次食物就生成一个爱心
    if (ptrMap->getFoodNum() == 5) {ptrMap-> setRandomItem(ItemType::HEART, "+");}
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



Entity::Entity(Map* map, SnakeBody* head, Direction init_dir, int init_len) {
    ptrMap  = map;
    dir     = init_dir;
    ptrHead = head;
    isAlive = true;
    overlap = false;

    int count = 0; 
    SnakeBody* ptr_S = ptrHead;
    BaseBlock* ptr_B = nullptr;
    BaseItem* temp_I = nullptr;

    for (int i = 0; i < init_len; i++) {

        ptr_S->set_snake(this);
        ptr_B = ptr_S->get_block();

        ptr_S = ptr_S->next();
        count++;
    }

    length = count;
}

bool Entity::moveForward() {
    // 检查是否有活性
    if (isAlive == false) {return false;}

    // 获取需要检测的方块列表
    std::vector<BaseBlock*> blocksNow(length);
    std::vector<BaseBlock*> blocksAhead(length);
    SnakeBody* ptr_S = ptrHead;
    BaseBlock* null_B = nullptr;
    SnakeBody* null_S = nullptr;
    for (int i = 0; i < length; i++) {
        if ( ! ptr_S) {exit(3);}

        blocksNow[i] = ptr_S->get_block();
        blocksNow[i]->getSnakeBody() = nullptr;
        blocksAhead[i] = nextBlock(ptrMap, ptr_S->get_block(), dir);
        ptr_S->get_block() = nullptr;
        ptr_S = ptr_S->next();
    }
    ptr_S = nullptr;

    BlockType blType = BlockType::EMPTY;
    BaseItem* ptr_I = nullptr;
    ItemType itType = ItemType::EMPTY;
    for (int i = 0; i < length; i++) {

        // 检测该方块是否在范围内
        if ( ! blocksAhead[i]) {isAlive = false; return false;}
        // 获取方块类型
        blType = blocksAhead[i]->type();
        switch (blType) {
            case BlockType::WALL:
            case BlockType::BARRIER:
                isAlive = false;
                ptr_S = ptrHead;
                for (int i = 0; i < length; i++) {
                    bond(blocksNow[i], ptr_S);
                    ptr_S = ptr_S->next();
                }
                return false;
        }

        ptr_S = blocksAhead[i]->getSnakeBody();
        if (ptr_S) {
            isAlive = false;
            ptr_S = ptrHead;
            for (int i = 0; i < length; i++) {
                bond(blocksNow[i], ptr_S);
                ptr_S = ptr_S->next();
            }
            return false;
        }
        ptr_S = nullptr;

        ptr_I = blocksAhead[i]->get_item();
        if ( ! ptr_I) {continue;}
        itType = ptr_I->type();

        // 撞到东西要删了之后重新生成
        switch (itType) {
            case ItemType::FOOD:
                blocksAhead[i]->clear_item();
                break;
            case ItemType::HEART:
                blocksAhead[i]->clear_item();
                break;
            case ItemType::SNAKEBODY:
                continue;
        }
    }

    // 移动
    BaseItem* temp_I = nullptr;
    ptr_S = ptrHead;
    for (int i = 0; i < length; i++) {
        if ( ! ptr_S) {exit(3);}

        bond(blocksAhead[i], ptr_S);

        ptr_S = ptr_S->next();
    }

    return true;
}
