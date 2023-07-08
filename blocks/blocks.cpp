/**
 * definitions for blocks.h
*/

#include "blocks.h"
#include "../snake/snake.h"

BaseBlock::BaseBlock(int input_x, int input_y, BaseItem& item):
    x(input_x), y(input_y) {
        if (item.type() == ItemType::SNAKEBODY) {
            ptrItem = nullptr;
        }
        else {
            ptrItem = &item;
            item.set_block(*this);
        }
}

BaseBlock::~BaseBlock() {
    if (ptrItem != nullptr) {
        delete ptrItem;
    }
}

bool BaseBlock::set_item(BaseItem& item) {
    if (ptrItem == nullptr && item.type() != ItemType::SNAKEBODY) {
        ptrItem = &item;
        item.set_block(*this);
        return true;
    }
    else return false;
}

void BaseBlock::clear_item() {
    if (ptrItem != nullptr) {
        delete ptrItem;
    }
}

BaseItem* BaseBlock::get_item() {
    return ptrItem;
}

bool BaseBlock::attachSnakeBody(SnakeBody& sbody) {
    if (ptrSnakeBody == nullptr) {
        ptrSnakeBody = &sbody;
        sbody.set_block(*this);
        return true;
    }
    else return false;
}

void BaseBlock::releaseSnakeBody() {
    if (ptrSnakeBody != nullptr) {
        ptrSnakeBody->escapeBlock();
        ptrSnakeBody = nullptr;
    }
}
