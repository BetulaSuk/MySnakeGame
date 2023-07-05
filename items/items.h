/**
 * provide class:
 * - BaseItem
 * - Food
 * - Heart
*/

#ifndef _ITEMS_H_
#define _ITEMS_H_

#include "../blocks/blocks.h"
#include "../snake/snake.h"

enum class ItemType {
    BASEITEM  = 0,
    FOOD      = 1,
    HEART     = 2,
    SNAKEBODY = 3  // in ../snake/snake.h
};

class BaseItem {
    public:
        BaseItem(): ptrBlock(nullptr) {}
        BaseItem(BaseBlock& block): ptrBlock(&block) {}

        virtual ~BaseItem() = default;
        
        /* 获取基本信息 */

        virtual ItemType type() const {return TYPE;}
        int get_x() const {return ptrBlock->get_x();}
        int get_y() const {return ptrBlock->get_y();}

        /* Block 相关操作 */

        BaseBlock* get_block() {return ptrBlock;}
        /* 若需将 item 绑定到指定 block, 应使用 BaseBlock::set_item(...)
         * SnakeBody 则需使用 BaseBlock::attach(...) */
        void set_block(BaseBlock& block);

    protected:
        
        BaseBlock * ptrBlock;

    private:
        const static ItemType TYPE = ItemType::BASEITEM;
};


class Food: public BaseItem {
    public:
        Food(): BaseItem() {}
        Food(BaseBlock& block): BaseItem(block) {}

        virtual ~Food() = default;

        virtual ItemType type() const {return TYPE;}

    private:
        const static ItemType TYPE = ItemType::FOOD;
};


class Heart: public BaseItem {
    public:
        Heart(): BaseItem() {}
        Heart(BaseBlock& block): BaseItem(block) {}

        virtual ~Heart() = default;

        virtual ItemType type() const {return TYPE;}

    private:
        const static ItemType TYPE = ItemType::HEART;
};




#endif
