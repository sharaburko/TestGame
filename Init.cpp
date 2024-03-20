#include "Init.h"

void Init::setChip(Config& config)
{
    chips.reserve(config.getChipCount());

    for (int i = 0; i < config.getChipCount(); i++) {
        int numberPositionShape = config.getArrStartPoints(i);
        chips.emplace_back(config.getArrStartPoints(i), config.getArrWinnerPoints(i), arrColor[i], config.getCoordinatePoints(numberPositionShape).getCoordinateX(), config.getCoordinatePoints(numberPositionShape).getCoordinateY(), radiusChip);
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
    roads.reserve(connectPoints.size());
	
    for (int i = 0; i < connectPoints.size(); i++) {

        Road tempRoad;

        int p1 = connectPoints[i].front() - 1;
        int p2 = connectPoints[i].back() - 1;
        float p1X = getPositionPoints()[p1].getCoordinateX();
        float p1Y = getPositionPoints()[p1].getCoordinateY();
        float p2X = getPositionPoints()[p2].getCoordinateX();
        float p2Y = getPositionPoints()[p2].getCoordinateY();


        if (p1X == p2X) {
            sf::Vector2f size(Road::getWidthShape(), p2Y + getSizePointsY() - p1Y -
                (getSizePointsY() - Road::getWidthShape()));
            sf::Vector2f position(p1X + (2 * getRadiusChip() - Road::getWidthShape()) / 2,
                p1Y + (2 * getRadiusChip() - Road::getWidthShape()) / 2);
            tempRoad.setRoad().setSize(size);
            tempRoad.setRoad().setPosition(position);
        }
        else {
            sf::Vector2f size(p2X + getSizePointsX() - p1X - (getSizePointsX() -
                Road::getWidthShape()), Road::getWidthShape());
            tempRoad.setRoad().setSize(size);
            sf::Vector2f position(p1X + (2 * getRadiusChip() - Road::getWidthShape()) / 2,
                p1Y + (2 * getRadiusChip() - Road::getWidthShape()) / 2);
            tempRoad.setRoad().setPosition(position);
        }
    	
        roads.push_back(tempRoad);
    }
}

const sf::Vector2f& Init::getPositionPoint(int numberPosition)
{
    for (auto it = positionPoints.begin(); it != positionPoints.end(); it++)     {
        
        if (it->getPosition() == numberPosition) {
            return it->getCoordinate();
        }
    }
}


