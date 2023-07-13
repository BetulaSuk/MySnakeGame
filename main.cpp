//main.cpp
//主函数入口

#include "../MySnakeGame/renders/renders.h"

#include <string>

int main() {
    //随机数种子以及读取地图路径的初始化
    Random::resetRandomEngine();
    Path::setRootPath();

    GameBoard game;

    while (true) {
        bool choice;
        //欢迎界面
        choice = game.createWelcomeBoard();
        if (!choice) break;

        //选择游戏模式
        int mode = game.chooseMode();
        erase();
        refresh();

        //提前渲染信息栏和LOGO
        game.renderInformationBoard();
        game.renderLogo();

        //Classic Mode
        if (mode == 0)
        {
            //初始化地图，同时得到Snake，并生成第一个食物
            //剩余食物会在蛇吃到食物时候自动生成    
            //渲染最上面保持恒定的两个窗口
            Map map(game.getGameBoardHeight(), game.getGameBoardWidth());

            //通过地图初始化蛇，取得指针
            map.init_snake();
            Snake* snake = map.get_snake();

            //生成第一个食物，此后食物在moveforward()中自动生成
            map.setRandomItem(ItemType::FOOD, "#");

            //游戏主循环入口
            game.startGame(&map, snake);

            //结束界面，选择是否重新开始
            choice = game.renderRestartMenu(snake);
            if (choice == false) break;
        }

        //Word Snake Mode
        else if (mode == 1)
        {
            //初始化地图
            Map* map = new Map(game.getGameBoardHeight(), game.getGameBoardWidth());

            //指定蛇的初始化位置、length、heart
            WordSnake* snake = new WordSnake(map, game.getGameBoardHeight()/2, game.getGameBoardWidth()/2, 1, 3);

            //随机刷新英文字母（此处简单起见，刷新26个不同字母）
            setNRandomLetter(map, 26);
            snake->setNewFoodNum(26);

            //游戏主循环
            game.startWord(map, snake);

            //结束界面，选择是否重新开始
            choice = game.renderRestartMenu(snake);
            if (choice == false) break;
        }

        //SandBox
        else if (mode == 2) {
            //通过文件初始化Map
            //具体Map文件规则见README
            std::string partPath = "/data/maps/test.map";
            Map* ptrMap = loadMap(Path::fullPath(partPath));

            //取得Snake指针
            Snake* snake = ptrMap->get_snake();

            //游戏主循环入口
            game.startGame(ptrMap, snake);

            //结束界面，选择是否重新开始
            choice = game.renderRestartMenu(snake);
            if (choice == false) break;
        }
    }
}
