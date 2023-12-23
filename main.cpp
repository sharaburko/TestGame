#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include "config.h"

using namespace sf;
vector <sf::Color> arrColor{Color::Black, sf::Color::White, Color::Red, Color::Green, Color::Blue, Color::Magenta, Color::Cyan, Color::Transparent };    //color points and chip
//Color yellow(sf::Color::Yellow);



int main()
{ 
    RenderWindow window(VideoMode(640, 480), "Game");
    Config config;
    config.readConfig("config.txt");
    Mouse mouse;
    Vector2i mousePosition (0, 0);    	

    int activChip = 0;

    struct Chip {
        CircleShape shape;
        int numberPositionShape;
        int numberWinPOsitionShape;
        Chip(int position, int winPosition, sf::Color color, float positionX, float positionY) {
            shape.setRadius(radiusChip);
            numberPositionShape = position;
            numberWinPOsitionShape = winPosition;
            shape.setFillColor(color);            
            shape.setPosition(positionX + (sizePoints.x - 2 * radiusChip) / 2, positionY + (sizePoints.y - 2 * radiusChip) / 2);
        }
    };

    struct Square{
        int numberPositionSquare;
        RectangleShape point;
        Square(int position, float positionX, float positionY, sf::Color color) {
            numberPositionSquare = position;
            point.setSize(sizePoints);
            point.setPosition(positionX, positionY);
            point.setFillColor(color);
        }    
    };

    vector <Chip> chip;   
    vector <Square> square;

    for (int i = 0; i < config.getChipCount(); i++) {
        int numberPositionShape = config.getArrStartPoints(i);
        Chip tempChip(config.getArrStartPoints(i), config.getArrWinnerPoints(i),arrColor[i], config.getCoordinatePoints(numberPositionShape).getCoordinateX(), config.getCoordinatePoints(numberPositionShape).getCoordinateY());
        chip.push_back(tempChip);
    }

    for (int i = 0; i < config.getChipCount(); i++) {
        int NumberPositionPoint = config.getArrWinnerPoints(i);
        Square tempSquare(NumberPositionPoint, config.getCoordinatePoints(NumberPositionPoint).getCoordinateX(), config.getCoordinatePoints(NumberPositionPoint).getCoordinateY(), arrColor[i]);
        square.push_back(tempSquare);
    }
	
	
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
            window.draw(square[i].point);
        }
    	
        for (int i = 0; i < chip.size(); i++)
        {

           IntRect areaChip(chip[i].shape.getPosition().x, chip[i].shape.getPosition().y, chip[i].shape.getRadius() * 2, chip[i].shape.getRadius() * 2);

        	if (areaChip.contains(mousePosition.x, mousePosition.y)) {
                chip[i].shape.setRadius(radiusChip * 1.1);
                chip[i].shape.setOutlineThickness(2);
                chip[i].shape.setOutlineColor(sf::Color::White);
            }
            else {
                chip[i].shape.setRadius(radiusChip);
                chip[i].shape.setOutlineThickness(0);
            }
        	
            window.draw(chip[i].shape);                       
        }
        
        window.display();
    }

    return 0;
}