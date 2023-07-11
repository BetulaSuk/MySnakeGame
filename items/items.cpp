/**
 * definitions for items.h
*/

#include "items.h"
#include "../snake/snake.h"

Color setColor(int red, int green, int blue) {
    Color c;
    c.red = red;
    c.green = green;
    c.blue = blue;
    return c;
}


BaseItem::BaseItem(BaseBlock* block) {
    ptrBlock = block;
    block->set_item(this);
}

int BaseItem::get_x() const {return ptrBlock->get_x();}
int BaseItem::get_y() const {return ptrBlock->get_y();}


void BaseItem::set_block(BaseBlock* block) {
    ptrBlock = block;
}


void SnakeBody::escapeBlock() {
    ptrBlock = nullptr;
}

void SnakeBody::set_block(BaseBlock* block) {
    ptrBlock = block;
}

void SnakeBody::set_snake(Snake* ptr_S) {
    ptrSnake = ptr_S;
}
