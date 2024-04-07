#include <string>
#include "config.h"
#include "GameEngine.h"
#include "menu.h"

constexpr auto Level_1 = "config.txt";
constexpr auto Level_2 = "config.txt";

int main() {
    AssetManager::getBackgroundMusic().play();      

    do {
        
        Menu menu("Game_Sharaburko");        

        switch (menu.run()) {
        case 1: {
            GameEngine gameEngine(1);
            Config config;
            config.readConfig(Level_1);
            gameEngine.run(config);
            break;
        }
        case 2: {
            GameEngine gameEngine(2);
            Config config;
            config.readConfig(Level_2);
            gameEngine.run(config);
            break;
        }
        case 3:
            return 0;
        }

    } while (true);
       
}
