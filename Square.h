#pragma once
#include <SFML/Graphics.hpp>
#include "AssetManager.h"

class Square
{
public:
    Square(int position, float positionX, float positionY, sf::Color color,
           int const& radiusChip);
    sf::RectangleShape& getPoint() { return point; }
private:
    int numberPositionSquare;
    sf::RectangleShape point;
    sf::Texture textureSquare;
};

