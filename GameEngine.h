#pragma once
#include <SFML/Graphics.hpp>
#include "Chip.h"
#include <vector>
#include "move.h"

class GameEngine
{
public:
	GameEngine(const std::string& Title, unsigned modeWidth, unsigned modeHeight);
	GameEngine();
    const sf::RenderWindow &getWindow();
	void run();
private:


    sf::RenderWindow window;
    sf::Mouse mouse;
    sf::Clock clock;

    std::vector <Chip> chip;

    //float radiusChip = 15;
    sf::Vector2f sizePoints{40, 40 };
    sf::Vector2i mousePosition{ 0, 0 };
    int activPosition = 0;
    int activChip = 0;
    //int stepActivChip = 1;
    //int countWinPosition = 0;
    bool moveChip = false;

    std::vector <std::vector <int>> road;

    //void initialization(Config& config, std::vector <std::vector <int>>& connectPoints, std::vector <Chip>& chip, std::vector <Square>& square, std::vector <PositionPoints>& positionPoints, float const& radiusChip);
    int searchActivPosition(std::vector<PositionPoints> const& positionPoints, sf::Vector2i const& mousePosition);
    void searchFreePointsChip(std::vector <std::vector <int>>& road, std::vector <int> const& occupiredPoints);
    std::vector <int> const searchRoadActivChip(std::vector <std::vector <int>> const& road, int const& activPosition);


	void inpute();
	void update();
	void draw();

};

