#include "Chip.h"


Chip::Chip(int position, int winPosition, sf::Color color, float positionX, float positionY, float const& radiusChip) {
    shape.setRadius(radiusChip);
    numberPositionShape = position;
    numberWinPOsitionShape = winPosition;
    shape.setFillColor(color);
    shape.setPosition(positionX, positionY);
    shape.setTexture(AssetManager::getTexture("img/chip.png"));

}

void Chip::selectChip() {
    this->shape.setRadius(shape.getRadius() * 1.1);
    this->shape.setOutlineThickness(-2);
    this->shape.setOutlineColor(sf::Color::White);
}

void Chip::selectWinPositionChip() {
    this->shape.setOutlineThickness(-2);
    this->shape.setOutlineColor(sf::Color::Yellow);
}
