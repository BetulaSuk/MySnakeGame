#include "../MySnakeGame/renders/renders.h"

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

        //TODO
        switch (mode)
        {
        //Classic Mode
        case 0:
            //初始化地图，同时得到Snake，并生成第一个食物
            //剩余食物会在蛇吃到食物时候自动生成
            
            //渲染最上面保持恒定的两个窗口
            game.renderInformationBoard();
            game.renderLogo();

            Map map(game.getGameBoardHeight(), game.getGameBoardWidth());

            map.init_snake();
            Snake* snake = map.get_snake();

            
            map.setRandomItem(ItemType::FOOD, "#");

            //游戏主循环入口
            game.startGame(map, snake);

            //结束界面，选择是否重新开始
            choice = game.renderRestartMenu(snake);
            if (choice == false) break;

            //复活蛇，重新开始
            //TODO：
            //继承heart
            snake -> revive();
            clear();
            refresh();
            break;
        /*
        //Word Snake Mode
        case 1:
        //PVP Mode
        case 2:
        case 3:
        */
        }
    }
}