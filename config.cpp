#include "config.h"

void Config::readConfig(std::string  const configFilePath) {
    std::ifstream cfg;
    cfg.open(configFilePath);
    points.reserve(pointsCount);
    arrStartPoints.reserve(chipCount);
    arrWinnerPoints.reserve(chipCount);
    connection.reserve(connectCount);

    if (!cfg.is_open()) {
        std::cout << "Configuration file not found!\n";
        return;
    }

    cfg >> chipCount;
    cfg >> pointsCount;

    for (int i = 0; i < pointsCount; i++) {
        float x, y;
        std::string str;
        cfg >> str;

        if (!str.empty()) {
            int positionComma = str.find(',');
            x = (float)atoi(str.c_str());
            str.erase(0, positionComma + 1);
            y = (float)atoi(str.c_str());
            Coordinate coordinateTemp(x, y);
            points.push_back(coordinateTemp);
        }

    }

    for (int i = 0; i < chipCount; i++) {
        std::string str;
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
        std::string str;
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

    for (int i = 0; i < connectCount; i++) {
        int p1, p2;
        std::string str;
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