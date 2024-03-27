#include "GameEngine.h"
#include <SFML/Window/Event.hpp>

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

        if (event.type == sf::Keyboard::Escape)
            window.close();    
    }

    fillingBusyPoints();

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !moveChip) {

        mousePosition = mouse.getPosition(window);
        activPosition = searchActivPosition();

        if (activPosition) {

            for (auto &positionPoint : positionPoints) {

                if (positionPoint.getPosition() == activPosition && !positionPoint.getFreePoints()) {
                    activChip = activPosition;
                    break;
                }

            }
        }

    }

    roads = movesActivChip(activChip, connectPoints);
    deleteOccupPointsFromRoad();    

    if (!movingPlaces.empty()) {
        movingPlaces.clear();
    }

    for (auto &chip : chips) {
        chip.getShape().setRadius(radiusChip);
        chip.getShape().setOutlineThickness(0);
    }

}

void GameEngine::update() {

    for (auto road : roads) {
        movingPlaces.emplace_back(road.back());
    }

    for (auto & movingPlace : movingPlaces) {
        movingPlace.setCoordinatePlace(getPositionPoint(movingPlace.getPositin()).x +
                                          (2 * radiusChip - 2 * movingPlace.getRadiusMovingPlace()) / 2,
                                          getPositionPoint(movingPlace.getPositin()).y +
                                          (2 * radiusChip - 2 * movingPlace.getRadiusMovingPlace()) / 2);
    }

    for (auto &chip : chips) {

        if (chip.getNumberPositionShape() == activChip) {
            chip.selectChip();

            searchRoadActivPosition();

            if (!roads.empty()) {
                moveChip = true;
                float distanceX = getPositionPoint((roads.front())[stepActivChip]).x - chip.getShape().getPosition().x;
                float distanceY = getPositionPoint((roads.front())[stepActivChip]).y - chip.getShape().getPosition().y;
                float distance = sqrt(distanceX * distanceX + distanceY * distanceY);

                if (distance > 3) {
                    chip.getShape().setPosition(chip.getShape().getPosition().x + 0.01 * time * distanceX,
                                          chip.getShape().getPosition().y + 0.01 * time * distanceY);
                }
                else {
                    chip.getShape().setPosition(getPositionPoint((roads.front())[stepActivChip]).x, getPositionPoint((roads.front())[stepActivChip]).y);
                    AssetManager::getSoundMoveChip().play();
                    stepActivChip++;

                    if ((stepActivChip == (roads.front()).size())) {
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
    window.draw(AssetManager::instance().getBackground("img/background.jpg"));

    for (auto& road : roadsBackground) {
        window.draw(road.getRoad());
    }

    for (auto& square : square) {
        window.draw(square.getPoint());
    }

    for (auto& movingPlace : movingPlaces) {
        window.draw(movingPlace.getMovingPlace());
    }

    for (auto& chip : chips) {
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

void GameEngine::run(Config& config) {
    initialization(config);

    while (window.isOpen()) {
        inpute();
        update();
        draw();

        if (countWinPosition == chips.size()) {
            end();
            break;
        }
    }

}

void GameEngine::initialization(Config& config) {
    setSquare(config);
    setPositionPoints(config);
    setConnectPoints(config);
    setRoadsBackground();
    setChip(config);
}

int GameEngine::searchActivPosition() {
    
    for (auto &positionPoint : positionPoints) {
        sf::IntRect areaChip(positionPoint.getCoordinateX(), positionPoint.getCoordinateY(), sizePoints.x, sizePoints.y);

        if (areaChip.contains(mousePosition.x, mousePosition.y)) {
            return positionPoint.getPosition();
        }

    }

    return 0;
}

void GameEngine::deleteOccupPointsFromRoad() {
   
    for (auto it = roads.begin(); it != roads.end();) {

        for (auto &occupiredPoint : occupPoints) {

            if (find((*it).begin() + 1, (*it).end(), occupiredPoint) != (*it).end()) {
                it = roads.erase(it);
                break;
            }

            if (occupiredPoint == occupPoints.back())
                it++;
        }
    }
}

void GameEngine::searchRoadActivPosition() {

    for (auto it = roads.begin(); it != roads.end(); ) {

        if (it->back() != activPosition) {
            it = roads.erase(it);
        }
        else {
            ++it;
        }            

    }

}

void GameEngine::fillingBusyPoints() { 
   
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

void GameEngine::setChip(Config& config) {
    chips.reserve(config.getChipCount());

    for (int i = 0; i < config.getChipCount(); i++) {
        int numberPositionShape = config.getArrStartPoints(i);
        chips.emplace_back(config.getArrStartPoints(i), config.getArrWinnerPoints(i), arrColor[i], config.getCoordinatePoints(numberPositionShape).getCoordinateX(), config.getCoordinatePoints(numberPositionShape).getCoordinateY(), radiusChip);
    }
}

void GameEngine::setSquare(Config& config) {
    square.reserve(config.getChipCount());

    for (int i = 0; i < config.getChipCount(); i++) {
        int NumberPositionPoint = config.getArrWinnerPoints(i);
        square.emplace_back(NumberPositionPoint, config.getCoordinatePoints(NumberPositionPoint).getCoordinateX(), config.getCoordinatePoints(NumberPositionPoint).getCoordinateY(), arrColor[i], radiusChip, sizePoints);
    }
}

void GameEngine::setPositionPoints(Config& config) {
    positionPoints.reserve(config.getPointsCount());

    for (int i = 1; i <= config.getPointsCount(); i++) {
        positionPoints.emplace_back(i, config.getCoordinatePoints(i).getCoordinateX(), config.getCoordinatePoints(i).getCoordinateY());
    }
}

void GameEngine::setConnectPoints(Config& config) {
    connectPoints.reserve(config.getConnectCount());

    for (int i = 0; i < config.getConnectCount(); i++) {
        std::vector <int> tempConnect;
        tempConnect.push_back(config.getConnectionsBetweenPoints(i).getConnectionP1());
        tempConnect.push_back(config.getConnectionsBetweenPoints(i).getConnectionP2());
        connectPoints.push_back(tempConnect);
        tempConnect.clear();
    }
}

void GameEngine::setRoadsBackground() {
    roadsBackground.reserve(connectPoints.size());

    for (auto connectPoint : connectPoints) {
        sf::Vector2f positionP1 = getPositionPoint(connectPoint.front());
        sf::Vector2f positionP2 = getPositionPoint(connectPoint.back());
        sf::Vector2f sizeShape;
        sf::Vector2f positionShape;

        if (positionP1.x == positionP2.x) {
            sizeShape.x = RoadBackground::getWidthShape();
            sizeShape.y = positionP2.y + sizePoints.y - positionP1.y - (sizePoints.y - RoadBackground::getWidthShape());

            positionShape.x = positionP1.x + (2 * radiusChip - RoadBackground::getWidthShape()) / 2;
            positionShape.y = positionP1.y + (2 * radiusChip - RoadBackground::getWidthShape()) / 2;
        }
        else {
            sizeShape.x = positionP2.x + sizePoints.x - positionP1.x - (sizePoints.x - RoadBackground::getWidthShape());
            sizeShape.y = RoadBackground::getWidthShape();

            positionShape.x = positionP1.x + (2 * radiusChip - RoadBackground::getWidthShape()) / 2;
            positionShape.y = positionP1.y + (2 * radiusChip - RoadBackground::getWidthShape()) / 2;
        }

        roadsBackground.emplace_back(sizeShape, positionShape);
    }
}

const sf::Vector2f& GameEngine::getPositionPoint(int numberPosition) {

    for (auto it = positionPoints.begin(); it != positionPoints.end(); it++) {

        if (it->getPosition() == numberPosition) {
            return it->getCoordinate();
        }
    }
}

MovingPlace::MovingPlace(int numberPosition) {
    place.setFillColor(colorPlace);
    place.setRadius(radiusMovingPlace);
    position = numberPosition;
}

void MovingPlace::setCoordinatePlace(float coordinateX, float coordinateY) {
    place.setPosition(coordinateX, coordinateY);
}

RoadBackground::RoadBackground() {
    shape.setFillColor(colorShape);
}

RoadBackground::RoadBackground(sf::Vector2f& size, sf::Vector2f& position) {
    shape.setFillColor(colorShape);
    shape.setSize(size);
    shape.setPosition(position);
}

void RoadBackground::setPositionShape(float coordinateX, float coordinateY) {
    shape.setPosition(coordinateX, coordinateY);
}