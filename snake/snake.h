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

class BaseItem;
class Food;
class Heart;
// SnakeBody 定义在 items 中!!!
class SnakeBody;
class BaseBlock;
enum class ItemType;
enum class BlockType;
class Map;
enum class Direction;

class Snake {

    public:
        Snake() = delete;
        Snake(Map* map, int start_x, int start_y, int init_len, int init_heart);

        virtual ~Snake();

        /* 获取基本信息 */

        int get_heart() const {return heart;}
        int get_len() const {return length;}
        Direction get_dir() const {return dir;}
        int get_point() const {return point;}

        SnakeBody* get_head() {return ptrHead;}
        Map* get_map() {return ptrMap;}

        /* 行动 */

        void changeDir(Direction new_dir) {dir = new_dir;}
        // 如果成功前进, 返回 true, 否则返回 false
        bool moveForward();

        bool revive();

        /* 判定 */

        bool checkAlive() const {return isAlive;}

    protected:
        /* 工具函数 */

        SnakeBody* getTailPtr();

        // 销毁头部的食物, 根据坐标长出新尾巴, 加分.
        bool eatFood(int newTail_x, int newTail_y);
        // 重载: 可指定新尾巴的渲染字符串;
        bool eatFood(int newTail_x, int newTail_y, std::string newTail_s);

    private:
        bool isAlive = true;
        int heart;
        int length;
        Direction dir;

        int point;

        SnakeBody* ptrHead = nullptr;
        Map* ptrMap = nullptr;
};





#endif
