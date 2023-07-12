/**
 * provide class: 
 * - BaseBlock
 * - Wall
*/

#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "../items/items.h"

#include <string>
#include <vector>

class Color;
class BaseItem;
enum class ItemType;
class SnakeBody;
class Snake;

enum class BlockType {
    EMPTY     = -1,
    BASEBLOCK = 0,
    WALL      = 1,
    PORTAL    = 2,
    BARRIER   = 3
};


class BaseBlock {
    public:
        BaseBlock() = delete;
        BaseBlock(int input_x, int input_y):
            x(input_x), y(input_y), ptrItem(nullptr) {}

        // 在 block 销毁时会自动删除其上附着的 item! 
        virtual ~BaseBlock();

        /* 获取基本信息 */

        virtual BlockType type() const {return TYPE;}

        int get_x() const {return x;}
        int get_y() const {return y;}
        // 获取渲染用的字符串
        std::string toString() const {return displayString;}
        // 修改渲染用的字符串
        void setString(std::string s) {displayString = s;}

        Color* getColor() const {return colr;}
        void setColor(Color* ptrC) {colr = ptrC;}

        /* item 相关操作 */

        // 若有物品, 删除该物品, 不仅仅是指针设空 ! 
        void clear_item();
        BaseItem*& get_item();

        /* SnakeBody 相关操作 */

        SnakeBody*& getSnakeBody() {return ptrSnakeBody;}
        
        void attachSnakeBody(SnakeBody* ptrSbody);
        // 取消 block 对 SnakeBody 的<单向>连接 ! 
        void releaseSnakeBody();

    protected:
        int y;
        int x;

        BaseItem* ptrItem = nullptr;
        SnakeBody* ptrSnakeBody = nullptr;
    
    private:
        const static BlockType TYPE = BlockType::BASEBLOCK;

        std::string displayString = " ";

        Color* colr;
};


class Wall: public BaseBlock {
    public:
        Wall() = delete;
        Wall(int input_y, int input_x): BaseBlock(input_x, input_y) {}
        
        ~Wall() = default;

        BlockType type() const {return TYPE;}

    private:
        const static BlockType TYPE = BlockType::WALL;
};


class Barrier: public BaseBlock {
    public:
        Barrier() = delete;
        Barrier(int input_x, int input_y): BaseBlock(input_x, input_y) {}

        ~Barrier() = default;

        BlockType type() const {return TYPE;}

    private:
        const static BlockType TYPE = BlockType::BARRIER;
};


class Portal: public BaseBlock {
    public:
        Portal() = delete;
        Portal(int input_x, int input_y, int e_x, int e_y): BaseBlock(input_x, input_y), exit_x(e_x), exit_y(e_y) {};

        ~Portal() = default;

        int get_ex() const {return exit_x;}
        int get_ey() const {return exit_y;}

        BlockType type() const {return TYPE;}

    private:
        const static BlockType TYPE = BlockType::PORTAL;
        int exit_x, exit_y;
};



#endif