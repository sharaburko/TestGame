#include "Chip.h"


Chip::Chip(int position, int winPosition, sf::Color color, float positionX, float positionY, float const& radiusChip) {
    shape.setRadius(radiusChip);
    numberPositionShape = position;
    numberWinPOsitionShape = winPosition;
    shape.setFillColor(color);
    shape.setPosition(positionX, positionY);
    shape.setTexture(AssetManager::instance().getTexture("img/chip.png"));
    //shape.setTexture(&assetManager.textureChip);
}
