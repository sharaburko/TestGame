#include "Init.h"

void Init::setChip(Config& config)
{
    chip.reserve(config.getChipCount());

    for (int i = 0; i < config.getChipCount(); i++) {
        int numberPositionShape = config.getArrStartPoints(i);
        chip.emplace_back(config.getArrStartPoints(i), config.getArrWinnerPoints(i), arrColor[i], config.getCoordinatePoints(numberPositionShape).getCoordinateX(), config.getCoordinatePoints(numberPositionShape).getCoordinateY(), radiusChip);
    }
}

void Init::setSquare(Config& config)
{
    square.reserve(config.getChipCount());

    for (int i = 0; i < config.getChipCount(); i++) {
        int NumberPositionPoint = config.getArrWinnerPoints(i);
        square.emplace_back(NumberPositionPoint, config.getCoordinatePoints(NumberPositionPoint).getCoordinateX(), config.getCoordinatePoints(NumberPositionPoint).getCoordinateY(), arrColor[i], radiusChip, sizePoints);
    }
}

void Init::setPositionPoints(Config& config)
{
    positionPoints.reserve(config.getPointsCount());

    for (int i = 1; i <= config.getPointsCount(); i++) {
        PositionPoints tempPositionPoints(i, config.getCoordinatePoints(i).getCoordinateX(), config.getCoordinatePoints(i).getCoordinateY());
        positionPoints.push_back(tempPositionPoints);
    }
}

void Init::setConnectPoints(Config & config)
{
    connectPoints.reserve(config.getConnectCount());
    for (int i = 0; i < config.getConnectCount(); i++) {
        config.getConnectionsBetweenPoints(i);
        std::vector <int> tempConnect;
        tempConnect.push_back(config.getConnectionsBetweenPoints(i).getConnectionP1());
        tempConnect.push_back(config.getConnectionsBetweenPoints(i).getConnectionP2());
        connectPoints.push_back(tempConnect);
        tempConnect.clear();
    }
}

void Init::setRoads()
{
    for (int i = 0; i < connectPoints.size(); i++) {

        //int p1 = getConnectPoints()[i][0] - 1;
        //int p2 = getConnectPoints()[i][1] - 1;
        //float p1X = getPositionPoints()[p1].getCoordinateX();
        //float p1Y = getPositionPoints()[p1].getCoordinateY();
        //float p2X = getPositionPoints()[p2].getCoordinateX();
        //float p2Y = getPositionPoints()[p2].getCoordinateY();

        int p1 = *connectPoints[i].begin();
        int p2 = connectPoints[i].back();
        float p1X = getPositionPoints()[p1].getCoordinateX();
        float p1Y = getPositionPoints()[p1].getCoordinateY();
        float p2X = getPositionPoints()[p2].getCoordinateX();
        float p2Y = getPositionPoints()[p2].getCoordinateY();


        if (p1X == p2X) {
            sf::Vector2f size(roads[i].getWidthRoad(), p2Y + getSizePointsY() - p1Y -
                (getSizePointsY() - roads[i].getWidthRoad()));
            sf::Vector2f position(p1X + (2 * getRadiusChip() - roads[i].getWidthRoad()) / 2,
                p1Y + (2 * getRadiusChip() - roads[i].getWidthRoad()) / 2);
            roads[i].setRoad().setSize(size);
            roads[i].setRoad().setPosition(position);
        }
        else {
            sf::Vector2f size(p2X + getSizePointsX() - p1X - (getSizePointsX() -
                roads[i].getWidthRoad()), roads[i].getWidthRoad());
            roads[i].setRoad().setSize(size);
            sf::Vector2f position(p1X + (2 * getRadiusChip() - roads[i].getWidthRoad()) / 2,
                p1Y + (2 * getRadiusChip() - roads[i].getWidthRoad()) / 2);
            roads[i].setRoad().setPosition(position);
        }
    }
}


