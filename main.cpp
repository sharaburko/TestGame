#include <string>
#include "config.h"
#include "GameEngine.h"


std::vector <sf::Color> arrColor{sf::Color::Black, sf::Color::White, sf::Color::Green, 
sf::Color::Blue, sf::Color::Magenta, userColor::Purple, userColor::Olive, userColor::Gray, 
userColor::Navy, userColor::Fuchsia, userColor::Teal};    //color points and chip


int main() {
    GameEngine gameEngine("Game_Sharaburko", 640, 480);

    Config config;
    config.readConfig("config.txt");

    gameEngine.setInit(config);

    gameEngine.run();   

    return 0;
}
