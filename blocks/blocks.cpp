/**
 * definitions for blocks.h
*/

#include "blocks.h"
#include "../snake/snake.h"


BaseBlock::~BaseBlock() {
    if (ptrItem) {
        delete ptrItem;
    }
}

bool BaseBlock::set_item(BaseItem* item) {
    if ( ! ptrItem && item->type() != ItemType::SNAKEBODY) {
        ptrItem = item;
        return true;
    }
    else return false;
}

void BaseBlock::clear_item() {
    if (ptrItem) {
        delete ptrItem;
    }
}

BaseItem* BaseBlock::get_item() {
    return ptrItem;
}

bool BaseBlock::attachSnakeBody(SnakeBody* ptrSbody) {
    if (ptrSnakeBody) {return false;}
    else {
        ptrSnakeBody = ptrSbody;
        return true;
    }
}

void BaseBlock::releaseSnakeBody() {
    if (ptrSnakeBody) {
        ptrSnakeBody->escapeBlock();
        ptrSnakeBody = nullptr;
    }
}
