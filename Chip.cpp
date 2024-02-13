#include "Chip.h"

Chip::Chip(int position, int winPosition, sf::Color color, float positionX, float positionY, AssetManager const& assetManager, float const& radiusChip) {
    shape.setRadius(radiusChip);
    numberPositionShape = position;
    numberWinPOsitionShape = winPosition;
    shape.setFillColor(color);
    shape.setPosition(positionX, positionY);
    shape.setTexture(&assetManager.textureChip);
}
