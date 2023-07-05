/**
 * definitions for map.h
*/

#include "map.h"

#include <iostream>


Map::Map(int input_width, int input_height) {
    data.resize(input_height);

    for (int i = 0; i < input_height; i++) {
        data[i].resize(input_width);

        for (int j = 0; j < input_width; j++) {
            data[i][j] = new BaseBlock(i, j);
        }
    }
}

Map::Map(std::string fileDir) {
    loadMap(fileDir);
}



