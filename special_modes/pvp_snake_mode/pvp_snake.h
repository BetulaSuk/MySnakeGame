//new Mode: pvp


#ifndef _PVPSNAKE_H_
#define _PVPSNAKE_H_

#include "../../blocks/blocks.h"
#include "../../items/items.h"
#include "../../snake/snake.h"
#include "../../map/map.h"

#include <string>
#include <vector>


class PvpSnake: public Snake {
    public:
        PvpSnake() = delete;
        PvpSnake(Map* map, int start_x, int start_y, int init_len, int init_heart): Snake(map, start_x, start_y, init_len, init_heart) {}
        bool moveForward();

    private:
        std::vector<std::vector<int, int>> tails;


    
};



class Pvp_Map: public Map {
    public:
        void init_two_snakes();


    private:
        PvpSnake* Ptrsnake1 = nullptr;
        PvpSnake* Ptrsnake2 = nullptr;
        int height, width;



};


#endif