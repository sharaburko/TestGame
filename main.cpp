#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include "config.h"

using namespace sf;


int main()
{ 
    RenderWindow window(VideoMode(640, 480), "Game");
    Config config;
    config.readConfig("config.txt");

    Clock clock;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 800;
       

        window.clear();
        //window.draw();
        window.display();
    }

    return 0;
}