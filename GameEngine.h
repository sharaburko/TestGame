#pragma once
#include <SFML/Graphics.hpp>
#include "Init.h"
#include <vector>
#include "move.h"
#include "Color.h"

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


    sf::Vector2i mousePosition{ 0, 0 };
    int activPosition = 0;
    int activChip = 0;
    int stepActivChip = 1;
    int countWinPosition = 0;
    bool moveChip = false;


    std::vector <int> occupPoints;
    std::vector <int> freePoints;
    std::vector <int> roadActivChip;
    std::vector <std::vector <int>> road;

    int searchActivPosition(std::vector<PositionPoints> & positionPoints, sf::Vector2i const& mousePosition);
    void searchFreePointsChip(std::vector <std::vector <int>>& road, std::vector <int> const& occupiredPoints);
    std::vector <int> const searchRoadActivChip(std::vector <std::vector <int>> const& road, int const& activPosition);
    void fillingBusyPoints(std::vector<PositionPoints>& positionPoints, std::vector<int>& occupPoints, std::vector<Chip> const& chip);

	void inpute();
	void update();
	void draw();

};

