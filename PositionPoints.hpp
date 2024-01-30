#pragma once

struct PositionPoints {
    int position;
    float coordinateX;
    float coordinateY;
    bool freePoints = true;
    PositionPoints(int position, float x, float y);
};
