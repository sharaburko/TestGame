#pragma once
#include <SFML/Graphics.hpp>
#include "AssetManager.h"

class Chip {
public:
    sf::CircleShape shape;
    int numberPositionShape;
    int numberWinPOsitionShape;
    // bool avtivChip = false;

public:
    Chip(int position, int winPosition, sf::Color color, float positionX, float positionY, float const& radiusChip);
    const int& getNumberPositionShape() { return numberPositionShape; }
    const int& getNumberWinPOsitionShape() { return numberWinPOsitionShape; }
    int& setNumberPositionShape() { return numberPositionShape; }
    void selectChip();
    void selectWinPositionChip();
};
