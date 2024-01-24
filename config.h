#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

class Config {
    int chipCount = 0;
    int pointsCount = 0;
    int connectCount = 0;
    struct Coordinate;
    struct ConnectionsBetweenPoints;
    std::vector <Coordinate> points;
    std::vector <int> arrStartPoints;
    std::vector <int> arrWinnerPoints;
    std::vector <ConnectionsBetweenPoints> connection;

    struct Coordinate { 
        Coordinate() { x = y = 0; }
        Coordinate(const float x, const float y) : x(x), y(y) {}
        float getCoordinateX() const { return x; }
        float getCoordinateY() const { return y; }
    private:
        float x, y;
    };          
    
    struct ConnectionsBetweenPoints { 
        ConnectionsBetweenPoints(const int p1, const int p2) : p1(p1), p2(p2) {}
        int getConnectionP1() const { return p1; }
        int getConnectionP2() const { return p2; }
     private:
        int p1, p2; 
    };

public:
    void readConfig(std::string const configFilePath);    
    int getPointsCount() const {return pointsCount;}
    int getChipCount() const { return chipCount; }
    int getArrStartPoints(int i) { return arrStartPoints[i]; }
    int getArrWinnerPoints(int i) { return arrWinnerPoints[i]; }
    int getConnectCount() const { return connectCount; }
    Coordinate getCoordinatePoints(int pointNumber) { return points[pointNumber - 1]; }
    ConnectionsBetweenPoints getConnectionsBetweenPoints(int connectCount) { return connection[connectCount]; }
}; 