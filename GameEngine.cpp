#include "GameEngine.h"
#include <SFML/Window/Event.hpp>

GameEngine::GameEngine(std::string & Title, unsigned modeWidth, unsigned modeHeight) {
    window.create(sf::VideoMode(modeWidth, modeHeight), Title, sf::Style::Close);
    this->level = level;
}

GameEngine::GameEngine(std::string& Title) {
    window.create(sf::VideoMode(640, 480), Title, sf::Style::Close);
}

GameEngine::GameEngine() {
    window.create(sf::VideoMode(640, 480), "Sharaburko_Game", sf::Style::Close);
}

void GameEngine::inpute() {    
    time = clock.getElapsedTime().asMicroseconds();
    clock.restart();
    time = time / 900;

    countWinPosition = 0;

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

    cursor.setPosition(sf::Vector2f(mouse.getPosition(window)));

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
                    getSoundMoveChip().play();
                    stepActivChip++;
                    numberOfMoves++;
                    setNumberOfMoves(numberOfMoves);

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

    window.draw(resultsTable.getRectangle());
    window.draw(resultsTable.getResult());
    window.draw(resultsTable.getTextRecord());

    window.draw(footerTable.getRectangle());
    window.draw(footerTable.getText());

    for (auto& square : square) {
        window.draw(square.getPoint());
    }

    for (auto& movingPlace : movingPlaces) {
        window.draw(movingPlace.getMovingPlace());
    }

    for (auto& chip : chips) {
        window.draw(chip.getShape());
    }

    window.draw(cursor);

    window.display();
}

void GameEngine::end() {
    AssetManager::getSoundWin().play();

    if (resultsTable.getRecord() > numberOfMoves || !resultsTable.getRecord()) {
        resultsTable.setNewRecord(level, numberOfMoves);
        setText("NEW RECORD " +std::to_string(numberOfMoves) + "\nYOU WIN!!", sf::Color::Red);
    }
    else {
        setText("YOU LOSE!!");
    }

    while (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        window.clear(sf::Color::Black);
        window.draw(text);
        cursor.setPosition(sf::Vector2f(mouse.getPosition(window)));
        window.draw(cursor);
        window.display();
    }

    clearData();
    IsMenuRunning = true;
}

void GameEngine::run(std::vector <Config>& configs) {
    constexpr auto level_offset = 1;


    while (window.isOpen()) {

        if (IsMenuRunning) {
            level = menu.run(window, mouse);                     

            //level = 0 - exit
            if (level) {
                initialization(configs[level - level_offset]);
            }
            else {
                window.close();
                break;
            }

        }
        else {
            inpute();
            update();
            draw();

            if (countWinPosition == chips.size()) {
                end();
            }           

            checkEvent(configs[level - level_offset]);
        }

    }

}

sf::Sound& GameEngine::getSoundMoveChip() {
    auto& manager = AssetManager::instance();
    manager.setBuffer("music/move.ogg");
    soundMoveChip.setBuffer(manager.getBuffer());
    return soundMoveChip;
}


void GameEngine::initialization(Config& config) {
    setSquare(config);
    setPositionPoints(config);
    setConnectPoints(config);
    setRoadsBackground();
    setChip(config);
    window.setTitle("Level " + std::to_string(level));
    resultsTable.setRecord(level);
    resultsTable.setPositionTable(window);
    footerTable.setPositionTable(window);
    footerTable.setText("R - Restart    Q - Quit");
    updateCursor();
    IsMenuRunning = false;
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

void GameEngine::setNumberOfMoves(int& result) {
    resultsTable.setResult(result);
}

void GameEngine::setText(const std::string &text, const sf::Color& color, const std::string pathText) {
    auto& manager = AssetManager::instance();
    manager.setFont(pathText);
    this->text.setFont(manager.getFont());
    this->text.setPosition(80, 200);
    this->text.setCharacterSize(60);
    this->text.setString(text);
    this->text.setFillColor(color);
}

void GameEngine::updateCursor() {
    window.setMouseCursorVisible(false);
    cursor.setTexture(*AssetManager::getTexture("img/cursor.png"));
}

void GameEngine::checkEvent(Config& config) {
    while (window.pollEvent(event)) {

        if (event.type == sf::Event::Closed) {
            clearData();
            IsMenuRunning = true;
        }


        if (event.type == sf::Event::KeyPressed) {

            if (event.key.code == sf::Keyboard::Q) {
                clearData();
                IsMenuRunning = true;
            }

            if (event.key.code == sf::Keyboard::R) {
                restart(config);
            }
        }

    }
}

void GameEngine::clearData() {
    roadsBackground.clear();
    square.clear();
    positionPoints.clear();
    connectPoints.clear();
    chips.clear();

    numberOfMoves = 0;
    activPosition = 0;
    activChip = 0;
    stepActivChip = 1;
    countWinPosition = 0;
    moveChip = false;
    time = 0;
    setNumberOfMoves(numberOfMoves);
}

void GameEngine::restart(Config& config) {
    clearData();
    initialization(config);

}
