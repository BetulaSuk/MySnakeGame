/**
 * provide class:
 * - Map
*/

#ifndef _MAP_H_
#define _MAP_H_

#include "../blocks/blocks.h"
#include "../items/items.h"
#include "../snake/snake.h"

#include <vector>
#include <string>

enum Direction {
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

void nextPos(int x, int y, int& next_x, int& next_y, Direction dir);

BaseBlock* nextBlock(Map& map, BaseBlock* block, Direction dir);


class Map {
    public:
        /* 初始化 */

        Map() = delete;
        // 初始化: 空白地图, 创建并储存方块, 创建并绑定蛇
        Map(int input_width, int input_height);
        Map(std::string fileDir);

        bool loadMap(std::string fileDir);
        bool writeMap(std::string fileDir);

        /* 获取基本信息 */

        int get_width() const {return width;}
        int get_height() const {return height;}

        BaseBlock* at(int x, int y) {return data[x][y];}
        const std::vector<std::vector<BaseBlock*>> * const get_data() const {return &data;}

        Snake* get_snake() {return ptrSnake;}

        /* 工具函数 */

        bool inRange(int x, int y) {return x >= 0 && y >= 0 && x < height && y < width;}
        bool onMap(BaseBlock* block);

        void setRandomItem(ItemType itType);

    private:
        int width;
        int height;
        std::vector<std::vector<BaseBlock*>> data;

        Snake* ptrSnake;
};


#endif
