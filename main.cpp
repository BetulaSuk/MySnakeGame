#include "../MySnakeGame/renders/renders.h"

int main() {
    GameBoard game;
    while (true) {
        bool choice;
        //欢迎界面
        choice = game.createWelcomeBoard();
        if (!choice) break;

        //初始化地图，同时得到Snake，并生成第一个食物
        //剩余食物会在蛇吃到食物时候自动生成
        Map map(game.getGameBoardHeight(), game.getGameBoardWidth());
        map.init_snake();
        Snake* snake = map.get_snake();
        Random::resetRandomEngine();
        map.setRandomItem(ItemType::FOOD, "#");

        //游戏主循环入口
        game.startGame(map, snake);

        //结束界面，选择是否重新开始
        choice = game.renderRestartMenu(snake);
        if (choice == false) return false;

        //复活蛇，重新开始
        //TODO：
        //继承heart
        snake -> revive();
        clear();
        refresh();
    }
}