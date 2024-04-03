#include "MovingPlace.h"

MovingPlace::MovingPlace(int numberPosition) {
    place.setFillColor(colorPlace);
    place.setRadius(radiusMovingPlace);
    position = numberPosition;
}

void MovingPlace::setCoordinatePlace(float coordinateX, float coordinateY) {
    place.setPosition(coordinateX, coordinateY);
}
