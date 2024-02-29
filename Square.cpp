#include "Square.h"
Square::Square(int position, float positionX, float positionY, sf::Color color,
    int const& radiusChip, sf::Vector2f const &sizePoints) {
    numberPositionSquare = position;
    point.setSize(sizePoints);
    point.setPosition(positionX - (sizePoints.x / 2 - radiusChip),
        positionY - (sizePoints.y / 2 - radiusChip));
    point.setFillColor(color);
    point.setTexture(AssetManager::getTexture("img/point.png"));
}