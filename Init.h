#pragma once
#include <vector>
#include "Chip.h"
#include "PositionPoints.h"
#include "Square.h"
#include "config.h"
#include "Color.h"

class Init
{
private:
    sf::Vector2f sizePoints{ 40, 40 };
    float radiusChip = 15;

    std::vector <Chip> chip;
    std::vector <Square> square;
    std::vector <PositionPoints> positionPoints;
    std::vector<std::vector <int>> connectPoints;
    std::vector <sf::Color> arrColor { sf::Color::Black, sf::Color::White, sf::Color::Green,
                                         sf::Color::Blue, sf::Color::Magenta, userColor::Purple,
                                         userColor::Olive, userColor::Gray, userColor::Navy, 
                                         userColor::Fuchsia, userColor::Teal };
public:
    void setChip(Config& config);
    void setSquare(Config& config);
    void setPositionPoints(Config& config);
    void setConnectPoints(Config& config);
    std::vector <Chip>& setVectorChip() { return chip; }

    std:: vector <Square>& getSquare() { return square; }
    const std::vector <Chip>& getChip() { return chip; }
    std::vector <PositionPoints>& getPositionPoints() { return positionPoints; }

   const float& getRadiusChip() { return radiusChip; }
   const float& getSizePointsX() { return sizePoints.x; }
   const float& getSizePointsY() { return sizePoints.y; }
   const std::vector<std::vector <int>> & getConnectPoints() { return connectPoints; }
};

