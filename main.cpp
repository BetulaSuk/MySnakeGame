#include "../MySnakeGame/renders/renders.h"

int main() {
    GameBoard game;
    while (true) {
        bool choice;
        choice = game.createWelcomeBoard();
        if (!choice) break;

        Map map(game.getGameBoardHeight(), game.getGameBoardWidth());

        map.init_snake();
        Snake* snake = map.get_snake();
    
        Random::resetRandomEngine();
        map.setRandomItem(ItemType::FOOD, "#");

        game.startGame(map, snake);

        choice = game.renderRestartMenu(snake);
        if (choice == false) return false;
        snake -> revive();
        clear();
        refresh();
    }
}