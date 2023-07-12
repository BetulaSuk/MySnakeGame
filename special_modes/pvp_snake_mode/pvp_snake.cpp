/**
 * definitions for pvp_snake.h
*/

#include "pvp_snake.h"

bool PvpSnake::moveForward() {
    
}






void Pvp_Map::init_two_snakes() {
    Ptrsnake1 = new PvpSnake(this, height/2, width*0.25, 2, 3);
    Ptrsnake2 = new PvpSnake(this, height/2, width*0.75, 2, 3);
}