/**
 * definitions for blocks.h
*/

#include "blocks.h"
#include "../snake/snake.h"


BaseBlock::~BaseBlock() {
    if (ptrItem) delete ptrItem;
}


void BaseBlock::clear_item() {
    if (ptrItem) delete ptrItem;
    ptrItem = nullptr;
}


BaseItem*& BaseBlock::get_item() {
    return ptrItem;
}


void BaseBlock::attachSnakeBody(SnakeBody* ptrSbody) {
    ptrSnakeBody = ptrSbody;
}


void BaseBlock::releaseSnakeBody() {
    ptrSnakeBody = nullptr;
}

