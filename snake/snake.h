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

        virtual ~Snake();

        /* 获取基本信息 */

        int get_heart() const {return heart;}
        int get_len() const {return length;}
        SnakeBody* get_head() {return ptrHead;}

        Map* get_map() {return ptrMap;}

        /* 行动 */

        void changeDir(Direction new_dir) {dir = new_dir;}
        // 如果会超出地图边界, 返回 false, 否则返回 true
        bool moveForward();

        /* 判定 */

        ItemType actWithItem();
        // 检测是否受伤并返回, 更新生命值. 撞墙/自撞直接去世!!
        bool checkHurt();
        // 为了健壮性, 生命值小于零时也算作死亡, 并不报错
        bool isDead() const {return heart <= 0;}

    protected:
        bool eatFood();
        bool eatHeart();

        bool hitSelf() const;
        bool hitWall() const;

    private:
        int heart;
        int length;
        Direction dir;

        SnakeBody* ptrHead;
        Map* ptrMap;
};





#endif
