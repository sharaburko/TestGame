#include <string>
#include "config.h"
#include "GameEngine.h"
#include "menu.h"

constexpr auto CountOfLevels = 2;

int main() {
    AssetManager::getBackgroundMusic().play();
    std::vector <Config> configs;
    configs.reserve(CountOfLevels);

    configs.emplace_back("cfg/config.txt");
    configs.emplace_back("cfg/config1.txt");

    GameEngine gameEngine;
    gameEngine.run(configs);

    return 0;
}