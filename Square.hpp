#pragma once
#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"

struct Square {
    int numberPositionSquare;
    sf::RectangleShape point;
    sf::Texture textureSquare;
    Square(int position, int radiusChip, sf::Vector2f sizePoints, float positionX, float positionY, sf::Color color, AssetManager const& assetManager);
};

