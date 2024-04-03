#pragma once
#include <SFML/Graphics.hpp>

class RoadBackground {
private:
    sf::RectangleShape shape;
    static float widthShape;
    sf::Color colorShape = sf::Color(216, 216, 216);
public:
    RoadBackground();
    RoadBackground(sf::Vector2f& size, sf::Vector2f& position);
    const sf::RectangleShape& getRoad() { return shape; }
    void setSizeShape(sf::Vector2f& size) { shape.setSize(size); }
    void setPositionShape(sf::Vector2f& position) { shape.setPosition(position); }
    void setPositionShape(float coordinateX, float coordinateY);
    void setColorShape(sf::Color color) { colorShape = color; }
    static const float& getWidthShape() { return widthShape; }
};

inline float RoadBackground::widthShape = 20;

