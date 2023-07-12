/**
 * provide class:
 * - Map
*/

#ifndef _MAP_H_
#define _MAP_H_

#include "../blocks/blocks.h"
#include "../items/items.h"

#include <vector>
#include <string>
#include <random>

class BaseBlock;
class BaseItem;
enum class ItemType;
enum class BlockType;
class SnakeBody;
class Snake;
class Entity;

enum class Mode {
    CLASSIC    = 0,
    STAGE      = 1,
    WORD_SNAKE = 2,
    TETRISNAKE = 3
};


enum class Direction {
    UP    = 0,
    RIGHT = 1,
    DOWN  = 2,
    LEFT  = 3
};


/** !!!!
 * x 对应第一个维度/高度; y 对应第二个维度/宽度. 
 * 这与 y 表示高度的习惯不同 !!
 * 原点位于左上角, 0 为起始坐标
*/

class Map;

void nextPos(int x, int y, int& next_x, int& next_y, Direction dir);

BaseBlock* nextBlock(Map* map, BaseBlock* block, Direction dir);

// 供生成食物时使用
bool canSetItem(BaseBlock* const block);

// 用于连接方块与物品/蛇身
void bond(BaseBlock* ptr_B, SnakeBody* ptr_S);
void bond(BaseBlock* ptr_B, BaseItem*  ptr_I);

// 如果文件与预期不符, 返回空指针
Map* loadMap(std::string fileDir);

bool carryCommand(Map* map, std::string com);


class Map {
    friend Map* loadMap(std::string fileDir);
    friend bool carryCommand(Map* map, std::string com);

    public:
        /* 初始化 */

        Map() = default;
        // 初始化: 空白地图, 创建并储存方块
        Map(int input_height, int input_width);
        // 初始化: 创建并绑定蛇
        void init_snake();

        ~Map();

        void loadMap(std::string fileDir);
        bool writeMap(std::string fileDir);

        /* 获取基本信息 */

        int get_width() const {return width;}
        int get_height() const {return height;}

        BaseBlock* at(int x, int y) {return data[x][y];}
        const std::vector<std::vector<BaseBlock*>> * const get_data() const {return &data;}

        Snake* get_snake() {return ptrSnake;}
        void set_snake(Snake* s) {ptrSnake = s;}
        std::vector<Entity*> * get_entity_list() {return &entityList;}

        /* 工具函数 */

        bool inRange(int x, int y) {return x >= 0 && y >= 0 && x < height && y < width;}
        bool onMap(BaseBlock* block);

        void setRandomItem(ItemType itType, std::string displayString);

        int getFoodNum() {return foodNum;}

    private:
        int width = 0;
        int height = 0;
        std::vector<std::vector<BaseBlock*>> data;

        Snake* ptrSnake = nullptr;
        std::vector<Entity*> entityList;

        //为生成爱心准备：
        int foodNum = 0;
};


/* 随机数生成相关工具 */

namespace Random {
    extern std::default_random_engine* R_engine;

    void resetRandomEngine();

    int randInt(int start, int end);
}


namespace Path {
    extern std::string rootPath;

    void setRootPath();

    std::string fullPath(std::string partPath);
}

#endif
