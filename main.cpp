#include <string>
#include "config.h"
#include "GameEngine.h"
#include "menu.h"

int main() {
    AssetManager::getBackgroundMusic().play();      

    do {
        
        Menu menu("Game_Sharaburko");        

        switch (menu.run()) {
        case 1: {
            GameEngine gameEngine("Level 1");
            Config config;
            config.readConfig("config.txt");
            gameEngine.run(config);
            break;
        }
        case 2: {
            GameEngine gameEngine("Level 2");
            Config config;
            config.readConfig("config1.txt");
            gameEngine.run(config);
            break;
        }
        case 3:
            return 0;
        }

    } while (true);
       
}
