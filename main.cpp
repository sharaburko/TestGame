#include <string>
#include "config.h"
#include "GameEngine.h"
#include "menu.h"

int main() {
    //GameEngine gameEngine("Game_Sharaburko", 640, 480);
    Menu menu("MENU_Game_Sharaburko", 640, 480);

    //Config config;
    //config.readConfig("config.txt");

    menu.run();
    //gameEngine.run(config);

    return 0;
}
