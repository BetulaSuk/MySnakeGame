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



