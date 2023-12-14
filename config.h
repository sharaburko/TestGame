#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Config {
    struct Coordinate { //структура для хранения координат точек
        float x, y;
        Coordinate() { x = y = 0; }
        Coordinate(const float x, const float y) : x(x), y(y) {}
        float getCoordinateX() const { return x; }
        float getCoordinateY() const { return y; }

    };

    int chipCount = 0;                 //количество фишек
    int pointsCount = 0;               //количество точек
    vector <Coordinate> points;        //вектор с координатами точек
    vector <int> arrStartPoints;       //стартовые позиции фишек
    vector <int> arrWinnerPoints;      //победные позиции фишек
    int connectCount = 0;              //количество соединений


    struct ConnectionsBetweenPoints { //структура для хранения соединенных точек
        int p1, p2; // параметры сединеных точек
        ConnectionsBetweenPoints(const int p1, const int p2) : p1(p1), p2(p2) {}
        int getConnectionP1() { return p1; }
        int getConnectionP2() { return p2; }
    };

    vector <ConnectionsBetweenPoints> connection;
public:
    inline void readConfig(string const configFilePath);
    Coordinate getCoordinatePoints(int pointNumber) { return points[pointNumber - 1]; }
    int getPointsCount() const {return pointsCount;}
    int getChipCount() const { return chipCount; }
    int getArrStartPoints(int i) { return arrStartPoints[i]; }
    int getArrWinnerPoints(int i) { return arrWinnerPoints[i]; }
    int getConnectCount() const { return connectCount; }
    ConnectionsBetweenPoints getConnectionsBetweenPoints(int connectCount) { return connection[connectCount]; }
};
 
    //СЧИТЫВАНИЕ ВХОДНЫХ ДАННЫХ
void Config::readConfig(string  const configFilePath) {
    ifstream cfg;
    cfg.open(configFilePath);

    if (!cfg.is_open()) {
        cout << "Configuration file not found!\n";
        return;
    }

    cfg >> chipCount;	
    cfg >> pointsCount;
    points.reserve(pointsCount);
    arrStartPoints.reserve(chipCount);
    arrWinnerPoints.reserve(chipCount);

    for (int i = 0; i < pointsCount; i++) {
        int x, y;
        string str;
        cfg >> str;

        if (!str.empty()) {
            int positionComma = str.find(',');
            x = atoi(str.c_str());
            str.erase(0, positionComma + 1);
            y = atoi(str.c_str());
            Coordinate coordTemp(x, y);
            points.push_back(coordTemp);
        }

    }

    for (int i = 0; i < chipCount; i++) {
	    string str;
        int temp;

        if (i < chipCount - 1) {
            getline(cfg, str, ',');
        }
        else
        {
            cfg >> str;
        }

        temp = atoi(str.c_str());
        arrStartPoints.push_back(temp);
    }

    for (int i = 0; i < chipCount; i++) {
        string str;
        int temp;
        if (i < chipCount - 1) {
            getline(cfg, str, ',');
        }
        else
        {
            cfg >> str;
        }
        temp = atoi(str.c_str());
        arrWinnerPoints.push_back(temp);
    }

    cfg >> connectCount;
    connection.reserve(connectCount);

    for (int i = 0; i < connectCount; i++) {
        int p1, p2;
        string str;
        cfg >> str;

        if (!str.empty()) {
            int positionComma = str.find(',');
            p1 = atoi(str.c_str());
            str.erase(0, positionComma + 1);
            p2 = atoi(str.c_str());
            ConnectionsBetweenPoints connPoint(p1, p2);
            connection.push_back(connPoint);
        }

    }
    cfg.close();
}
	



