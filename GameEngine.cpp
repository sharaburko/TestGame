#include "GameEngine.h"
#include <SFML/Window/Event.hpp>

void GameEngine::setInit(Config& config) {
    init.setChip(config);
    init.setSquare(config);
    init.setPositionPoints(config);
    init.setConnectPoints(config);
    init.setRoads();
}

GameEngine::GameEngine(const std::string& Title, unsigned modeWidth, unsigned modeHeight) {
    window.create(sf::VideoMode(modeWidth, modeHeight), Title, sf::Style::Close);
}

GameEngine::GameEngine() {
    window.create(sf::VideoMode(640, 480), "Sharaburko_Game", sf::Style::Close);
}

void GameEngine::inpute() {    
    time = clock.getElapsedTime().asMicroseconds();
    clock.restart();
    time = time / 900;

    countWinPosition = 0;

    while (window.pollEvent(event)) {

        if (event.type == sf::Event::Closed)
            window.close();
    }

    fillingBusyPoints(init.getPositionPoints(), occupPoints, init.getChip());

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !moveChip) {

        mousePosition = mouse.getPosition(window);
        activPosition = searchActivPosition(init.getPositionPoints(), mousePosition);

        if (activPosition) {

            for (auto it = init.getPositionPoints().begin(); it != init.getPositionPoints().end(); it++) {

                if (it->getPosition() == activPosition && !it->getFreePoints()) {
                    activChip = activPosition;
                    break;
                }

            }
        }

    }

    road = movesActivChip(activChip, init.getConnectPoints());
    deleteOccupPointsFromRoad(road, occupPoints);    

    if (!movingPlaces.empty()) {
        movingPlaces.clear();
    }

    for (auto it = init.getChip().begin(); it != init.getChip().end(); it++) {
        it->setShape().setRadius(init.getRadiusChip());
        it->setShape().setOutlineThickness(0);
    }

}

void GameEngine::update() {

    for (auto it = road.begin(); it != road.end(); it++) {

        movingPlaces.emplace_back(*(it->end() - 1));
    }

    for (auto it = movingPlaces.begin(); it != movingPlaces.end(); it++) {
        it->setCoordinatePointMovingPlace(init.getPositionPoint(it->getPositin()).x +
                                          (2 * init.getRadiusChip() - 2 * it->getRadiusMovingPlace()) / 2,
                                          init.getPositionPoint(it->getPositin()).y +
                                          (2 * init.getRadiusChip() - 2 * it->getRadiusMovingPlace()) / 2);
    }

    for (auto it = init.getChip().begin(); it != init.getChip().end(); it++) {

        if (it->getNumberPositionShape() == activChip) {
            it->selectChip();

            searchRoadActivPosition(road, activPosition);

            if (!road.empty()) {
                moveChip = true;
                float distanceX = init.getPositionPoint((*road.begin())[stepActivChip]).x - it->getShape().getPosition().x;
                float distanceY = init.getPositionPoint((*road.begin())[stepActivChip]).y - it->getShape().getPosition().y;
                float distance = sqrt(distanceX * distanceX + distanceY * distanceY);

                if (distance > 3) {
                    it->setShape().setPosition(it->getShape().getPosition().x + 0.01 * time * distanceX,
                                          it->getShape().getPosition().y + 0.01 * time * distanceY);
                }
                else {
                    it->setShape().setPosition(init.getPositionPoint((*road.begin())[stepActivChip]).x, init.getPositionPoint((*road.begin())[stepActivChip]).y);
                    AssetManager::getSoundMoveChip().play();
                    stepActivChip++;

                    if ((stepActivChip == (*road.begin()).size())) {
                        it->setNumberPositionShape() = activPosition;
                        stepActivChip = 1;
                        activChip = activPosition;
                        moveChip = false;
                    }

                }
            }

        }

         if (it->getNumberPositionShape() == it->getNumberWinPOsitionShape()) {
            it->selectWinPositionChip();
            countWinPosition++;
        }

    }
}

void GameEngine::draw() {
    window.clear(userColor::Gray);
    window.draw(AssetManager::instance().getBackground());

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
        window.draw(i->getShape());
    }

    window.display();
}

void GameEngine::end() {
    AssetManager::getSoundWin().play();

    while (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        window.clear(sf::Color::Black);
        window.draw(AssetManager::getText());
        window.display();
    }
}

void GameEngine::run() {

    while (window.isOpen()) {
        inpute();
        update();
        draw();

        if (countWinPosition == init.getChip().size()) {
            end();
            break;
        }
    }

}

int GameEngine::searchActivPosition(std::vector<PositionPoints> & positionPoints, sf::Vector2i const& mousePosition) {
    
    for (auto it = positionPoints.begin(); it != positionPoints.end(); it++) {
        sf::IntRect areaChip(it->getCoordinateX(), it->getCoordinateY(), init.getSizePointsX(), init.getSizePointsY());

        if (areaChip.contains(mousePosition.x, mousePosition.y)) {
            return it->getPosition();
        }

    }

    return 0;
}

void GameEngine::deleteOccupPointsFromRoad(std::vector <std::vector <int>>& road, std::vector <int> const& occupiredPoints) {
   
    for (auto j = road.begin(); j != road.end();) {

        for (auto k = occupiredPoints.begin(); k != occupiredPoints.end(); k++) {

            if (find((*j).begin() + 1, (*j).end(), *k) != (*j).end()) {
                j = road.erase(j);
                break;
            }

            if (k == occupiredPoints.end() - 1)
                j++;
        }
    }
}

void GameEngine::searchRoadActivPosition(std::vector <std::vector <int>> & road, int const& activPosition) {

    for (auto it = road.begin(); it != road.end(); ) {

        if (*(it->end() - 1) != activPosition) {
            it = road.erase(it);
        }
        else {
            ++it;
        }
            

    }

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