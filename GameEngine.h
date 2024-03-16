#pragma once
#include <SFML/Graphics.hpp>
#include "Init.h"
#include <vector>
#include "move.h"
#include "Color.h"



class MovingPlace {
private:
    sf::CircleShape place;
    int radiusMovingPlace = 4;
    sf::Color colorPlace = sf::Color::Red;

public:
    MovingPlace(){
        place.setFillColor(colorPlace);
        place.setRadius(radiusMovingPlace);
    }

    void setPositionMovingPlace(float coordinateX, float coordinateY) {
        place.setPosition(coordinateX, coordinateY);
    };

    const sf::CircleShape& getMovingPlace()  {
        return place;
    };
    const int& getRadiusMovingPlace() { return radiusMovingPlace; }
};

class GameEngine
{
public:
	GameEngine(const std::string& Title, unsigned modeWidth, unsigned modeHeight);
	GameEngine();
	void run();

    void setInit(Config& config);
private:
    Init init;

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


    std::vector <int> occupPoints;
    std::vector <int> freePoints;
    std::vector <int> roadActivChip;
    std::vector <std::vector <int>> road;
    std::vector <MovingPlace> movingPlaces;


    int searchActivPosition(std::vector<PositionPoints> & positionPoints, sf::Vector2i const& mousePosition);
    void deleteOccupPointsFromRoad(std::vector <std::vector <int>>& road, std::vector <int> const& occupiredPoints);
    void searchRoadActivPosition(std::vector <std::vector <int>> & road, int const& activPosition);
    void fillingBusyPoints(std::vector<PositionPoints>& positionPoints, std::vector<int>& occupPoints, std::vector<Chip> & chip);

	void inpute();
	void update();
	void draw();

};

