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

enum class SnakeType {
    CLASSIC    = 0,
    WORD_SNAKE = 1,
    ENTITY     = 2,
    TETRISNAKE = 3
};


class Snake {
    public:
        Snake() = default;
        Snake(Map* map, int start_x, int start_y, int init_len, int init_heart);
        Snake(Map* map, SnakeBody* head, int init_heart, Direction init_dir);

        ~Snake();

        virtual SnakeType type() {return TYPE;}

        /* 获取基本信息 */

        int get_heart() const {return heart;}
        int get_len() const {return length;}
        Direction get_dir() const {return dir;}
        int get_point() const {return point;}

        SnakeBody* get_head() {return ptrHead;}
        Map* get_map() {return ptrMap;}

        /* 行动 */

        void changeDir(Direction new_dir);
        // 如果成功前进, 返回 true, 否则返回 false
        virtual bool moveForward();
        // 用于前进时检测, 为 Entity 类的功能而设置
        virtual bool canOverlap() const {return false;}

        bool revive();

        /* 判定 */

        bool checkAlive() const {return isAlive;}

    protected:
        /* 工具函数 */

        SnakeBody* getTailPtr();

        // 销毁头部的食物, 根据坐标长出新尾巴, 加分, 自动生成新食物
        bool tryEatFood(int newTail_x, int newTail_y);
        // 重载: 可指定新尾巴的渲染字符串;
        bool tryEatFood(int newTail_x, int newTail_y, std::string newTail_s);
        // 不会自动生成新的 Heart
        bool tryEatHeart();


        bool isAlive = true;
        int heart = 0;
        int length = 0;
        Direction dir;

        int point = 0;

        SnakeBody* ptrHead = nullptr;
        Map* ptrMap = nullptr;

    private:
        const static SnakeType TYPE = SnakeType::CLASSIC;
};

/**
 * class: Entity
 * 继承蛇, 但移动是整体平移, 且其Snakebody应当在block的ptrItem位置
 * isAlive 反映其是否有"活性", 即能否移动
 * length 反映其含有的Snakebody的数量
 * 新变量 overlap 反映其是否能与蛇重叠
*/
class Entity: public Snake {
    public:
        Entity(): Snake() {}
        Entity(Map* map, SnakeBody* head, Direction init_dir, int init_len);

        ~Entity() {};

        SnakeType type() {return TYPE;}

        void changeDir(Direction new_dir) {dir = new_dir;}

        // 保持形状不变整体移动
        bool moveForward();

        bool canOverlap() const {return overlap;}
        void setOverlap(bool ol) {overlap = ol;}
    
    private:
        bool overlap = true;

        const static SnakeType TYPE = SnakeType::ENTITY;
};


#endif
