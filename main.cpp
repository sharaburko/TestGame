#include <string>
#include "config.h"
#include "GameEngine.h"
#include "menu.h"

int main() {
    GameEngine gameEngine("Game_Sharaburko", 640, 480);
    Menu menu("MENU_Game_Sharaburko", 640, 480);

    AssetManager::getBackgroundMusic().play();

    Config config;    

    switch (menu.run()) {
    case 1: 
        config.readConfig("config.txt");
        gameEngine.run(config);
        break;
    case 2: 
        config.readConfig("config1.txt");
        gameEngine.run(config);
        break;
    case 3:
        break;
    }

    return 0;
}
