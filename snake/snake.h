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
        SnakeBody(BaseBlock& block);

        virtual ~SnakeBody() = default;

        virtual ItemType type() {return TYPE;}

        void escapeBlock();

        /* Snake 相关操作 */

        SnakeBody* next() {return ptrNext;}
        Snake* getSnake() {return ptrSnake;}

    private:
        const static ItemType TYPE = ItemType::SNAKEBODY;

        SnakeBody* ptrNext;
        Snake* ptrSnake;
};


class Snake {
    friend class SnakeBody;

    public:
        Snake() = delete;
        Snake(Map& map, int start_x, int start_y, int init_len);

        /* 获取基本信息 */

        int get_len() const {return length;}
        SnakeBody* get_head() {return ptrHead;}

        /* 行动 */

        void changeDir(Direction new_dir) {dir = new_dir;}
        // 如果会超出地图边界, 返回 false, 否则返回 true
        bool moveForward();

        /* 判定 */

        bool hitSelf() const;
        bool hitWall() const;

    private:
        int length;
        Direction dir;

        SnakeBody* ptrHead;
        Map* ptrMap;
};





#endif
