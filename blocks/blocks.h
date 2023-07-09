/**
 * provide class: 
 * - BaseBlock
 * - Wall
*/

#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "../items/items.h"

#include <string>

class BaseItem;
enum class ItemType;
class SnakeBody;
class Snake;

enum class BlockType {
    EMPTY     = -1,
    BASEBLOCK = 0,
    WALL      = 1
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

        /* item 相关操作 */

        bool have_item() const {return ptrItem != nullptr;}
        // 此格已有物品, 或尝试放入 SnakeBody: 不改变, 返回 false; 否则赋值并返回 true
        bool set_item(BaseItem* item);
        // 若有物品, 删除该物品, 不仅仅是指针设空 ! 
        void clear_item();
        BaseItem* get_item();

        /* SnakeBody 相关操作 */

        bool isSnakeAbove() const {return ptrSnakeBody != nullptr;}
        SnakeBody* getSnakeBody() {return ptrSnakeBody;}
        
        bool attachSnakeBody(SnakeBody* ptrSbody);
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
};


class Wall: public BaseBlock {
    public:
        Wall() = delete;
        Wall(int input_y, int input_x): BaseBlock(input_x, input_y) {}
        
        virtual ~Wall() = default;

        virtual BlockType type() const {return TYPE;}

    private:
        const static BlockType TYPE = BlockType::WALL;
};


#endif