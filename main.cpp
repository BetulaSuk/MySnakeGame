#include "../MySnakeGame/renders/renders.h"
#include <string>

int main() {
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

        game.renderInformationBoard();
        game.renderLogo();

        //TODO
        //Classic Mode
        if (mode == 0)
        {
            //初始化地图，同时得到Snake，并生成第一个食物
            //剩余食物会在蛇吃到食物时候自动生成    
            //渲染最上面保持恒定的两个窗口
            Map map(game.getGameBoardHeight(), game.getGameBoardWidth());
            //std::string partPath = "/data/maps/normal_1.map";
            //Map* ptrMap = loadMap(Path::fullPath(partPath));

            map.init_snake();
            Snake* snake = map.get_snake();

            map.setRandomItem(ItemType::FOOD, "#");

            //游戏主循环入口
            game.startGame(&map, snake);

            //结束界面，选择是否重新开始
            choice = game.renderRestartMenu(snake);
            if (choice == false) break;

            //复活蛇，重新开始
            //TODO：
            //继承heart
            //snake -> revive();
            //clear();
            //refresh();
        }
        //Word Snake Mode
        else if (mode == 1)
        {

            Map* map = new Map(game.getGameBoardHeight(), game.getGameBoardWidth());

            WordSnake* snake = new WordSnake(map, 10, 10, 2, 3);

            //主循环
            setNRandomLetter(map, 26);
            snake->setNewFoodNum(26);

            game.startWord(map, snake);

            choice = game.renderRestartMenu(snake);
            if (choice == false) break;
        }
        //SandBox
        else if (mode == 2) {
            std::string partPath = "/data/maps/test.map";
            Map* ptrMap = loadMap(Path::fullPath(partPath));

            Snake* snake = ptrMap->get_snake();

            //游戏主循环入口
            game.startGame(ptrMap, snake);

            //结束界面，选择是否重新开始
            choice = game.renderRestartMenu(snake);
            if (choice == false) break;
        }
        /*
        //PVP Mode
        case 2:
        case 3:
        */
    }
}
