#include "RoadBackground.h"

RoadBackground::RoadBackground() {
    shape.setFillColor(colorShape);
}

RoadBackground::RoadBackground(sf::Vector2f& size, sf::Vector2f& position) {
    shape.setFillColor(colorShape);
    shape.setSize(size);
    shape.setPosition(position);
}

void RoadBackground::setPositionShape(float coordinateX, float coordinateY) {
    shape.setPosition(coordinateX, coordinateY);
}