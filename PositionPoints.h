#pragma once
#include <SFML/Graphics.hpp>

class PositionPoints
{
public:
    PositionPoints(int position, float x, float y) {
        this->position = position;
        coordinateX = x;
        coordinateY = y;
        coordinate.x = x;
        coordinate.y = y;
    }
    bool& setFreePoints()  { return freePoints; }
    const bool& getFreePoints() { return freePoints; }
    const float & getCoordinateX() { return coordinateX; }
    const float& getCoordinateY() { return coordinateY; }
    const sf::Vector2f & getCoordinate() { return coordinate; }
    const int& getPosition() {return position;}
private:
        int position;
        float coordinateX;
        float coordinateY;
        sf::Vector2f coordinate;
        bool freePoints = true;
};

