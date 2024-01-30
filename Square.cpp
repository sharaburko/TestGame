#include "Square.hpp"

Square :: Square(int position, int radiusChip, sf::Vector2f sizePoints, float positionX, float positionY, sf::Color color, AssetManager const& assetManager) {
    numberPositionSquare = position;
    point.setSize(sizePoints);
    point.setPosition(positionX - (sizePoints.x / 2 - radiusChip), positionY - (sizePoints.y / 2 - radiusChip));
    point.setFillColor(color);
    point.setTexture(&assetManager.textureSquare);
}
