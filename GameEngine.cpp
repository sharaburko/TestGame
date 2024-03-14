#include "GameEngine.h"
#include <SFML/Window/Event.hpp>

void GameEngine::setInit(Config& config) {
    init.setChip(config);
    init.setSquare(config);
    init.setPositionPoints(config);
    init.setConnectPoints(config);
    init.setRoads();
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
    
    time = clock.getElapsedTime().asMicroseconds();
    clock.restart();
    time = time / 900;

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

    countWinPosition = 0;

    if (!movingPlaces.empty()) {
        movingPlaces.clear();
    }

    for (auto i = road.begin(); i != road.end(); i++) {

        movingPlaces.emplace_back();
    }


}

void GameEngine::update()
{

    for (size_t i = 0; i < movingPlaces.size(); i++) {

        movingPlaces[i].setPositionMovingPlace(init.getPositionPoints()[*(road[i].end() - 1) - 1].getCoordinateX() +
                                              (2 * init.getRadiusChip() - 2 * movingPlaces[i].getRadiusMovingPlace()) / 2,
                                               init.getPositionPoints()[*(road[i].end() - 1) - 1].getCoordinateY() +
                                             (2 * init.getRadiusChip() - 2 * movingPlaces[i].getRadiusMovingPlace()) / 2);
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
    }
}

void GameEngine::draw() {

    if (countWinPosition != init.getChip().size()) {

        window.clear(userColor::Gray);
        window.draw(AssetManager::getBackground());

        for (auto i = init.getRoads().begin(); i != init.getRoads().end(); i++) {
            window.draw(i->getRoad());
        }

        for (auto i = init.getSquare().begin(); i != init.getSquare().end(); i++) {
            window.draw(i->getPoint());
        }

        for (auto i = movingPlaces.begin(); i != movingPlaces.end(); i++) {
            window.draw(i->getMovingPlace());
        }

        for (auto i = init.getChip().begin(); i != init.getChip().end(); i++) {
            window.draw(i->shape);
        }

        window.display();
    }
    else {
        AssetManager::getSoundWin().play();        

        while (AssetManager::getSoundWin().getStatus() == 2) {
            window.clear(sf::Color::Black);
            window.draw(AssetManager::getText());
            window.display();
        }
    }

}


void GameEngine::run() {

    while (window.isOpen()) {
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

void GameEngine::fillingBusyPoints(std::vector <PositionPoints>& positionPoints, std::vector <int>& occupPoints, std::vector <Chip> & chip) { //при chip const ERROR
    for (auto i = positionPoints.begin(); i != positionPoints.end(); i++) {
        i->setFreePoints() = true;        
    }

    occupPoints.clear();

    for (auto i = chip.begin(); i != chip.end(); i++) { 
        
        for (auto j = positionPoints.begin(); j != positionPoints.end(); j++) {

            if (j -> getPosition() == i -> getNumberPositionShape()) {
                j -> setFreePoints() = false;
                occupPoints.push_back(i -> getNumberPositionShape());
            }
        }

    }

};