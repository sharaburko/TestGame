#include "GameEngine.h"
#include <SFML/Window/Event.hpp>

//void GameEngine::inpute()
//{
//    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !moveChip) {
//        chip = checkChipPosition();
//
//        if (chip != nullptr) {
//            chip.move(position);
//        }
//    }
//}
//
//void GameEngine::draw()
//{
//    roads.draw();
//
//}
//
//GameEngine::GameEngine(const std::string& Title, unsigned modeWidth, 
//                       unsigned modeHeight)
//{
//    window.create(sf::VideoMode(modeWidth, modeHeight), Title, sf::Style::Close);
//}
//
//void GameEngine::run()
//{
//    while (window.isOpen()) {
//
//        float time = clock.getElapsedTime().asMicroseconds();
//        clock.restart();
//        time = time / 900;
//
//        inpute();
//        update();
//        draw();
//    }
//}