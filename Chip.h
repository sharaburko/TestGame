#pragma once
#include <SFML/Graphics.hpp>
#include "AssetManager.h"

class Chip {
private:
    sf::CircleShape shape;
    int numberPositionShape;
    int numberWinPOsitionShape;

public:
    Chip(int position, int winPosition, sf::Color color, float positionX, float positionY, float const& radiusChip);
    const int& getNumberPositionShape() { return numberPositionShape; }
    const int& getNumberWinPOsitionShape() { return numberWinPOsitionShape; }
    void setNumberPositionShape(int position) { numberPositionShape = position; }
    void selectChip();
    void selectWinPositionChip();
    sf::CircleShape& getShape() { return shape; }

};
