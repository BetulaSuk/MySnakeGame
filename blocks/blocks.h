/**
 * provide class: 
 * - BaseBlock
 * - Wall
*/

#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "../snake/snake.h"
#include "../items/items.h"

#include <string>

enum class BlockType {
    BASEBLOCK = 0,
    WALL      = 1
};


class BaseBlock {
    public:
        BaseBlock() = delete;
        BaseBlock(int input_x, int input_y):
            x(input_x), y(input_y), ptrItem(nullptr) {}
        BaseBlock(int input_x, int input_y, BaseItem& item);

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
        bool set_item(BaseItem& item);
        // 若有物品, 删除该物品, 不仅仅是指针设空 ! 
        void clear_item();
        BaseItem* get_item();

        /* SnakeBody 相关操作 */

        bool isSnakeAbove() const {return ptrSnakeBody != nullptr;}
        SnakeBody* getSnakeBody() {return ptrSnakeBody;}
        // 已连有 SnakeBody, 不改变, 返回 false; 否则赋值并返回 true
        bool attachSnakeBody(SnakeBody& sbody);
        // 取消 block 与 SnakeBody 的<双向>连接 ! 
        void releaseSnakeBody();

    protected:
        int x;
        int y;

        BaseItem* ptrItem;
        SnakeBody* ptrSnakeBody;
    
    private:
        const static BlockType TYPE = BlockType::BASEBLOCK;

        std::string displayString;
};


class Wall: public BaseBlock {
    public:
        Wall() = delete;
        Wall(int input_x, int input_y): BaseBlock(input_x, input_y) {}
        Wall(int input_x, int input_y, BaseItem& item):
            BaseBlock(input_x, input_y, item) {}
        
        virtual ~Wall() = default;

        virtual BlockType type() const {return TYPE;}

    private:
        const static BlockType TYPE = BlockType::WALL;
};


#endif