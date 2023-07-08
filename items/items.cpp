/**
 * definitions for items.h
*/

#include "items.h"

BaseItem::BaseItem(BaseBlock& block) {
    block.set_item(*this);
}

void BaseItem::set_block(BaseBlock& block) {
    ptrBlock = &block;
}


void Food::item_func(Snake& s) {
    s.point++;
}

void Heart::item_func(Snake& s) {

}