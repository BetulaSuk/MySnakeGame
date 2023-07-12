/**
 * provide class: WordSnake, WordMap
*/

#ifndef _WORDSNAKE_H_
#define _WORDSNAKE_H_

#include "../../blocks/blocks.h"
#include "../../items/items.h"
#include "../../snake/snake.h"
#include "../../map/map.h"

#include <string>

// 返回值: -1 错误; 0 无单词; >0 单词的长度
int checkWord(std::string snakeStr);
// 判定两个字符是否是一个字母
bool isEqualChar(char ch_1, char ch_2);

class WordSnake: public Snake {
    public:
        WordSnake(): Snake() {}
        WordSnake(Map* map, int start_x, int start_y, int init_len, int init_heart): Snake(map, start_x, start_y, init_len, init_heart) {}
        WordSnake(Map* map, SnakeBody* head, int init_heart, Direction init_dir): Snake(map, head, init_heart, init_dir) {}
        
        //~WordSnake() {}

        SnakeType type() const {return TYPE;}

        bool canOverlap() const {return false;}

        // 如果遇到食物, 将其字符拼在尾部
        bool moveForward();

        std::string getString() const;

        // 如果组成了单词, 剪掉, 并返回Entity指针
        Entity* cutWord();

    private:
        const static SnakeType TYPE = SnakeType::WORD_SNAKE;
};


#endif
