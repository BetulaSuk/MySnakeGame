/**
 * definitions for items.h
*/

#include "items.h"
#include "../snake/snake.h"


BaseItem::BaseItem(BaseBlock* block) {
    ptrBlock = block;
    block->set_item(this);
}

int BaseItem::get_x() const {return ptrBlock->get_x();}
int BaseItem::get_y() const {return ptrBlock->get_y();}

void BaseItem::set_block(BaseBlock* block) {
    ptrBlock = block;
    block->set_item(this);
}


void SnakeBody::escapeBlock() {
    ptrBlock = nullptr;
}

void SnakeBody::set_block(BaseBlock* block) {
    ptrBlock = block;
    block->attachSnakeBody(this);
}
