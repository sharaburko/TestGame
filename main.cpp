#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include "config.h"

using namespace sf;
vector <sf::Color> arrColor{Color::Black, sf::Color::White, Color::Red, Color::Green, Color::Blue, Color::Magenta, Color::Cyan, Color::Transparent };    //color points and chip
//Color yellow(sf::Color::Yellow);

struct Chip {
    CircleShape shape;
    int numberPositionShape;
    int numberWinPOsitionShape;
    bool avtivChip = false;
    Chip(int position, int winPosition, sf::Color color, float positionX, float positionY) {
        shape.setRadius(radiusChip);
        numberPositionShape = position;
        numberWinPOsitionShape = winPosition;
        shape.setFillColor(color);
        shape.setPosition(positionX + (sizePoints.x - 2 * radiusChip) / 2, positionY + (sizePoints.y - 2 * radiusChip) / 2);
    }
};

struct Square {
    int numberPositionSquare;
    RectangleShape point;
    Square(int position, float positionX, float positionY, sf::Color color) {
        numberPositionSquare = position;
        point.setSize(sizePoints);
        point.setPosition(positionX, positionY);
        point.setFillColor(color);
    }
};

struct PositionPoints {
    int position;
    float coordinateX;
    float coordinateY;
    bool freePoints = true;
    IntRect areaPoints;
    PositionPoints(int position, float x, float y) {
        this->position = position;
        coordinateX = x;
        coordinateY = y;
    }
};


int main()
{ 
    RenderWindow window(VideoMode(640, 480), "Game");
    Config config;
    config.readConfig("config.txt");
    Mouse mouse;
    Vector2i mousePosition (0, 0);
    int activPosition = 0;
    int activChip = 0;

    vector <Chip> chip;   
    vector <Square> square;
    vector <PositionPoints> positionPoints;

    chip.reserve(config.getChipCount());
    square.reserve(config.getChipCount());
    positionPoints.reserve(config.getPointsCount());


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

    for (int i = 1; i <= config.getPointsCount(); i++) {
        PositionPoints tempPositionPoints(i, config.getCoordinatePoints(i).getCoordinateX(), config.getCoordinatePoints(i).getCoordinateY());
        positionPoints.push_back(tempPositionPoints);
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
        for (int i = 0; i < positionPoints.size(); i++) {
            positionPoints[i].freePoints = true;
        }

        for (int i = 0; i < chip.size(); i++) {
            positionPoints[chip[i].numberPositionShape - 1].freePoints = false;
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            mousePosition = mouse.getPosition(window);


            for (int i = 0; i < positionPoints.size(); i++) {
                IntRect areaChip(positionPoints[i].coordinateX, positionPoints[i].coordinateY, sizePoints.x, sizePoints.y);

                if (areaChip.contains(mousePosition.x, mousePosition.y)) {
                    activPosition = positionPoints[i].position;
                    break;
                }
            }

            if (positionPoints[activPosition - 1].freePoints) {

                for (int i = 0; i < chip.size(); i++) {

                    if (chip[i].avtivChip) {
                        float distance;
                        float distanceX = chip[i].shape.getPosition().x - positionPoints[activPosition - 1].coordinateX;
                        float distanceY = chip[i].shape.getPosition().y - positionPoints[activPosition - 1].coordinateY;
                        distance = sqrt(distanceX * distanceX + distanceY * distanceY);

                        if (distance > 2) {
                            chip[i].shape.setPosition(chip[i].shape.getPosition().x + 0.001* distanceX, chip[i].shape.getPosition().y + 0.001 * distanceY);
                            std::cout << "I am NOT position\n";
                        }
                        else {
                            chip[i].shape.setPosition(positionPoints[activPosition - 1].coordinateX, positionPoints[activPosition - 1].coordinateY);
                            chip[i].numberPositionShape = activPosition;
                            std::cout << "I am position\n";
                        }
                        
                    }

                }

            }
            else {

                for (int i = 0; i < chip.size(); i++) {
                    chip[i].avtivChip = false;
                }

                for (int i = 0; i < chip.size(); i++) {

                    if (activPosition == chip[i].numberPositionShape) {
                        chip[i].avtivChip = true;
                        break;
                    }

                }

            }
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

        for (int i = 0; i < square.size(); i++)
        {
            window.draw(square[i].point);
        }
    	
        for (int i = 0; i < chip.size(); i++) {          

        	if (chip[i].avtivChip) {
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