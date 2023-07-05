/**
 * provide class: 
 * - SnakeBody(item)
 * - Snake
*/

#ifndef _SNAKE_H_
#define _SNAKE_H_

#include <string>

#include "../items/items.h"
#include "../blocks/blocks.h"
#include "../map/map.h"


class SnakeBody: public BaseItem {
    friend class Snake;

    public:
        SnakeBody(): BaseItem() {}
        SnakeBody(BaseBlock& block): BaseItem(block) {}

        virtual ~SnakeBody() = default;

        virtual ItemType type() {return TYPE;}

        // 获取渲染用的字符串
        std::string toString() const {return displayString;}

        void escapeBlock();

        /* Snake 相关操作 */

        SnakeBody* next() {return ptrNext;}
        Snake* getSnake() {return ptrSnake;}

    private:
        const static ItemType TYPE = ItemType::SNAKEBODY;

        std::string displayString;

        SnakeBody* ptrNext;
        Snake* ptrSnake;
};


class Snake {
    friend class SnakeBody;

    public:
        Snake() = delete;
        Snake(Map& map, int start_x, int start_y, int init_len);

        /* 获取基本信息 */

        int getLen() const {return length;}
        SnakeBody* getHeadPtr() {return ptrHead;}

        /* 行动 */
        bool moveForward();

    private:
        int length;
        Direction dir;

        SnakeBody* ptrHead;
        Map* ptrMap;
};





#endif
