#pragma once
#include <SFML/Graphics.hpp>


struct Chip {
    sf::CircleShape shape;
    int numberPositionShape;
    int numberWinPOsitionShape;
    bool avtivChip = false;
    Chip(int position, int winPosition, sf::Color color, float positionX, float positionY, AssetManager const& assetManager, float const& radiusChip);
  
};
