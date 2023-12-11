#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class Config {
    struct Coordinate { //��������� ��� �������� ��������� �����
        int x, y;
        Coordinate() { x = y = 0; }
        Coordinate(const int x, const int y) : x(x), y(y) {}
    };

    int chipCount = 0;                 //���������� �����
    int pointsCount = 0;               //���������� �����
    vector <Coordinate> points;        //������ � ������������ �����
    vector <int> arrStartPoints;       //��������� ������� �����
    vector <int> arrWinnerPoints;      //�������� ������� �����
    int connectCount = 0;              //���������� ����������

    struct ConnectionsBetweenPoints { //��������� ��� �������� ����������� �����
        int p1, p2; // ��������� ��������� �����
        ConnectionsBetweenPoints(const int p1, const int p2) : p1(p1), p2(p2) {}
    };

    vector <ConnectionsBetweenPoints> connection;
public:
    inline void readConfig(string const &configFilePath);
};
 
    //���������� ������� ������
void Config::readConfig(string  const &configFilePath) {
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
	



