/**
 * definitions for map.h
*/

#include "map.h"
#include "../snake/snake.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <filesystem>

void nextPos(int x, int y, int& next_x, int& next_y, Direction dir) {
    next_x = x;
    next_y = y;
    switch (dir) {
        case Direction::UP:    next_x = x - 1; break;
        case Direction::RIGHT: next_y = y + 1; break;
        case Direction::DOWN:  next_x = x + 1; break;
        case Direction::LEFT:  next_y = y - 1; break;
    }
}

BaseBlock* nextBlock(Map* map, BaseBlock* block, Direction dir) {
    BaseBlock* nextBlock = nullptr;

    if (not map->onMap(block)) {return nextBlock;}

    int init_x = block->get_x(),
        init_y = block->get_y();
    int next_x = 0,
        next_y = 0;

    //传送门下的蛇的下一步位置
    //TODO
    if (block -> type() == BlockType::PORTAL) {
        Portal* entrance = reinterpret_cast<Portal*>(block);
        int exit_x = entrance -> get_ex(), exit_y = entrance -> get_ey();
        next_x = exit_x;
        next_y = exit_y;
    }
    else nextPos(init_x, init_y, next_x, next_y, dir);

    if (not map->inRange(next_x, next_y)) {return nextBlock;}

    nextBlock = map->at(next_x, next_y);
    return nextBlock;
}

bool canSetItem(BaseBlock* const block) {
    BlockType B_type = block->type();
    switch (B_type) {
        case BlockType::BASEBLOCK:
            return true;
        default:
            return false;
    }
}

void bond(BaseBlock* ptr_B, SnakeBody* ptr_S) {
    if (ptr_B && ptr_S) {
        ptr_B->attachSnakeBody(ptr_S);
        ptr_S->set_block(ptr_B);
    } else {exit(2);}
}
void bond(BaseBlock* ptr_B, BaseItem*  ptr_I) {
    if (ptr_B && ptr_I && ptr_I->type() != ItemType::SNAKEBODY) {
        ptr_B->set_item(ptr_I);
        ptr_I->set_block(ptr_B);
    } else {exit(2);}
}

Map* loadMap(std::string fileDir) {
    Map* ptrMap = nullptr;
    try {

    std::ifstream mapFile;
    mapFile.open(fileDir, std::ios::in);
    if ( ! mapFile.is_open()) {mapFile.close(); throw 1;}

    char ch1, ch2;
    mapFile >> ch1;
    if (ch1 != 'm') {mapFile.close(); throw 1;}

    // 创建新的空地图, 设置地图大小
    int height, width;
    mapFile >> height >> width;
    ptrMap = new Map();
    ptrMap->width  = width;
    ptrMap->height = height;
    ptrMap->data.resize(height);
    for (int i = 0; i < height; i++) {
        ptrMap->data[i].resize(width);
    }

    std::string aline = "",
                displayStr = " ";

    // 相当于光标换行
    std::getline(mapFile, aline); 

    for (int i = 0; i < height; i++) {
        std::getline(mapFile, aline);

        for (int j = 0; j < width; j++) {
            ch1 = aline[2 * j];
            ch2 = aline[2 * j + 1];
            displayStr[0] = ch2;

            switch (ch1) {
                case '0': ptrMap->data[i][j] = new BaseBlock(i, j); break;
                case '1': ptrMap->data[i][j] = new Wall(i, j); break;
                // 由于传送门生成需要更多参数, 先使用基本方块占位, 在命令执行阶段再设置
                case '2': ptrMap->data[i][j] = new BaseBlock(i, j); break;
                /* TODO 添加新的方块类型 */
                default: mapFile.close(); throw 1;
            }

            ptrMap->data[i][j]->setString(displayStr);
        }
    }

    int tempi = 0;
    mapFile >> ch1;
    if (ch1 == 'f') {
        mapFile >> tempi;
        std::getline(mapFile, aline); // 光标换行
        for (int i = 0; i < tempi; i++) {
            std::getline(mapFile, aline);

            //临时注释！
            //if ( ! carryCommand(ptrMap, aline)) {mapFile.close(); throw 1;}
        }
    }

    mapFile.close();
    
    } catch (...) {
        if (ptrMap->ptrSnake) {delete ptrMap->ptrSnake;}
        delete ptrMap; return nullptr;
    }

    return ptrMap;
}

//临时注释！
/*bool carryCommand(Map* map, std::string com) {
    std::stringstream sstr;
    sstr << com;

    /** 命令说明:
     * 第一个字符决定命令性质
     * - b: 创建方块, 下一个数字决定方块种类, 接着的两个数字为位置,
     *      再然后是需要传入构造函数的参数
     * - i: 创建物品, 种类, 位置, 渲染用字符! , 其他可能参数
     * - s: 创建蛇身, 位置, 渲染字符, 下一节的位置
     * - c: 声明蛇, 蛇头的位置, 初始生命, 初始方向
    */

    char comType;
    sstr >> comType;
    int x, y; std::string displayStr;
    switch (comType) {
        // 注释
        case '#': return true; 
        case 'b':
            int bType;
            sstr >> bType >> x >> y;
            switch (bType) {
                case 0:
                    displayStr = map->data[x][y]->toString();
                    delete map->data[x][y];
                    map->data[x][y] = new BaseBlock(x, y);
                    map->data[x][y]->setString(displayStr);
                    break;
                case 1:
                    displayStr = map->data[x][y]->toString();
                    delete map->data[x][y];
                    map->data[x][y] = new Wall(x, y);
                    map->data[x][y]->setString(displayStr);
                    break;
                case 2:
                    int e_x, e_y;
                    sstr >> e_x >> e_y;
                    displayStr = map->data[x][y]->toString();
                    delete map->data[x][y];
                    map->data[x][y] = new Portal(x, y, e_x, e_y);
                    map->data[x][y]->setString(displayStr);
                    break;
            }
            break;

        case 'i':
            int iType; BaseItem* ptr_I;
            sstr >> iType >> x >> y >> displayStr;
            switch (iType) {
                case 0:
                    ptr_I = new BaseItem();
                    ptr_I->setString(displayStr);
                    bond(map->data[x][y], ptr_I);
                    break;
                case 1:
                    ptr_I = new Food();
                    ptr_I->setString(displayStr);
                    bond(map->data[x][y], ptr_I);
                    break;
                case 2:
                    ptr_I = new Heart();
                    ptr_I->setString(displayStr);
                    bond(map->data[x][y], ptr_I);
                    break;
                /* TODO */
            }
            break;

        case 's':
            int next_x, next_y; SnakeBody* ptr_S;
            sstr >> x >> y >> displayStr >> next_x >> next_y;
            ptr_S = new SnakeBody();
            ptr_S->setString(displayStr);
            bond(map->data[x][y], ptr_S);

            if (next_x < 0 || next_y < 0) {break;} // 蛇尾
            else if (map->inRange(next_x, next_y) &&
                    map->data[next_x][next_y]->getSnakeBody())
                 {ptr_S->setNext(map->data[next_x][next_y]->getSnakeBody());}
            else {return false;}
            break;
        
        case 'c':
            int init_heart, dir_int;
            sstr >> x >> y >> init_heart >> dir_int;
            Direction init_dir = static_cast<Direction>(dir_int);
            
            if ( ! map->inRange(x, y)) {return false;}
            SnakeBody* head = map->data[x][y]->getSnakeBody();
            if ( ! head) {return false;}

            map->ptrSnake = new Snake(map, head, init_heart, init_dir);
            break;
    }

    return true;
}*/



// 初始化: 创建并储存方块, 创建并绑定蛇
Map::Map(int input_height, int input_width) {
    height = input_height;
    width  = input_width;

    data.resize(height);

    for (int i = 0; i < height; i++) {
        data[i].resize(width);

        for (int j = 0; j < width; j++) {
            // 边缘是墙
            if (i == 0 || i == height -1 ||
                j == 0 || j == width -1) {
                    /*data[i][j] = new Wall(i, j);
                    data[i][j]->setString("+");*/

                    //尝试将周围的变成传送门
                    if (i == 0) data[i][j] = new Portal(i, j, height-2, j);
                    else if (j == 0) data[i][j] = new Portal(i, j, i, width-2);
                    else if (i == height-1) data[i][j] = new Portal(i, j, 1, j);
                    else if (j == width-1) data[i][j] = new Portal(i, j, i, 1);
                    else data[i][j] = new Wall(i, j);
            }
            else {data[i][j] = new BaseBlock(i, j);}
        }
    }
    //临时生成一组传送门
    /*data[5][5] = new Portal(5, 5, 15, 30);
    data[5][5] -> setString("P");
    data[15][15] = new Portal(15, 15, 5, 30);
    data[15][15] -> setString("P");*/
}

void Map::init_snake() {
    ptrSnake = new Snake(this, height/2, width/2, 2, 3);
}


Map::~Map() {
    delete ptrSnake;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if ( ! data[i][j]) {continue;}
            data[i][j]->clear_item();
            delete data[i][j];
        }
    }
}

bool Map::writeMap(std::string fileDir) {
    /* TODO */
}

bool Map::onMap(BaseBlock* block) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (block && block == data[i][j]) {
                return true;
            }
        }
    }
    return false;
}

void Map::setRandomItem(ItemType itType, std::string displayString) {
    int rand_x = 0,
        rand_y = 0;
    BaseBlock* tarBlock;

    do {
        rand_x = Random::randInt(0, height - 1);
        rand_y = Random::randInt(0,  width - 1);
        tarBlock = data[rand_x][rand_y];
    } while ( ! canSetItem(tarBlock)
        || tarBlock->get_item() 
        || tarBlock->getSnakeBody());

    BaseItem* newItem;
    switch (itType) {
        case ItemType::FOOD:
            newItem = new Food();
            this -> foodNum++;
            break;
        case ItemType::HEART:
            newItem = new Heart();
            this -> foodNum = 0;
            break;
    }
    if (newItem) {
        newItem->setString(displayString);
        bond(tarBlock, newItem);
    }
}


/* definitions of namespace Random */

std::default_random_engine* Random::R_engine;

void Random::resetRandomEngine() {
    std::random_device seed;
    R_engine = new std::default_random_engine(seed());
}

int Random::randInt(int start, int end) {
    std::uniform_int_distribution<int> dis(start, end);
    return dis(*R_engine);
}


/* definitions of namespace Path */

std::string Path::rootPath;

void Path::setRootPath() {
    std::stringstream sstr;
    sstr << std::filesystem::current_path();
    sstr >> rootPath;

    // 有双引号, 掐头去尾
    rootPath.pop_back();
    rootPath.erase(0, 1);
}

std::string Path::fullPath(std::string partPath) {
    return rootPath + partPath;
}
