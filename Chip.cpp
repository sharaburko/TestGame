#include "Chip.hpp"

Chip::Chip(int position, int winPosition, int radiusChip, sf::Color color, float positionX, float positionY, AssetManager const& assetManager) {
    shape.setRadius(radiusChip);
    numberPositionShape = position;
    numberWinPOsitionShape = winPosition;
    shape.setFillColor(color);
    shape.setPosition(positionX, positionY);
    shape.setTexture(&assetManager.textureChip);
}
