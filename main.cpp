#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include "config.h"
#include "move.h"
#include "Color.h"


std::vector <sf::Color> arrColor{sf::Color::Black, sf::Color::White, sf::Color::Green, sf::Color::Blue, sf::Color::Magenta, userColor::Purple, userColor::Olive, userColor::Gray, userColor::Navy, userColor::Fuchsia, userColor::Teal};    //color points and chip
float radiusChip = 15;
sf::Vector2f sizePoints(40, 40);

struct AssetManager {
    sf::Texture textureChip;
    sf::Texture textureSquare;
    sf::Music soundWin;
    sf::Sound soundMoveChip;
    sf::Sprite background;
    sf::Text text;
    sf::Texture textureBackground;
    sf::Font font;
    sf::SoundBuffer bufferMove;

    static AssetManager& instance() {
        static AssetManager staticAssetManager;
        return staticAssetManager;
    }
private:
    AssetManager() {
        font.loadFromFile("arial.ttf");
        textureChip.loadFromFile("img/chip.png");
        textureSquare.loadFromFile("img/point.png");
        textureBackground.loadFromFile("img/background.jpg");
        background.setTexture(textureBackground);
        bufferMove.loadFromFile("music/move.ogg");
        soundMoveChip.setBuffer(bufferMove);
        soundWin.openFromFile("music/finish.ogg");
        text.setFont(font);
        text.setPosition(80, 200);
        text.setCharacterSize(60);
    }
    AssetManager(AssetManager const&);
    AssetManager& operator=(AssetManager const&);

};

struct Chip {
    sf::CircleShape shape;    
    int numberPositionShape;
    int numberWinPOsitionShape;
    bool avtivChip = false;
    Chip(int position, int winPosition, sf::Color color, float positionX, float positionY, AssetManager const &assetManager) {
        shape.setRadius(radiusChip);
        numberPositionShape = position;
        numberWinPOsitionShape = winPosition;
        shape.setFillColor(color);
        shape.setPosition(positionX , positionY );
        shape.setTexture(&assetManager.textureChip);
    }
};

struct Square {
    int numberPositionSquare;
    sf::RectangleShape point;
    sf::Texture textureSquare;
    Square(int position, float positionX, float positionY, sf::Color color, AssetManager const &assetManager) {
        numberPositionSquare = position;
        point.setSize(sizePoints);
        point.setPosition(positionX - (sizePoints.x/2 - radiusChip), positionY - (sizePoints.y / 2 - radiusChip));
        point.setFillColor(color);
        point.setTexture(&assetManager.textureSquare);
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

void initialization(Config& config, std::vector <std::vector <int>>& connectPoints, std::vector <Chip>& chip, std::vector <Square>& square, std::vector <PositionPoints>& positionPoints, AssetManager& assetManager);
int searchActivPosition(std::vector<PositionPoints> const &positionPoints, sf::Vector2i const &mousePosition);
void searchFreePointsChip(std::vector <std::vector <int>> &road, std::vector <int> const &occupiredPoints);
std::vector <int> const searchRoadActivChip(std::vector <std::vector <int>> const &road, int const& activPosition);

int main() { 
    sf::RenderWindow window(sf::VideoMode(640, 480), "Game_Sharaburko", sf::Style::Close);
    Config config;
    config.readConfig("config.txt");
    sf::Mouse mouse;
    sf::Clock clock;
    AssetManager& assetManager = AssetManager::instance();
    sf::Vector2i mousePosition (0, 0);
    int activPosition = 0;
    int activChip = 0;
    int stepActivChip = 1;
    int countWinPosition = 0;
    bool moveChip = false;
    std::vector <Chip> chip;   
    std::vector <Square> square;
    std::vector <PositionPoints> positionPoints;
    chip.reserve(config.getChipCount());
    square.reserve(config.getChipCount());
    positionPoints.reserve(config.getPointsCount());
    std::vector<std::vector <int>> connectPoints;
    std::vector <int> occupPoints;
    std::vector <int> freePoints;
    std::vector <int> roadActivChip;
    std::vector <std::vector <int>> road;
    connectPoints.reserve(config.getConnectCount());    
    initialization(config, connectPoints, chip, square, positionPoints, assetManager);
    void fillingBusyPoints(std::vector <PositionPoints> &positionPoints, std::vector <int> &occupPoints, std::vector <Chip> const& chip);

    while (window.isOpen()) {
        sf::Event event;
    	
        while (window.pollEvent(event)) {

            if (event.type == sf::Event::Closed)
                window.close();
        }

        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 900;

        fillingBusyPoints(positionPoints, occupPoints, chip);

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !moveChip) {

            mousePosition = mouse.getPosition(window);
            
            if (searchActivPosition(positionPoints, mousePosition)) {
                activPosition = searchActivPosition(positionPoints, mousePosition);

                if (!positionPoints[activPosition - 1].freePoints) {
                    activChip = activPosition;
                }

            }

        }

        road = movesActivChip(activChip, connectPoints);
        searchFreePointsChip(road, occupPoints);

        if (countWinPosition == chip.size()) 
            break;        

        window.clear(userColor::Gray);
        window.draw(assetManager.background);
        countWinPosition = 0;

        for (int i = 0; i < config.getConnectCount(); i++) {
            int p1 = config.getConnectionsBetweenPoints(i).getConnectionP1();
            int p2 = config.getConnectionsBetweenPoints(i).getConnectionP2();
            float p1X = config.getCoordinatePoints(p1).getCoordinateX();
            float p1Y = config.getCoordinatePoints(p1).getCoordinateY();
            float p2X = config.getCoordinatePoints(p2).getCoordinateX();
            float p2Y = config.getCoordinatePoints(p2).getCoordinateY();
            float widthConnection = 20;
            sf::RectangleShape connectingPoints;

            if (p1X == p2X) {
                sf::Vector2f size(widthConnection, p2Y + sizePoints.y - p1Y - (sizePoints.y - widthConnection));
                sf::Vector2f position(p1X + (2 * radiusChip - widthConnection) / 2, p1Y + (2 * radiusChip - widthConnection) / 2);
                connectingPoints.setSize(size);
                connectingPoints.setPosition(position);
            }
            else {
                sf::Vector2f size(p2X + sizePoints.x - p1X - (sizePoints.x - widthConnection), widthConnection);
                connectingPoints.setSize(size);
                sf::Vector2f position(p1X + (2 * radiusChip - widthConnection) / 2, p1Y + (2 * radiusChip - widthConnection) / 2);
                connectingPoints.setPosition(position);
            }

            connectingPoints.setFillColor(sf::Color(216, 216, 216));
            window.draw(connectingPoints);
        }

        for (int i = 0; i < square.size(); i++) {
            window.draw(square[i].point);
        }

        for (size_t i = 0; i < road.size(); i++) {
            sf::CircleShape activ;
            int radiusFreePosition = radiusChip * 0.2;
            activ.setFillColor(sf::Color::Red);
            activ.setRadius(radiusFreePosition);
            activ.setPosition(positionPoints[*(road[i].end() - 1) - 1].coordinateX + (2 * radiusChip - 2 * radiusFreePosition) / 2 , positionPoints[*(road[i].end() - 1) - 1].coordinateY + (2 * radiusChip - 2 * radiusFreePosition) / 2);
            window.draw(activ);
        }

        for (size_t i = 0; i < chip.size(); i++) {

            if (chip[i].numberPositionShape == activChip) {
                chip[i].shape.setRadius(radiusChip * 1.1);
                chip[i].shape.setOutlineThickness(-2);
                chip[i].shape.setOutlineColor(sf::Color::White);
                roadActivChip = searchRoadActivChip(road, activPosition);

                if (!roadActivChip.empty()) {
                    moveChip = true;
                    float distanceX = positionPoints[roadActivChip[stepActivChip] - 1].coordinateX - chip[i].shape.getPosition().x;
                    float distanceY = positionPoints[roadActivChip[stepActivChip] - 1].coordinateY - chip[i].shape.getPosition().y;
                    float distance = sqrt(distanceX * distanceX + distanceY * distanceY);
                    if (distance > 3) {                        
                        chip[i].shape.setPosition(chip[i].shape.getPosition().x + 0.01 * time * distanceX, chip[i].shape.getPosition().y + 0.01 * time * distanceY);
                    }
                    else {
                        chip[i].shape.setPosition(positionPoints[roadActivChip[stepActivChip] - 1].coordinateX, positionPoints[roadActivChip[stepActivChip] - 1].coordinateY);
                        assetManager.soundMoveChip.play();
                        stepActivChip++;

                        if ((stepActivChip == roadActivChip.size())) {
                            chip[i].numberPositionShape = activPosition;
                            stepActivChip = 1;
                            activChip = activPosition;
                            roadActivChip.clear();
                            moveChip = false;
                        }

                    }
                }

            }
            else if (chip[i].numberPositionShape == chip[i].numberWinPOsitionShape) {
                chip[i].shape.setOutlineThickness(-2);
                chip[i].shape.setOutlineColor(sf::Color::Yellow);
            }
            else {
                chip[i].shape.setRadius(radiusChip);
                chip[i].shape.setOutlineThickness(0);
            }

            if (chip[i].numberPositionShape == chip[i].numberWinPOsitionShape) {
                countWinPosition++;
            }

            window.draw(chip[i].shape);
        }
        
        window.display();
    }

    if (countWinPosition == chip.size()) {
        assetManager.soundWin.play();
    }

    while (assetManager.soundWin.getStatus() == 2) {        
        window.clear(sf::Color::Black);
        window.draw(assetManager.text);
        window.display();
    }

    return 0;
}

int searchActivPosition(std::vector<PositionPoints> const &positionPoints, sf::Vector2i const &mousePosition)
{
    for (int i = 0; i < positionPoints.size(); i++) {
        sf::IntRect areaChip(positionPoints[i].coordinateX, positionPoints[i].coordinateY, sizePoints.x, sizePoints.y);

        if (areaChip.contains(mousePosition.x, mousePosition.y)) {
            return positionPoints[i].position;
        }

    }

    return 0;
}

void searchFreePointsChip(std::vector <std:: vector <int>>& road, std::vector <int> const &occupiredPoints) {
    for (size_t j = 0; j < road.size(); j++) {

        for (size_t k = 0; k < occupiredPoints.size(); k++) {

            if (find(road[j].begin() + 1, road[j].end(), occupiredPoints[k]) != road[j].end()) {
                road.erase(road.begin() + j);
                j--;
                break;
            }

        }
    }
}

std::vector <int> const searchRoadActivChip(std::vector <std::vector <int>> const &road, int const& activPosition) {
    std::vector <int> tempRoadActivChip;
    for (size_t i = 0; i < road.size(); i++) {

        if (*(road[i].end() - 1) == activPosition) {
            tempRoadActivChip = road[i];
            return tempRoadActivChip;
        }

    }
    return tempRoadActivChip;
}

void initialization(Config &config, std::vector <std::vector <int>>& connectPoints, std::vector <Chip> &chip, std::vector <Square>& square, std::vector <PositionPoints>& positionPoints, AssetManager &assetManager){

    for (int i = 0; i < config.getConnectCount(); i++) {
        config.getConnectionsBetweenPoints(i);
        std::vector <int> tempConnect;
        tempConnect.push_back(config.getConnectionsBetweenPoints(i).getConnectionP1());
        tempConnect.push_back(config.getConnectionsBetweenPoints(i).getConnectionP2());
        connectPoints.push_back(tempConnect);
        tempConnect.clear();
    }

    for (int i = 0; i < config.getChipCount(); i++) {
        int numberPositionShape = config.getArrStartPoints(i);
        Chip tempChip(config.getArrStartPoints(i), config.getArrWinnerPoints(i), arrColor[i], config.getCoordinatePoints(numberPositionShape).getCoordinateX(), config.getCoordinatePoints(numberPositionShape).getCoordinateY(), assetManager);
        chip.push_back(tempChip);
    }

    for (int i = 0; i < config.getChipCount(); i++) {
        int NumberPositionPoint = config.getArrWinnerPoints(i);
        Square tempSquare(NumberPositionPoint, config.getCoordinatePoints(NumberPositionPoint).getCoordinateX(), config.getCoordinatePoints(NumberPositionPoint).getCoordinateY(), arrColor[i], assetManager);
        square.push_back(tempSquare);
    }

    for (int i = 1; i <= config.getPointsCount(); i++) {
        PositionPoints tempPositionPoints(i, config.getCoordinatePoints(i).getCoordinateX(), config.getCoordinatePoints(i).getCoordinateY());
        positionPoints.push_back(tempPositionPoints);
    }

}

void fillingBusyPoints(std::vector <PositionPoints>& positionPoints, std::vector <int>& occupPoints, std::vector <Chip> const& chip) {
    for (int i = 0; i < positionPoints.size(); i++) {
        positionPoints[i].freePoints = true;
        occupPoints.clear();
    }

    for (int i = 0; i < chip.size(); i++) {
        positionPoints[chip[i].numberPositionShape - 1].freePoints = false;
        occupPoints.push_back(chip[i].numberPositionShape);
    }
};