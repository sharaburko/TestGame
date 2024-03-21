#include <string>
#include "config.h"
#include "GameEngine.h"

int main() {
    GameEngine gameEngine("Game_Sharaburko", 640, 480);

    Config config;
    config.readConfig("config.txt");

    gameEngine.run(config);

    return 0;
}
