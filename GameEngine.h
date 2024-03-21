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
    MovingPlace(int numberPosition){
        place.setFillColor(colorPlace);
        place.setRadius(radiusMovingPlace);
        position = numberPosition;
    }

    void setCoordinatePointMovingPlace(float coordinateX, float coordinateY) {
        place.setPosition(coordinateX, coordinateY);
    };

    const int& getPositin() { return position; }
    const sf::CircleShape& getMovingPlace()  { return place;};
    const int& getRadiusMovingPlace() { return radiusMovingPlace; }
};

class Road {
private:
    sf::RectangleShape shape;
    static float widthShape;
    sf::Color colorShape = sf::Color(216, 216, 216);
public:
    Road() {
        shape.setFillColor(colorShape);
    }
    const sf::RectangleShape& getRoad() { return shape; }
    sf::RectangleShape& setRoad() { return shape; }
    void setPositionShape(float coordinateX, float coordinateY) {
        shape.setPosition(coordinateX, coordinateY);
    }
    void setColorShape(sf::Color color) { colorShape = color; }
    static const float& getWidthShape() { return widthShape; }
};

inline float Road::widthShape = 20;

class GameEngine
{
public:
	GameEngine(const std::string& Title, unsigned modeWidth, unsigned modeHeight);
	GameEngine();
	void run();

    void initialization(Config& config);
    void setInit(Config& config);
private:
    //Init init;

    sf::RenderWindow window;

    sf::Mouse mouse;
    sf::Clock clock;

    sf::Event event;

    sf::Vector2i mousePosition{ 0, 0 };
    int activPosition = 0;
    int activChip = 0;
    int stepActivChip = 1;
    int countWinPosition = 0;
    bool moveChip = false;
    float time = 0;
    float radiusChip = 15;
    sf::Vector2f sizePoints{ 40, 40 };

    std::vector <sf::Color> arrColor{ sf::Color::Black, sf::Color::White, sf::Color::Green,
                                     sf::Color::Blue, sf::Color::Magenta, userColor::Purple,
                                     userColor::Olive, userColor::Gray, userColor::Navy,
                                     userColor::Fuchsia, userColor::Teal };

    std::vector <Road> roads;
    std::vector <Square> square;
    std::vector <PositionPoints> positionPoints;
    std::vector<std::vector <int>> connectPoints;
    std::vector <Chip> chips;
    std::vector <int> occupPoints;
    std::vector <int> freePoints;
    std::vector <int> roadActivChip;
    std::vector <std::vector <int>> road;
    std::vector <MovingPlace> movingPlaces;


    int searchActivPosition(std::vector<PositionPoints> & positionPoints, sf::Vector2i const& mousePosition);
    void deleteOccupPointsFromRoad(std::vector <std::vector <int>>& roads, std::vector <int> const& occupiredPoints);
    void searchRoadActivPosition(std::vector <std::vector <int>> & roads, int const& activPosition);
    void fillingBusyPoints(std::vector<PositionPoints>& positionPoints, std::vector<int>& occupPoints, std::vector<Chip> & chips);

    void setChip(Config& config);
    void setSquare(Config& config);
    void setPositionPoints(Config& config);
    void setConnectPoints(Config& config);
    void setRoads();
    const std::vector<std::vector <int>>& getConnectPoints() { return connectPoints; }
    const sf::Vector2f& getPositionPoint(int numberPosition);

	void inpute();
	void update();
	void draw();
    void end();



};

