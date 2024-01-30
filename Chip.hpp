#pragma once
#include <SFML/Graphics.hpp>
#include "AssetManager.hpp"

struct Chip {
    sf::CircleShape shape;
    int numberPositionShape;
    int numberWinPOsitionShape;
    bool avtivChip = false;
    Chip(int position, int winPosition, int radiusChip, sf::Color color, float positionX, float positionY, AssetManager const& assetManager);
};
