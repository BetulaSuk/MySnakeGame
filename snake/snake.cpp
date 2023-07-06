/**
 * definitions for snake.h
*/

#include "snake.h"


SnakeBody::SnakeBody(BaseBlock& block) {
    block.attachSnakeBody(*this);
}

void SnakeBody::escapeBlock() {
    ptrBlock = nullptr;
}

// 初始化: 蛇身创建, 蛇身绑定方块, 蛇身绑定蛇, 蛇绑定地图
Snake::Snake(Map& map, int start_x, int start_y, int init_len) {
    ptrHead = new SnakeBody(*map.at(start_x, start_y));
    ptrHead->ptrSnake = this;

    int x = start_x,
        y = start_y;
    if (not map.inRange(start_x, start_y)) {exit(1);}

    SnakeBody* ptr = ptrHead;
    for (int i = 1; i < init_len; i++) {
        nextPos(x, y, x, y, DOWN);

        if (not map.inRange(x, y)) {exit(1);}

        ptr->ptrNext = new SnakeBody(*map.at(x, y));
        ptr = ptr->ptrNext;
        ptr->ptrSnake = this;
        ptr->setString("@");
    }

    ptrMap = &map;
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

// 类似蚯蚓蠕动: 从头部开始向前伸, 身体一节节跟上
bool Snake::moveForward() {
    SnakeBody* ptrSbody = ptrHead;
    BaseBlock* tempB_1 = ptrHead->get_block();
    BaseBlock* tempB_2 = nextBlock(*ptrMap, ptrHead->get_block(), dir);

    if (tempB_2 = nullptr) {return false;}

    for (int i = 0; i < length; i++) {
        tempB_2->attachSnakeBody(*ptrSbody);
        ptrSbody = ptrSbody->ptrNext;
        tempB_2 = tempB_1;

        if (ptrSbody == nullptr) {break;}
        else {tempB_1 = ptrSbody->get_block();}
    }

    return true;
}

/* 判定 */

ItemType Snake::actWithItem() {
    BaseItem* ptrIt = ptrHead->get_block()->get_item();
    ItemType itType = ItemType::EMPTY;

    if (ptrIt == nullptr) {return itType;}
    else {itType = ptrIt->type();}

    switch (itType) {
        case ItemType::FOOD:  eatFood(); break;
        case ItemType::HEART: eatHeart(); break;
    }

    return itType;
}

bool Snake::checkHurt() {
    if (hitWall() || hitSelf()) {
        heart = 0;
        return true;
    }

    /* TODO */
}

/* 工具函数 */

bool Snake::eatFood() {
    BaseItem* food = ptrHead->get_block()->get_item();

    if (food == nullptr || food->type() != ItemType::FOOD)
        {return false;}
    
    SnakeBody* oldTail = ptrHead;
    for (int i = 1; i < length; i++) {
        oldTail = oldTail->ptrNext;
    }

    oldTail->ptrNext = 
}

bool Snake::hitSelf() const {
    SnakeBody* ptrSbody = ptrHead;

    while (ptrSbody != nullptr) {
        ptrSbody = ptrSbody->ptrNext;
        if (ptrSbody = ptrHead) {return true;}
    }
    return false;
}

bool Snake::hitWall() const {
    SnakeBody* ptrSbody = ptrHead;

    while (ptrSbody != nullptr) {
        ptrSbody = ptrSbody->ptrNext;
        if (ptrSbody->get_block()->type() == BlockType::WALL) 
            {return true;}
    }
    return false;
}
