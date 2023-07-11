/**
 * definitions for word_snake.h
*/

#include "word_snake.h"

#include <fstream>
#include <sstream>

int checkWord(std::string snakeStr) {
    if (snakeStr.length() == 0) {return -1;}

    int ret = 0;
    // 需要提前初始化好 Path::rootPath
    std::ifstream word_list;
    std::stringstream sstr;

    char first_ch = snakeStr[0];
    std::string wl_path;

    sstr << "/data/word_lists/" << first_ch << ".wl";
    sstr >> wl_path;
    wl_path = Path::fullPath(wl_path);

    word_list.open(wl_path);
    if ( ! word_list.is_open()) {return -1;}

    int line_num = 0;
    std::string aline;

    word_list >> line_num;
    std::getline(word_list, aline); // 光标换行

    bool match = false;
    for (int i = 0; i < line_num; i++) {
        std::getline(word_list, aline);

        for (int j = 1; j < snakeStr.length(); j++) {
            if (snakeStr[j] != aline[j]) {match = false;}
        }

        if (match) {
            word_list.close(); 
            return aline.length();
        }
    }

    word_list.close();
    return 0;
}

bool WordSnake::moveForward() {
    // 检查蛇是否死亡
    if (isAlive == false) {return false;}

    BaseBlock* blockAhead = nextBlock(ptrMap, ptrHead->get_block(), dir);
    BlockType  typeBlock  = blockAhead->type();

    // 检查是否超出地图边界
    if ( ! blockAhead) {return false;}

    // 检查前方方块是否可踏足
    switch (typeBlock) {
        case BlockType::WALL:
            isAlive = false;
            heart = 0;
            return false;
        // TODO 添加更多方块类型时此处可能要增加判定
        default:
            break;
    }

    // 检查前方方块是否有蛇身
    SnakeBody* ptrSAhead = blockAhead->getSnakeBody();

    if (ptrSAhead) {
        isAlive = false;
        heart = 0;
        return false;
    }

    BaseItem* itemAhead = blockAhead->get_item();
    ItemType typeItem = ItemType::EMPTY;
    if (itemAhead) {typeItem = itemAhead->type();}

    /* 以下为与 Snake::moveForward() 不同的部分 */

    

}

std::string WordSnake::getString() const {
    std::string snakeStr;
    SnakeBody* ptr_S = ptrHead;
    for (int i = 0; i < length; i++) {
        snakeStr.append(ptr_S->toString());
        ptr_S = ptr_S->next();
    }
    return snakeStr;
}

