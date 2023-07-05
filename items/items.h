/**
 * provide class:
 * - BaseItem
 * - FoodItem
 * - HeartItem
*/

#ifndef _ITEMS_H_
#define _ITEMS_H_

#include "../blocks/blocks.h"
#include "../snake/snake.h"

class BaseItem {
    public:
        BaseItem() = delete;
        BaseItem(BaseBlock& block):
            ptrBlock(&block) {}
        virtual ~BaseItem() = default;
        
        virtual int get_ID() const {return item_ID;}

        virtual BaseBlock* get_block() {return ptrBlock;}

        virtual int get_x() const;
        virtual int get_y() const;

        virtual bool run_item_func() = 0;

    private:
        const static int item_ID = 0;

        BaseBlock * ptrBlock;
};



#endif
