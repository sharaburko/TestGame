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
    }

    fillingBusyPoints(positionPoints, occupPoints, chips);

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !moveChip) {

        mousePosition = mouse.getPosition(window);
        activPosition = searchActivPosition(positionPoints, mousePosition);

        if (activPosition) {

            for (auto &it : positionPoints) {

                if (it.getPosition() == activPosition && !it.getFreePoints()) {
                    activChip = activPosition;
                    break;
                }

            }
        }

    }

    road = movesActivChip(activChip, connectPoints);
    deleteOccupPointsFromRoad(road, occupPoints);    

    if (!movingPlaces.empty()) {
        movingPlaces.clear();
    }

    for (auto &chip : chips) {
        chip.getShape().setRadius(radiusChip);
        chip.getShape().setOutlineThickness(0);
    }

}

void GameEngine::update() {

    for (auto road : road) {
        movingPlaces.emplace_back(road.back());
    }

    for (auto & movingPlace : movingPlaces) {
        movingPlace.setCoordinatePointMovingPlace(getPositionPoint(movingPlace.getPositin()).x +
                                          (2 * radiusChip - 2 * movingPlace.getRadiusMovingPlace()) / 2,
                                          getPositionPoint(movingPlace.getPositin()).y +
                                          (2 * radiusChip - 2 * movingPlace.getRadiusMovingPlace()) / 2);
    }

    for (auto &chip : chips) {

        if (chip.getNumberPositionShape() == activChip) {
            chip.selectChip();

            searchRoadActivPosition(road, activPosition);

            if (!road.empty()) {
                moveChip = true;
                float distanceX = getPositionPoint((road.front())[stepActivChip]).x - chip.getShape().getPosition().x;
                float distanceY = getPositionPoint((road.front())[stepActivChip]).y - chip.getShape().getPosition().y;
                float distance = sqrt(distanceX * distanceX + distanceY * distanceY);

                if (distance > 3) {
                    chip.getShape().setPosition(chip.getShape().getPosition().x + 0.01 * time * distanceX,
                                          chip.getShape().getPosition().y + 0.01 * time * distanceY);
                }
                else {
                    chip.getShape().setPosition(getPositionPoint((road.front())[stepActivChip]).x, getPositionPoint((road.front())[stepActivChip]).y);
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

    for (auto& road : roads) {
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

void GameEngine::run() {  

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
    setRoads();
    setChip(config);
}

int GameEngine::searchActivPosition(std::vector<PositionPoints> & positionPoints, sf::Vector2i const& mousePosition) {
    
    for (auto &positionPoint : positionPoints) {
        sf::IntRect areaChip(positionPoint.getCoordinateX(), positionPoint.getCoordinateY(), sizePoints.x, sizePoints.y);

        if (areaChip.contains(mousePosition.x, mousePosition.y)) {
            return positionPoint.getPosition();
        }

    }

    return 0;
}

void GameEngine::deleteOccupPointsFromRoad(std::vector <std::vector <int>>& roads, std::vector <int> const& occupiredPoints) {
   
    for (auto it = roads.begin(); it != roads.end();) {

        for (auto &occupiredPoint : occupiredPoints) {

            if (find((*it).begin() + 1, (*it).end(), occupiredPoint) != (*it).end()) {
                it = roads.erase(it);
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

void GameEngine::fillingBusyPoints(std::vector <PositionPoints>& positionPoints, std::vector <int>& occupPoints, std::vector <Chip> & chips) { //��� chip const ERROR
   
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

void GameEngine::setSquare(Config& config)
{
    square.reserve(config.getChipCount());

    for (int i = 0; i < config.getChipCount(); i++) {
        int NumberPositionPoint = config.getArrWinnerPoints(i);
        square.emplace_back(NumberPositionPoint, config.getCoordinatePoints(NumberPositionPoint).getCoordinateX(), config.getCoordinatePoints(NumberPositionPoint).getCoordinateY(), arrColor[i], radiusChip, sizePoints);
    }
}

void GameEngine::setPositionPoints(Config& config)
{
    positionPoints.reserve(config.getPointsCount());

    for (int i = 1; i <= config.getPointsCount(); i++) {
        PositionPoints tempPositionPoints(i, config.getCoordinatePoints(i).getCoordinateX(), config.getCoordinatePoints(i).getCoordinateY());
        positionPoints.push_back(tempPositionPoints);
    }
}

void GameEngine::setConnectPoints(Config& config)
{
    connectPoints.reserve(config.getConnectCount());
    for (int i = 0; i < config.getConnectCount(); i++) {
        config.getConnectionsBetweenPoints(i);
        std::vector <int> tempConnect;
        tempConnect.push_back(config.getConnectionsBetweenPoints(i).getConnectionP1());
        tempConnect.push_back(config.getConnectionsBetweenPoints(i).getConnectionP2());
        connectPoints.push_back(tempConnect);
        tempConnect.clear();
    }
}

void GameEngine::setRoads()
{
    roads.reserve(connectPoints.size());

    for (int i = 0; i < connectPoints.size(); i++) {

        Road tempRoad;

        int p1 = connectPoints[i].front() - 1; //��������� ��������
        int p2 = connectPoints[i].back() - 1;
        float p1X = positionPoints[p1].getCoordinateX();
        float p1Y = positionPoints[p1].getCoordinateY();
        float p2X = positionPoints[p2].getCoordinateX();
        float p2Y = positionPoints[p2].getCoordinateY();


        if (p1X == p2X) {
            sf::Vector2f size(Road::getWidthShape(), p2Y + sizePoints.y - p1Y -
                (sizePoints.y - Road::getWidthShape()));
            sf::Vector2f position(p1X + (2 * radiusChip - Road::getWidthShape()) / 2,
                p1Y + (2 * radiusChip - Road::getWidthShape()) / 2);
            tempRoad.setRoad().setSize(size);
            tempRoad.setRoad().setPosition(position);
        }
        else {
            sf::Vector2f size(p2X + sizePoints.x - p1X - (sizePoints.x -
                Road::getWidthShape()), Road::getWidthShape());
            tempRoad.setRoad().setSize(size);
            sf::Vector2f position(p1X + (2 * radiusChip - Road::getWidthShape()) / 2,
                p1Y + (2 * radiusChip - Road::getWidthShape()) / 2);
            tempRoad.setRoad().setPosition(position);
        }

        roads.push_back(tempRoad);
    }
}

const sf::Vector2f& GameEngine::getPositionPoint(int numberPosition) {

    for (auto it = positionPoints.begin(); it != positionPoints.end(); it++) {

        if (it->getPosition() == numberPosition) {
            return it->getCoordinate();
        }
    }
}