#pragma once
#include <SFML/Graphics.hpp>

    class MovingPlace {
    private:
        sf::CircleShape place;
        int radiusMovingPlace = 4;
        sf::Color colorPlace = sf::Color::Red;
        int position;

    public:
        MovingPlace(int numberPosition);
        void setCoordinatePlace(float coordinateX, float coordinateY);

        const int& getPositin() { return position; }
        const sf::CircleShape& getMovingPlace() { return place; };
        const int& getRadiusMovingPlace() { return radiusMovingPlace; }
    };
	

