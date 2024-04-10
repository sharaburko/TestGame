#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "move.h"
#include "Color.h"
#include "Chip.h"
#include "PositionPoints.h"
#include "Square.h"
#include "config.h"
#include "menu.h"
#include "MovingPlace.h"
#include "RoadBackground.h"
#include "Table.h"

class GameEngine {
    friend Menu;
public:
	GameEngine(std::string& Title, unsigned modeWidth, unsigned modeHeight);
    GameEngine(std::string& Title);
	GameEngine();

	void run(std:: vector <Config> & configs);
private:
    sf::RenderWindow window;
    sf::Event event;
    sf::Mouse mouse;
    sf::Clock clock;

    ResultsTable resultsTable;
    FooterTable footerTable;
    Menu menu;

    sf::Sound soundMoveChip;
    sf::Sprite cursor;
    sf::Text text;
        
    int numberOfMoves = 0;
    int activPosition = 0;
    int activChip = 0;
    int stepActivChip = 1;
    int countWinPosition = 0;
    bool moveChip = false;
    bool IsMenuRunning = true;
    int level = 0;
    float time = 0;
    float radiusChip = 15;
    sf::Vector2i mousePosition{ 0, 0 };
    sf::Vector2f sizePoints{ 40, 40 };
    std::vector <sf::Color> arrColor{ sf::Color::Black, sf::Color::White, sf::Color::Green,
                                     sf::Color::Blue, sf::Color::Magenta, userColor::Purple,
                                     userColor::Olive, userColor::Gray, userColor::Navy,
                                     userColor::Fuchsia, userColor::Teal };

    std::vector <RoadBackground> roadsBackground;
    std::vector <Square> square;
    std::vector <PositionPoints> positionPoints;
    std::vector<std::vector <int>> connectPoints;
    std::vector <Chip> chips;
    std::vector <int> occupPoints;
    std::vector <std::vector <int>> roads;
    std::vector <MovingPlace> movingPlaces;

    int searchActivPosition();
    void deleteOccupPointsFromRoad();
    void searchRoadActivPosition();
    void fillingBusyPoints();

    void checkEvent(Config& config);
    void clearData();
    void initialization(Config& config);
    void setChip(Config& config);
    void setSquare(Config& config);
    void setPositionPoints(Config& config);
    void setConnectPoints(Config& config);
    void setRoadsBackground();
    void setNumberOfMoves(int& result);
    void updateCursor();
    void setText(const std::string &text, const sf::Color& color = sf::Color::White, const std::string pathText = "arial.ttf");

    sf::Sound& getSoundMoveChip();
    const std::vector<std::vector <int>>& getConnectPoints() { return connectPoints; }
    const sf::Vector2f& getPositionPoint(int numberPosition);
   
    void restart(Config& config);
	void inpute();
	void update();
	void draw();
    void end();
};

