#include "GameEngine.h"
#include <SFML/Window/Event.hpp>

void GameEngine::inpute()
{
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
}

void GameEngine::draw()
{
    roads.draw();

}

GameEngine::GameEngine(const std::string& Title, unsigned modeWidth, 
                       unsigned modeHeight)
{
    window.create(sf::VideoMode(modeWidth, modeHeight), Title, sf::Style::Close);
}

GameEngine::GameEngine()
{
    window.create(sf::VideoMode(640, 480), "Game_Sharaburko", sf::Style::Close);
}

const sf::RenderWindow& GameEngine::getWindow()
{
    return window;
}

void GameEngine::run()
{
    while (window.isOpen()) {

        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 900;

        inpute();
        update();
        draw();
    }
}

int GameEngine::searchActivPosition(std::vector<PositionPoints> const& positionPoints, sf::Vector2i const& mousePosition)
{
    for (int i = 0; i < positionPoints.size(); i++) {
        sf::IntRect areaChip(positionPoints[i].coordinateX, positionPoints[i].coordinateY, sizePoints.x, sizePoints.y);

        if (areaChip.contains(mousePosition.x, mousePosition.y)) {
            return positionPoints[i].position;
        }

    }

    return 0;
}

void GameEngine::searchFreePointsChip(std::vector <std::vector <int>>& road, std::vector <int> const& occupiredPoints) {
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

std::vector <int> const GameEngine::searchRoadActivChip(std::vector <std::vector <int>> const& road, int const& activPosition) {
    std::vector <int> tempRoadActivChip;
    for (size_t i = 0; i < road.size(); i++) {

        if (*(road[i].end() - 1) == activPosition) {
            tempRoadActivChip = road[i];
            return tempRoadActivChip;
        }

    }
    return tempRoadActivChip;
}

//void GameEngine:initialization(Config& config, std::vector <std::vector <int>>& connectPoints, std::vector <Chip>& chip, std::vector <Square>& square, std::vector <PositionPoints>& positionPoints, float const& radiusChip) {
//
//    for (int i = 0; i < config.getConnectCount(); i++) {
//        config.getConnectionsBetweenPoints(i);
//        std::vector <int> tempConnect;
//        tempConnect.push_back(config.getConnectionsBetweenPoints(i).getConnectionP1());
//        tempConnect.push_back(config.getConnectionsBetweenPoints(i).getConnectionP2());
//        connectPoints.push_back(tempConnect);
//        tempConnect.clear();
//    }
//
//    for (int i = 0; i < config.getChipCount(); i++) {
//        int numberPositionShape = config.getArrStartPoints(i);
//        chip.emplace_back(config.getArrStartPoints(i), config.getArrWinnerPoints(i), arrColor[i], config.getCoordinatePoints(numberPositionShape).getCoordinateX(), config.getCoordinatePoints(numberPositionShape).getCoordinateY(), radiusChip);
//    }
//
//    for (int i = 0; i < config.getChipCount(); i++) {
//        int NumberPositionPoint = config.getArrWinnerPoints(i);
//        square.emplace_back(NumberPositionPoint, config.getCoordinatePoints(NumberPositionPoint).getCoordinateX(), config.getCoordinatePoints(NumberPositionPoint).getCoordinateY(), arrColor[i], radiusChip);
//    }
//
//    for (int i = 1; i <= config.getPointsCount(); i++) {
//        PositionPoints tempPositionPoints(i, config.getCoordinatePoints(i).getCoordinateX(), config.getCoordinatePoints(i).getCoordinateY());
//        positionPoints.push_back(tempPositionPoints);
//    }
//
//}

void GameEngine:fillingBusyPoints(std::vector <PositionPoints>& positionPoints, std::vector <int>& occupPoints, std::vector <Chip> const& chip) {
    for (int i = 0; i < positionPoints.size(); i++) {
        positionPoints[i].freePoints = true;
        occupPoints.clear();
    }

    for (int i = 0; i < chip.size(); i++) {
        positionPoints[chip[i].numberPositionShape - 1].freePoints = false;
        occupPoints.push_back(chip[i].numberPositionShape);
    }
};