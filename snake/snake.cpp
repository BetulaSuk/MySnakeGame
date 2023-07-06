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
    SnakeBody* ptr = ptrHead;
    for (int i = 1; i < init_len; i++) {
        nextPos(x, y, x, y, DOWN);
        ptr->ptrNext = new SnakeBody(*map.at(x, y));
        ptr = ptr->ptrNext;
        ptr->ptrSnake = this;
    }

    ptrMap = &map;
}

// 类似蚯蚓蠕动: 从头部开始向前伸, 身体一节节跟上
bool Snake::moveForward() {
    if (nextBlock(*ptrMap, ptrHead->get_block(), dir) == nullptr) {
        return false;
    }

    SnakeBody* ptrSbody = ptrHead;
    BaseBlock* tempB_1 = ptrHead->get_block();
    BaseBlock* tempB_2 = nextBlock(*ptrMap, ptrHead->get_block(), dir);

    for (int i = 0; i < length; i++) {
        tempB_2->attachSnakeBody(*ptrSbody);
        ptrSbody = ptrSbody->ptrNext;
        tempB_2 = tempB_1;

        if (ptrSbody == nullptr) {break;}
        else {tempB_1 = ptrSbody->get_block();}
    }

    return true;
}

