#include <iostream>
#include <curses.h>
#include <string>
#include <thread>
#include <chrono>
#include <fstream>
#include <sstream>
#include <filesystem>

#include "../snake/snake.h"
#include "../map/map.h"
#include "../blocks/blocks.h"
#include "../items/items.h"
#include "../renders/renders.h"

using namespace std;

string test_map = "/data/maps/normal_1.map";

int main() {
    string rootPath;
    stringstream sstr;

    sstr << filesystem::current_path();
    sstr >> rootPath;

    rootPath.pop_back();
    rootPath.erase(0, 1);

    cout << rootPath + test_map << endl;

    fstream ifs;
    ifs.open(rootPath + test_map);

    if ( ! ifs.is_open()) {cout << ">>> ?!!" << endl; ifs.close(); return 1;}

    ifs.seekg(0);

    string s1, s2;
    ifs >> s1;

    getline(ifs, s2);

    cout << ">>> first s:  " << s1 << endl;
    cout << ">>> second s: " << s2 << endl;

    ifs << "test\n";

    ifs.close();

    return 0;
}
