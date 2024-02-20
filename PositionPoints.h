#pragma once
class PositionPoints
{
public:
    PositionPoints(int position, float x, float y) {
        this->position = position;
        coordinateX = x;
        coordinateY = y;
    }
    bool& setFreePoints()  { return freePoints; }
    const bool& getFreePoints() { return freePoints; }
    const float & getCoordinateX() { return coordinateX; }
    const float& getCoordinateY() { return coordinateY; }
    const int& getPosition() {return position;}
private:
        int position;
        float coordinateX;
        float coordinateY;
        bool freePoints = true;
};

