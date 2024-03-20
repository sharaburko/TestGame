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

    fillingBusyPoints(init.getPositionPoints(), occupPoints, init.getChips());

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !moveChip) {

        mousePosition = mouse.getPosition(window);
        activPosition = searchActivPosition(init.getPositionPoints(), mousePosition);

        if (activPosition) {

            for (auto &it : init.getPositionPoints()) {

                if (it.getPosition() == activPosition && !it.getFreePoints()) {
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

    for (auto &chip : init.getChips()) {
        chip.getShape().setRadius(init.getRadiusChip());
        chip.getShape().setOutlineThickness(0);
    }

}

void GameEngine::update() {

    for (auto road : road) {
        movingPlaces.emplace_back(road.back());
    }

    for (auto & movingPlace : movingPlaces) {
        movingPlace.setCoordinatePointMovingPlace(init.getPositionPoint(movingPlace.getPositin()).x +
                                          (2 * init.getRadiusChip() - 2 * movingPlace.getRadiusMovingPlace()) / 2,
                                          init.getPositionPoint(movingPlace.getPositin()).y +
                                          (2 * init.getRadiusChip() - 2 * movingPlace.getRadiusMovingPlace()) / 2);
    }

    for (auto &chip : init.getChips()) {

        if (chip.getNumberPositionShape() == activChip) {
            chip.selectChip();

            searchRoadActivPosition(road, activPosition);

            if (!road.empty()) {
                moveChip = true;
                float distanceX = init.getPositionPoint((road.front())[stepActivChip]).x - chip.getShape().getPosition().x;
                float distanceY = init.getPositionPoint((road.front())[stepActivChip]).y - chip.getShape().getPosition().y;
                float distance = sqrt(distanceX * distanceX + distanceY * distanceY);

                if (distance > 3) {
                    chip.getShape().setPosition(chip.getShape().getPosition().x + 0.01 * time * distanceX,
                                          chip.getShape().getPosition().y + 0.01 * time * distanceY);
                }
                else {
                    chip.getShape().setPosition(init.getPositionPoint((road.front())[stepActivChip]).x, init.getPositionPoint((road.front())[stepActivChip]).y);
                    AssetManager::getSoundMoveChip().play();
                    stepActivChip++;

                    if ((stepActivChip == (road.front()).size())) {
                        chip.setNumberPositionShape(activPosition);
                        stepActivChip = 1;
                        activChip = activPosition;
                        moveChip = false;
                    }

                }
            }

        }

         if (chip.getNumberPositionShape() == chip.getNumberWinPOsitionShape()) {
             chip.selectWinPositionChip();
            countWinPosition++;
        }

    }
}

void GameEngine::draw() {
    window.clear(userColor::Gray);
    window.draw(AssetManager::instance().getBackground());

    for (auto& road : init.getRoads()) {
        window.draw(road.getRoad());
    }

    for (auto& square : init.getSquare()) {
        window.draw(square.getPoint());
    }

    for (auto& movingPlace : movingPlaces) {
        window.draw(movingPlace.getMovingPlace());
    }

    for (auto& chip : init.getChips()) {
        window.draw(chip.getShape());
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

        if (countWinPosition == init.getChips().size()) {
            end();
            break;
        }
    }

}

int GameEngine::searchActivPosition(std::vector<PositionPoints> & positionPoints, sf::Vector2i const& mousePosition) {
    
    for (auto &positionPoint : positionPoints) {
        sf::IntRect areaChip(positionPoint.getCoordinateX(), positionPoint.getCoordinateY(), init.getSizePointsX(), init.getSizePointsY());

        if (areaChip.contains(mousePosition.x, mousePosition.y)) {
            return positionPoint.getPosition();
        }

    }

    return 0;
}

void GameEngine::deleteOccupPointsFromRoad(std::vector <std::vector <int>>& road, std::vector <int> const& occupiredPoints) {
   
    for (auto it = road.begin(); it != road.end();) {

        for (auto &occupiredPoint : occupiredPoints) {

            if (find((*it).begin() + 1, (*it).end(), occupiredPoint) != (*it).end()) {
                it = road.erase(it);
                break;
            }

            if (occupiredPoint == occupiredPoints.back())
                it++;
        }
    }
}

void GameEngine::searchRoadActivPosition(std::vector <std::vector <int>> & roads, int const& activPosition) {

    for (auto it = roads.begin(); it != roads.end(); ) {

        if (it->back() != activPosition) {
            it = roads.erase(it);
        }
        else {
            ++it;
        }
            

    }

}

void GameEngine::fillingBusyPoints(std::vector <PositionPoints>& positionPoints, std::vector <int>& occupPoints, std::vector <Chip> & chips) { //при chip const ERROR
   
    for (auto &positionPoint : positionPoints) {
        positionPoint.setFreePoints() = true;
    }

    occupPoints.clear();

    for (auto &chip : chips) { 
        
        for (auto &positionPoint : positionPoints) {

            if (positionPoint.getPosition() == chip.getNumberPositionShape()) {
                positionPoint.setFreePoints() = false;
                occupPoints.push_back(chip.getNumberPositionShape());
            }
        }

    }

};