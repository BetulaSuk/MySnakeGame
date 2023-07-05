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


class Map {
    public:
        /* 初始化 */

        Map() = delete;
        Map(int input_width, int input_height);
        Map(std::string fileDir);

        bool loadMap(std::string fileDir);

        /* 获取基本信息 */

        int getWidth() const {return width;}
        int getHeight() const {return height;}

        BaseBlock* at(int x, int y) {return data[x][y];}
        const std::vector<std::vector<BaseBlock*>> * const getDataPtr() const {return &data;}

        Snake* getSnake() {return ptrSnake;}

    private:
        int width;
        int height;
        std::vector<std::vector<BaseBlock*>> data;

        Snake* ptrSnake;
};


#endif
