#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include "config.h"
#include "move.h"
#include "Color.h"

vector <sf::Color> arrColor{sf::Color::Black, sf::Color::White, sf::Color::Green, sf::Color::Blue, sf::Color::Magenta, userColor::Purple, userColor::Olive, userColor::Gray, userColor::Navy, userColor::Fuchsia, userColor::Teal};    //color points and chip

struct Chip {
    sf::CircleShape shape;
    int numberPositionShape;
    int numberWinPOsitionShape;
    bool avtivChip = false;
    Chip(int position, int winPosition, sf::Color color, float positionX, float positionY, sf::Texture *textureChip) {
        shape.setRadius(radiusChip);
        numberPositionShape = position;
        numberWinPOsitionShape = winPosition;
        shape.setFillColor(color);
        shape.setPosition(positionX , positionY );
        shape.setTexture(textureChip);
    }
};

struct Square {
    int numberPositionSquare;
    sf::RectangleShape point;
    Square(int position, float positionX, float positionY, sf::Color color, sf::Texture *textureSquare) {
        numberPositionSquare = position;
        point.setSize(sizePoints);
        point.setPosition(positionX - (sizePoints.x/2 - radiusChip), positionY - (sizePoints.y / 2 - radiusChip));
        point.setFillColor(color);
        point.setTexture(textureSquare);
    }
};

struct PositionPoints {
    int position;
    float coordinateX;
    float coordinateY;
    bool freePoints = true;
    PositionPoints(int position, float x, float y) {
        this->position = position;
        coordinateX = x;
        coordinateY = y;
    }
};

int main()
{ 
    sf::RenderWindow window(sf::VideoMode(640, 480), "Game_Sharaburko", sf::Style::Close);
    Config config;
    config.readConfig("config.txt");
    sf::Mouse mouse;
    sf::Clock clock;
    sf::Texture textureChip;
    sf::Texture textureSquare;
    textureChip.loadFromFile("img/chip.png");
    textureSquare.loadFromFile("img/point.png");
    sf::Texture textureBackground;
    textureBackground.loadFromFile("img/background.jpg");
    sf::Sprite background(textureBackground);
    sf::Music soundWin;
    sf::Sound soundMoveChip;
    sf::SoundBuffer bufferMove;
    bufferMove.loadFromFile("music/move.ogg");
    soundMoveChip.setBuffer(bufferMove);
    sf::Font font;
    font.loadFromFile("arial.ttf");
    sf::Text text("You WIN!!!", font);
    text.setCharacterSize(60);
    sf::Vector2i mousePosition (0, 0);
    int activPosition = 0;
    int activChip = 0;
    int stepActivChip = 0;
    int countWinPosition = 0;
    vector <Chip> chip;   
    vector <Square> square;
    vector <PositionPoints> positionPoints;
    chip.reserve(config.getChipCount());
    square.reserve(config.getChipCount());
    positionPoints.reserve(config.getPointsCount());
    std::vector<std::vector <int>> connectPoints;
    std::vector <int> occupPoints;
    std::vector <int> freePoints;
    std::vector <int> roadActivChip;
    std::vector <std::vector <int>> road;
    connectPoints.reserve(config.getConnectCount());
    
    for (int i = 0; i < config.getConnectCount(); i++)
    {
        std::vector <int> tempConnect;
        tempConnect.push_back(config.getConnectionsBetweenPoints(i).getConnectionP1());
        tempConnect.push_back(config.getConnectionsBetweenPoints(i).getConnectionP2());
        connectPoints.push_back(tempConnect);
        tempConnect.clear();
    }

    for (int i = 0; i < config.getChipCount(); i++) {
        int numberPositionShape = config.getArrStartPoints(i);
        Chip tempChip(config.getArrStartPoints(i), config.getArrWinnerPoints(i),arrColor[i], config.getCoordinatePoints(numberPositionShape).getCoordinateX(), config.getCoordinatePoints(numberPositionShape).getCoordinateY(), &textureChip);
        chip.push_back(tempChip);
    }

    for (int i = 0; i < config.getChipCount(); i++) {
        int NumberPositionPoint = config.getArrWinnerPoints(i);
        Square tempSquare(NumberPositionPoint, config.getCoordinatePoints(NumberPositionPoint).getCoordinateX(), config.getCoordinatePoints(NumberPositionPoint).getCoordinateY(), arrColor[i], &textureSquare);
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

        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 900;

        for (int i = 0; i < positionPoints.size(); i++) {
            positionPoints[i].freePoints = true;
            occupPoints.clear();
        }

        for (int i = 0; i < chip.size(); i++) {
            positionPoints[chip[i].numberPositionShape - 1].freePoints = false;
            occupPoints.push_back(chip[i].numberPositionShape);
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            mousePosition = mouse.getPosition(window);
 
            for (int i = 0; i < positionPoints.size(); i++) {
                sf::IntRect areaChip(positionPoints[i].coordinateX, positionPoints[i].coordinateY, sizePoints.x, sizePoints.y);

                if (areaChip.contains(mousePosition.x, mousePosition.y)) {
                    activPosition = positionPoints[i].position;

                    if (!positionPoints[i].freePoints) {
                        activChip = activPosition;
                    }

                    break;
                }
                             
            }

        }

        road = movesActivChip(activChip, connectPoints);

        for (size_t j = 0; j < road.size(); j++)
        {

            for (size_t k = 0; k < occupPoints.size(); k++)
            {

                if (find(road[j].begin() + 1, road[j].end(), occupPoints[k]) != road[j].end())
                {
                    road.erase(road.begin() + j);
                    j--;
                    break;
                }

            }
        }

        if (countWinPosition == chip.size()) {
            break;
        }

        window.clear(userColor::Gray);
        window.draw(background);
        countWinPosition = 0;

        for (int i = 0; i < config.getConnectCount(); i++)
        {
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
                sf::Vector2f position(p1X + (2 * radiusChip - widthConnection) / 2, p1Y + (2 * radiusChip - widthConnection) / 2);
                connectingPoints.setSize(size);
                connectingPoints.setPosition(position);
            }
            else
            {
                sf::Vector2f size(p2X + sizePoints.x - p1X - (sizePoints.x - widthConnection), widthConnection);
                connectingPoints.setSize(size);
                sf::Vector2f position(p1X + (2 * radiusChip - widthConnection) / 2, p1Y + (2 * radiusChip - widthConnection) / 2);
                connectingPoints.setPosition(position);
            }

            connectingPoints.setFillColor(sf::Color(216, 216, 216));
            window.draw(connectingPoints);
        }

        for (int i = 0; i < square.size(); i++)
        {
            window.draw(square[i].point);
        }

        for (size_t i = 0; i < road.size(); i++)
        {
            sf::CircleShape activ;
            int radiusFreePosition = radiusChip * 0.2;
            activ.setFillColor(sf::Color::Red);
            activ.setRadius(radiusFreePosition);
            activ.setPosition(positionPoints[*(road[i].end() - 1) - 1].coordinateX + (2 * radiusChip - 2 * radiusFreePosition) / 2 , positionPoints[*(road[i].end() - 1) - 1].coordinateY + (2 * radiusChip - 2 * radiusFreePosition) / 2);
            window.draw(activ);
        }

        for (int i = 0; i < chip.size(); i++) {

            if (chip[i].numberPositionShape == activChip) {

                for (size_t i = 0; i < road.size(); i++)
                {

                    if (*(road[i].end() - 1) == activPosition)
                    {
                        roadActivChip = road[i];
                        stepActivChip = 1;
                        break;
                    }

                }

                chip[i].shape.setRadius(radiusChip * 1.1);
                chip[i].shape.setOutlineThickness(-2);
                chip[i].shape.setOutlineColor(sf::Color::White);

                if (!roadActivChip.empty()) {

                    float distanceX = positionPoints[roadActivChip[stepActivChip] - 1].coordinateX - chip[i].shape.getPosition().x;
                    float distanceY = positionPoints[roadActivChip[stepActivChip] - 1].coordinateY - chip[i].shape.getPosition().y;
                    float distance = sqrt(distanceX * distanceX + distanceY * distanceY);

                    if (distance > 3) {
                        chip[i].shape.setPosition(chip[i].shape.getPosition().x + 0.01 * time * distanceX, chip[i].shape.getPosition().y + 0.01 * time * distanceY);
                    }
                    else {
                        chip[i].shape.setPosition(positionPoints[roadActivChip[stepActivChip] - 1].coordinateX, positionPoints[roadActivChip[stepActivChip] - 1].coordinateY);
                        soundMoveChip.play();

                        if (stepActivChip < roadActivChip.size()) {
                            activChip = roadActivChip[stepActivChip];
                            chip[i].numberPositionShape = roadActivChip[stepActivChip];
                            stepActivChip++;
                        }

                        if ((stepActivChip == roadActivChip.size())) {
                            chip[i].numberPositionShape = activPosition;
                            activChip = activPosition;
                            roadActivChip.clear();

                        }

                    }
                }

            }
            else {
                chip[i].shape.setRadius(radiusChip);
                chip[i].shape.setOutlineThickness(0);
            }

            if (chip[i].numberPositionShape == chip[i].numberWinPOsitionShape) {
                chip[i].shape.setOutlineThickness(-2);
                chip[i].shape.setOutlineColor(sf::Color::Yellow);
            }

            window.draw(chip[i].shape);
        }

        for (size_t i = 0; i < chip.size(); i++) {
            if (chip[i].numberPositionShape == chip[i].numberWinPOsitionShape)
            {
                countWinPosition++;
            }
        }
        
        window.display();
    }

    if (!soundWin.openFromFile("music/finish.ogg"))
    {
        return 0;
    }

    if (countWinPosition == chip.size()) {
        soundWin.play();
    }

    while (soundWin.getStatus() == 2)
    {
        text.setPosition(80, 200);
        window.clear(sf::Color::Black);
        window.draw(text);
        window.display();
    }

    return 0;
}