/**
 * provide class:
 * - BaseItem
 * - Food
 * - Heart
*/

#ifndef _ITEMS_H_
#define _ITEMS_H_

#include "../blocks/blocks.h"

#include <string>


class Color {
    public:
        Color(int red, int green, int blue) {
            this->red = red;
            this->green = green;
            this->blue = blue;
        }

        int red;
        int green;
        int blue;
};


enum class ItemType {
    EMPTY     = -1,
    BASEITEM  = 0,
    FOOD      = 1,
    HEART     = 2,
    SNAKEBODY = 3
};

class BaseBlock;
enum class BlockType;
class SnakeBody;
class Snake;

class BaseItem {
    public:
        BaseItem(): ptrBlock(nullptr) {}

        virtual ~BaseItem() = default;
        
        /* 获取基本信息 */

        virtual ItemType type() const {return TYPE;}
        int get_x() const;
        int get_y() const;
        // 获取渲染用的字符串
        std::string toString() const {return displayString;}
        // 修改渲染用的字符串
        void setString(std::string s) {displayString = s;}

        Color* getColor() const {return colr;}
        void setColor(Color* ptrC) {colr = ptrC;}

        /* Block 相关操作 */

        BaseBlock*& get_block() {return ptrBlock;}

    protected:
        
        BaseBlock * ptrBlock = nullptr;

    private:
        const static ItemType TYPE = ItemType::BASEITEM;

        std::string displayString = " ";

        Color* colr;
};


class Food: public BaseItem {
    public:
        Food(): BaseItem() {}

        ~Food() = default;

        ItemType type() const {return TYPE;}

    private:
        const static ItemType TYPE = ItemType::FOOD;
};


class Heart: public BaseItem {
    public:
        Heart(): BaseItem() {}

        ~Heart() = default;

        ItemType type() const {return TYPE;}

    private:
        const static ItemType TYPE = ItemType::HEART;
};


class SnakeBody: public BaseItem {
    friend class Snake;

    public:
        SnakeBody(): BaseItem() {}

        ~SnakeBody() = default;

        ItemType type() {return TYPE;}

        void set_snake(Snake* ptr_S);

        void escapeBlock();

        /* Snake 相关操作 */

        SnakeBody*& next() {return ptrNext;}
        void setNext(SnakeBody* next) {ptrNext = next;}
        Snake* getSnake() {return ptrSnake;}

    private:
        const static ItemType TYPE = ItemType::SNAKEBODY;

        SnakeBody* ptrNext = nullptr;
        Snake* ptrSnake = nullptr;
};


#endif
