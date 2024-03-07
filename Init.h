#pragma once
#include <vector>
#include "Chip.h"
#include "PositionPoints.h"
#include "Square.h"
#include "config.h"
#include "Color.h"

class Road {
private:
    Road() {
        road.setFillColor(colorRoad);
    }
    sf::RectangleShape road;
    float widthRoad = 20;
    sf::Color colorRoad = sf::Color((216, 216, 216));
public:
    const sf::RectangleShape& getRoad() { return road; }
    sf::RectangleShape& setRoad() { return road; }
    void setPositionRoad(float coordinateX, float coordinateY) {
        road.setPosition(coordinateX, coordinateY);
    }
    const float& getWidthRoad() { return widthRoad; }
};

class Init
{
private:
    sf::Vector2f sizePoints{ 40, 40 };
    float radiusChip = 15;

    std::vector <Road> roads;
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
    void setRoads();
    std::vector <Road>& getRoads() { return roads; }

    std::vector <Chip>& setVectorChip() { return chip; }

    std:: vector <Square>& getSquare() { return square; }
    const std::vector <Chip>& getChip() { return chip; }
    std::vector <PositionPoints>& getPositionPoints() { return positionPoints; }

   const float& getRadiusChip() { return radiusChip; }
   const float& getSizePointsX() { return sizePoints.x; }
   const float& getSizePointsY() { return sizePoints.y; }
   const std::vector<std::vector <int>> & getConnectPoints() { return connectPoints; }
};

