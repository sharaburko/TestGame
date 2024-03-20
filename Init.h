#pragma once
#include <vector>
#include "Chip.h"
#include "PositionPoints.h"
#include "Square.h"
#include "config.h"
#include "Color.h"

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

class Init
{
private:
    sf::Vector2f sizePoints{ 40, 40 };
    float radiusChip = 15;

    std::vector <Road> roads;
    std::vector <Chip> chips;
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

    //std::vector <Chip>& setVectorChip() { return chips; }//исправить

    std:: vector <Square>& getSquare() { return square; }
    std::vector <Chip>& getChips() { return chips; } //нельзя const
    std::vector <PositionPoints>& getPositionPoints() { return positionPoints; }
    const sf::Vector2f& getPositionPoint(int numberPosition);
   const float& getRadiusChip() { return radiusChip; }
   const float& getSizePointsX() { return sizePoints.x; }
   const float& getSizePointsY() { return sizePoints.y; }
   const std::vector<std::vector <int>> & getConnectPoints() { return connectPoints; }
};

