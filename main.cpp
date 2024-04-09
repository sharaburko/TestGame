#include <string>
#include "config.h"
#include "GameEngine.h"
#include "menu.h"

constexpr auto level = 2;

int main() {
    AssetManager::getBackgroundMusic().play();
    std::vector <Config> configs;
    configs.reserve(level);

    configs.emplace_back("config.txt");
    configs.emplace_back("config1.txt");

    GameEngine gameEngine;
    gameEngine.run(configs);

    //do {
    //    
    //    Menu menu("Game_Sharaburko");        

    //    switch (int result = menu.run()) {
    //    case 1: {
    //        GameEngine gameEngine(1);
    //        config.readConfig(Level_1);
    //        gameEngine.run(config);
    //        break;
    //    }
    //    case 2: {
    //        GameEngine gameEngine(2);
    //        config.readConfig(Level_2);
    //        gameEngine.run(config);
    //        break;
    //    }
    //    case 3:
    //        return 0;
    //    }

    //} while (true);
    // 
    //   

    return 0;
}
