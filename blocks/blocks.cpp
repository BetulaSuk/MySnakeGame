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
    ptrItem = nullptr;
}

BaseItem* BaseBlock::get_item() {
    return ptrItem;
}

void BaseBlock::attachSnakeBody(SnakeBody* ptrSbody) {
    ptrSnakeBody = ptrSbody;
}

void BaseBlock::releaseSnakeBody() {
    if (ptrSnakeBody) {
        ptrSnakeBody = nullptr;
    }
}
