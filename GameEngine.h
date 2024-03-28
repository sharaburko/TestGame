#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "move.h"
#include "Color.h"
#include "Chip.h"
#include "PositionPoints.h"
#include "Square.h"
#include "config.h"

class MovingPlace {
private:
    sf::CircleShape place;
    int radiusMovingPlace = 4;
    sf::Color colorPlace = sf::Color::Red;
    int position;

public:
    MovingPlace(int numberPosition);
    void setCoordinatePlace(float coordinateX, float coordinateY);

    const int& getPositin() { return position; }
    const sf::CircleShape& getMovingPlace()  { return place;};
    const int& getRadiusMovingPlace() { return radiusMovingPlace; }
};

class RoadBackground {
private:
    sf::RectangleShape shape;
    static float widthShape;
    sf::Color colorShape = sf::Color(216, 216, 216);
public:
    RoadBackground();
    RoadBackground(sf::Vector2f& size, sf::Vector2f& position);
    const sf::RectangleShape& getRoad() { return shape; }
    void setSizeShape(sf::Vector2f &size) { shape.setSize(size); }
    void setPositionShape(sf::Vector2f& position) { shape.setPosition(position); }
    void setPositionShape(float coordinateX, float coordinateY);
    void setColorShape(sf::Color color) { colorShape = color; }
    static const float& getWidthShape() { return widthShape; }
};

inline float RoadBackground::widthShape = 20;

class GameEngine {
public:
	GameEngine(const std::string& Title, unsigned modeWidth, unsigned modeHeight);
    GameEngine(const std::string& Title);
	GameEngine();
	void run(Config& config);

    class ResultsTable {
    private:
        sf::RectangleShape rectangl;
        sf::Text result;
        sf::Text record;
    };

private:
    sf::RenderWindow window;

    sf::Mouse mouse;
    sf::Clock clock;

    sf::Event event;


    
    int numberOfMoves = 0;
    int activPosition = 0;
    int activChip = 0;
    int stepActivChip = 1;
    int countWinPosition = 0;
    bool moveChip = false;
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

    void initialization(Config& config);
    void setChip(Config& config);
    void setSquare(Config& config);
    void setPositionPoints(Config& config);
    void setConnectPoints(Config& config);
    void setRoadsBackground();

    const std::vector<std::vector <int>>& getConnectPoints() { return connectPoints; }
    const sf::Vector2f& getPositionPoint(int numberPosition);

	void inpute();
	void update();
	void draw();
    void end();
};

