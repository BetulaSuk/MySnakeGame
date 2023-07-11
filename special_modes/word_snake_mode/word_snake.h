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

int checkWord(std::string snakeStr);


class WordSnake: public Snake {
    public:
        WordSnake(): Snake() {}
        WordSnake(Map* map, int start_x, int start_y, int init_len, int init_heart): Snake(map, start_x, start_y, init_len, init_heart) {}
        WordSnake(Map* map, SnakeBody* head, int init_heart, Direction init_dir): Snake(map, head, init_heart, init_dir) {}
        
        ~WordSnake() = default;

        virtual bool moveForward();

        std::string getString() const;
};


#endif
