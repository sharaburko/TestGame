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
    float radiusChip = 15;
    sf::Vector2f sizePoints(40, 40);
    Mouse mouse;
    Vector2i mousePosition (0, 0);
	

	
    //Clock clock;	
    sf::CircleShape chip(radiusChip,30);
    sf::RectangleShape square(sizePoints);

	
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

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            mousePosition = mouse.getPosition(window);
            std::cout << "mouse click: " << mousePosition.x << " " << mousePosition.y << "\n";
        }

        window.clear(sf::Color(214,203,174));
    	

        for (int i = 0; i < config.getConnectCount(); i++) {
            int p1 = config.getConnectionsBetweenPoints(i).getConnectionP1();
            int p2 = config.getConnectionsBetweenPoints(i).getConnectionP2();
            float p1X = config.getCoordinatePoints(p1).getCoordinateX();
            float p1Y = config.getCoordinatePoints(p1).getCoordinateY();
            float p2X = config.getCoordinatePoints(p2).getCoordinateX();
            float p2Y = config.getCoordinatePoints(p2).getCoordinateY();
            float widthConnection = 20;
            sf::RectangleShape connectingPoints;

        	
            if (p1X == p2X)
            {
                sf::Vector2f size(widthConnection, p2Y + sizePoints.y - p1Y - (sizePoints.y - widthConnection));
                sf::Vector2f position(p1X + ((sizePoints.x - widthConnection)/2), p1Y + ((sizePoints.y - widthConnection) / 2));
                connectingPoints.setSize(size);
                connectingPoints.setPosition(position);
            }
            else
            {
                sf::Vector2f size(p2X + sizePoints.x - p1X - (sizePoints.x - widthConnection), widthConnection);
                connectingPoints.setSize(size);
                sf::Vector2f position(p1X + ((sizePoints.x - widthConnection) / 2), p1Y + ((sizePoints.y - widthConnection) / 2));
                connectingPoints.setPosition(position);
            }        	
      	
            connectingPoints.setFillColor(sf::Color(216, 216, 216));
            window.draw(connectingPoints);
        }

        for (int i = 0; i < config.getChipCount(); i++)
        {
            int j = config.getArrWinnerPoints(i);
            float positionX = config.getCoordinatePoints(j).getCoordinateX();
            float positionY = config.getCoordinatePoints(j).getCoordinateY();
            square.setPosition(positionX, positionY);
            square.setFillColor(arrColor[i]);
            window.draw(square);
        }
    	
        for (int i = 0; i < config.getChipCount(); i++)
        {
            int j = config.getArrStartPoints(i);
            float positionX = config.getCoordinatePoints(j).getCoordinateX();
            float positionY = config.getCoordinatePoints(j).getCoordinateY();
            IntRect chipObject(positionX, positionY, radiusChip*2, radiusChip*2);
      	    chip.setPosition(positionX + (sizePoints.x - 2 * radiusChip)/2, positionY + (sizePoints.y - 2 * radiusChip) / 2);
            chip.setFillColor(arrColor[i]);
        	
            if (chipObject.contains(positionX, positionY)) {
                chip.scale(1.5, 1.5);
                window.draw(chip);
        	

        }
        
        window.display();
    }

    return 0;
}