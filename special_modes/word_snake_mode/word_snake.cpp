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

        for (int j = 1; j < aline.length(); j++) {
            if (i >= snakeStr.length()) {
                match = false; 
                break;
            }
            if ( ! isEqualChar(snakeStr[i], aline[i])) {
                match = false;
                break;
            }
        }

        if (match) {
            word_list.close(); 
            return aline.length();
        }
    }

    word_list.close();
    return 0;
}

bool isEqualChar(char ch_1, char ch_2) {
    int chi_1 = (int)ch_1,
        chi_2 = (int)ch_2;

    if (((chi_1 >= 65 && chi_1 <= 90) || (chi_1 >= 97 && chi_1 <= 122))
        && ((chi_2 >= 65 && chi_2 <= 90) || (chi_2 >= 97 && chi_2 <= 122)))
        {
            if (std::abs(chi_1 - chi_2) == 32) {return true;}
        }

    return false;
}


Entity::Entity(Map* map, SnakeBody* head, Direction init_dir) {
    ptrMap  = map;
    dir     = init_dir;
    ptrHead = head;

    int count = 0; 
    SnakeBody* ptr_S = ptrHead;
    BaseBlock* ptr_B;
    BaseItem* temp_I;
    while (ptr_S) {
        ptr_S->set_snake(this);
        ptr_B = ptr_S->get_block();
        ptr_B->releaseSnakeBody();
        temp_I = ptr_S;
        bond(ptr_B, temp_I);
        count++;
    }
    length = count;
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
        case BlockType::BARRIER:
            heart--;
            if (heart <= 0) {
                isAlive = false;
                return false;
            }
            break;
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

    // 获取前方方块上的物品类型
    BaseItem* itemAhead = blockAhead->get_item();
    ItemType typeItem = ItemType::EMPTY;
    std::string displayStr = "#"; // 用于之后创建新蛇尾
    if (itemAhead) {
        typeItem = itemAhead->type();
        displayStr = itemAhead->toString();    
    }

    // 撞Entity的判定
    if (typeItem == ItemType::SNAKEBODY) {
        SnakeBody* temp_S = reinterpret_cast<SnakeBody*>(itemAhead);
        if ( ! temp_S->getSnake()->canOverlap()) {
            heart--;
            if (heart <= 0) {
                isAlive = false;
                return false;
            }
        }
    }

    // 提前获取此时的尾部坐标, 为可能吃食物的情况做准备
    int oldTail_x, oldTail_y;
    SnakeBody* ptrTail = getTailPtr();
    oldTail_x = ptrTail->get_x();
    oldTail_y = ptrTail->get_y();

    // 向前挪动: 从头开始一点点向前伸
    SnakeBody* ptrSbody = ptrHead;
    BaseBlock* ptrB_1 = ptrHead->get_block();
    BaseBlock* ptrB_2 = nextBlock(ptrMap, ptrB_1, dir);

    for (int i = 0; i < length; i++) {
        bond(ptrB_2, ptrSbody);
        ptrB_1->releaseSnakeBody();

        ptrSbody = ptrSbody->next();
        if ( ! ptrSbody) {break;}
        ptrB_2 = ptrB_1;
        ptrB_1 = ptrSbody->get_block();
    }

    // 因为 eatFood 中有判定, 所以不担心误判为吃食物
    tryEatFood(oldTail_x, oldTail_y, displayStr);
    tryEatHeart();

    return true;
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

Entity* WordSnake::cutWord() {
    int word_len = checkWord(getString());
    if (word_len == 0) {return nullptr;}

    int new_len = length - word_len;
    if (new_len <= 0) {exit(3);}

    SnakeBody* new_tail = ptrHead;
    for (int i = 1; i < new_len; i++) {
        new_tail = new_tail->next();
    }

    SnakeBody* en_head = new_tail->next();
    Direction en_dir = static_cast<Direction>((static_cast<int>(dir) + 2) % 4);
    Entity* ptr_E = new Entity(ptrMap, en_head, en_dir);

    new_tail->setNext(nullptr);
    ptrMap->get_entity_list()->push_back(ptr_E);
    
    return ptr_E;
}
