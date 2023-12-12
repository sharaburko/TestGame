#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include "config.h"

using namespace sf;
vector <sf::Color> arrColor{Color::Black, sf::Color::White, Color::Red, Color::Green, Color::Blue, Color::Magenta, Color::Cyan, Color::Transparent };    //color points and chip
Color yellow(sf::Color::Yellow);

int main()
{ 
    RenderWindow window(VideoMode(640, 480), "Game");
    Config config;
    config.readConfig("config.txt");
	
    //Clock clock;	
    sf::CircleShape chip(20,30);
    sf::RectangleShape square(Vector2f(30, 30));

	
    while (window.isOpen())
    {
        sf::Event event;
    	
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //float time = clock.getElapsedTime().asMicroseconds();
        //clock.restart();
        //time = time / 800;
    	
        window.clear();
    	for(int i = 0; i < config.getChipCount(); i++)
    	{
            int j = config.getArrWinnerPoints(i);
            chip.setPosition(config.getCoordinatePoints(j).getCoordinateX(), config.getCoordinatePoints(j).getCoordinateY());
            chip.setFillColor(arrColor[i]);
            window.draw(chip);
    	}

        for (int i = 0; i < config.getChipCount(); i++)
        {
            int j = config.getArrStartPoints(i);
            square.setPosition(config.getCoordinatePoints(j).getCoordinateX(), config.getCoordinatePoints(j).getCoordinateY());
            square.setFillColor(arrColor[i]);
            window.draw(square);
        }


        window.display();
    }

    return 0;
}