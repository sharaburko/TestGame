#include "GameEngine.h"
#include <SFML/Window/Event.hpp>

void GameEngine::setInit(Config& config) {
    init.setChip(config);
    init.setSquare(config);
    init.setPositionPoints(config);
    init.setConnectPoints(config);
}

GameEngine::GameEngine(const std::string& Title, unsigned modeWidth,
                       unsigned modeHeight)
{
    window.create(sf::VideoMode(modeWidth, modeHeight), Title, sf::Style::Close);
}

GameEngine::GameEngine() {
    window.create(sf::VideoMode(640, 480), "Sharaburko_Game", sf::Style::Close);
}

void GameEngine::inpute()
{
    //if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !moveChip) {
    //    chip = checkChipPosition();

    //    if (chip != nullptr) {
    //        chip.move(position);
    //    }
    //}
    

    while (window.pollEvent(event)) {

        if (event.type == sf::Event::Closed)
            window.close();
    }

    fillingBusyPoints(init.getPositionPoints(), occupPoints, init.getChip());

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !moveChip) {

        mousePosition = mouse.getPosition(window);

        if (searchActivPosition(init.getPositionPoints(), mousePosition)) {
            activPosition = searchActivPosition(init.getPositionPoints(), mousePosition);

            if (!init.getPositionPoints()[activPosition - 1].getFreePoints()) {
                activChip = activPosition;
            }

        }

    }

    road = movesActivChip(activChip, init.getConnectPoints());
    searchFreePointsChip(road, occupPoints);

    //if (countWinPosition == init.getChip().size())
    //    break;

    window.clear(userColor::Gray);
    window.draw(AssetManager::getBackground());
    countWinPosition = 0;

    for (int i = 0; i < init.getConnectPoints().size(); i++) {

        int p1 = init.getConnectPoints()[i][0] - 1;
        int p2 = init.getConnectPoints()[i][1] - 1;
        float p1X = init.getPositionPoints()[p1].getCoordinateX();
        float p1Y = init.getPositionPoints()[p1].getCoordinateY();
        float p2X = init.getPositionPoints()[p2].getCoordinateX();
        float p2Y = init.getPositionPoints()[p2].getCoordinateY();

        float widthConnection = 20;
        sf::RectangleShape connectingPoints;

        if (p1X == p2X) {
            sf::Vector2f size(widthConnection, p2Y + init.getSizePointsY() - p1Y -
                             (init.getSizePointsY() - widthConnection));
            sf::Vector2f position(p1X + (2 * init.getRadiusChip() - widthConnection) / 2,
                                  p1Y + (2 * init.getRadiusChip() - widthConnection) / 2);
            connectingPoints.setSize(size);
            connectingPoints.setPosition(position);
        }
        else {
            sf::Vector2f size(p2X + init.getSizePointsX() - p1X - (init.getSizePointsX() -
                              widthConnection), widthConnection);
            connectingPoints.setSize(size);
            sf::Vector2f position(p1X + (2 * init.getRadiusChip() - widthConnection) / 2,
                                  p1Y + (2 * init.getRadiusChip() - widthConnection) / 2);
            connectingPoints.setPosition(position);
        }

        connectingPoints.setFillColor(sf::Color(216, 216, 216));
        window.draw(connectingPoints);
    }

    for (int i = 0; i < init.getSquare().size(); i++) {
        window.draw(init.getSquare()[i].getPoint());
    }

    for (size_t i = 0; i < road.size(); i++) {
        sf::CircleShape activ;
        int radiusFreePosition = init.getRadiusChip() * 0.2;
        activ.setFillColor(sf::Color::Red);
        activ.setRadius(radiusFreePosition);
        activ.setPosition(init.getPositionPoints()[*(road[i].end() - 1) - 1].getCoordinateX() + (2 * init.getRadiusChip() - 2 * radiusFreePosition) / 2, init.getPositionPoints()[*(road[i].end() - 1) - 1].getCoordinateY() + (2 * init.getRadiusChip() - 2 * radiusFreePosition) / 2);
        window.draw(activ);
    }

    for (size_t i = 0; i < init.getChip().size(); i++) {

        if (init.getChip()[i].numberPositionShape == activChip) {
            init.setVectorChip()[i].shape.setRadius(init.getRadiusChip() * 1.1);
            init.setVectorChip()[i].shape.setOutlineThickness(-2);
            init.setVectorChip()[i].shape.setOutlineColor(sf::Color::White);
            roadActivChip = searchRoadActivChip(road, activPosition);

            if (!roadActivChip.empty()) {
                moveChip = true;
                float distanceX = init.getPositionPoints()[roadActivChip[stepActivChip] - 1].getCoordinateX() - init.getChip()[i].shape.getPosition().x;
                float distanceY = init.getPositionPoints()[roadActivChip[stepActivChip] - 1].getCoordinateY() - init.getChip()[i].shape.getPosition().y;
                float distance = sqrt(distanceX * distanceX + distanceY * distanceY);
                if (distance > 3) {
                    init.setVectorChip()[i].shape.setPosition(init.getChip()[i].shape.getPosition().x + 0.01 * time * distanceX, init.getChip()[i].shape.getPosition().y + 0.01 * time * distanceY);
                }
                else {
                    init.setVectorChip()[i].shape.setPosition(init.getPositionPoints()[roadActivChip[stepActivChip] - 1].getCoordinateX(), init.getPositionPoints()[roadActivChip[stepActivChip] - 1].getCoordinateY());
                    AssetManager::getSoundMoveChip().play();
                    stepActivChip++;

                    if ((stepActivChip == roadActivChip.size())) {
                        init.setVectorChip()[i].numberPositionShape = activPosition;
                        stepActivChip = 1;
                        activChip = activPosition;
                        roadActivChip.clear();
                        moveChip = false;
                    }

                }
            }

        }
        else if (init.getChip()[i].numberPositionShape == init.getChip()[i].numberWinPOsitionShape) {
            init.setVectorChip()[i].shape.setOutlineThickness(-2);
            init.setVectorChip()[i].shape.setOutlineColor(sf::Color::Yellow);
        }
        else {
            init.setVectorChip()[i].shape.setRadius(init.getRadiusChip());
            init.setVectorChip()[i].shape.setOutlineThickness(0);
        }

        if (init.getChip()[i].numberPositionShape == init.getChip()[i].numberWinPOsitionShape) {
            countWinPosition++;
        }

        window.draw(init.getChip()[i].shape);
    }

    window.display();

    if (countWinPosition == init.getChip().size()) {
        AssetManager::getSoundWin().play();
    }

    while (AssetManager::getSoundWin().getStatus() == 2) {
        window.clear(sf::Color::Black);
        window.draw(AssetManager::getText());
        window.display();
    }
}

void GameEngine::update()
{
}

void GameEngine::draw()
{
    //roads.draw();

}


void GameEngine::run()
{
    while (window.isOpen()) {

        time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time = time / 900;

        inpute();
        update();
        draw();
    }
}


int GameEngine::searchActivPosition(std::vector<PositionPoints> & positionPoints, sf::Vector2i const& mousePosition)
{
    for (int i = 0; i < positionPoints.size(); i++) {
        sf::IntRect areaChip(positionPoints[i].getCoordinateX(), positionPoints[i].getCoordinateY(), init.getSizePointsX(), init.getSizePointsY());

        if (areaChip.contains(mousePosition.x, mousePosition.y)) {
            return positionPoints[i].getPosition();
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

void GameEngine::fillingBusyPoints(std::vector <PositionPoints>& positionPoints, std::vector <int>& occupPoints, std::vector <Chip> const& chip) {
    for (int i = 0; i < positionPoints.size(); i++) {
        positionPoints[i].setFreePoints() = true;
        occupPoints.clear();
    }

    for (int i = 0; i < chip.size(); i++) {
        positionPoints[chip[i].numberPositionShape - 1].setFreePoints() = false;
        occupPoints.push_back(chip[i].numberPositionShape);
    }
};