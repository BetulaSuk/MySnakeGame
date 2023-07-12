/**
 * definitions for items.h
*/

#include "items.h"
#include "../snake/snake.h"


int BaseItem::get_x() const {return ptrBlock->get_x();}
int BaseItem::get_y() const {return ptrBlock->get_y();}


void SnakeBody::escapeBlock() {
    ptrBlock = nullptr;
}


void SnakeBody::set_snake(Snake* ptr_S) {
    ptrSnake = ptr_S;
}
