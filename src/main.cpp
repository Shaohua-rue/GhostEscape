#include "core/Game.h"
#include "core/Object.h"
#include "core/Scene.h"
int main() {
    Game& game = Game::getInstance();
    game.init("Game", 800, 600);
    game.run();
    return 0;
}