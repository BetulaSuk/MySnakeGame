/**
 * definitions for items.h
*/

#include "items.h"
#include "../snake/snake.h"


BaseItem::BaseItem(BaseBlock& block) {
    block.set_item(*this);
}

int BaseItem::get_x() const {return ptrBlock->get_x();}
int BaseItem::get_y() const {return ptrBlock->get_y();}

void BaseItem::set_block(BaseBlock& block) {
    ptrBlock = &block;
}


SnakeBody::SnakeBody(BaseBlock& block) {
    block.attachSnakeBody(*this);
}

void SnakeBody::escapeBlock() {
    ptrBlock = nullptr;
}
