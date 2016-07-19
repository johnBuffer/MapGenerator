#include "MapPoint.hpp"
#include "Region.hpp"

#include <cmath>
#include <iostream>

MapPoint::MapPoint() :
    _x(0),
    _y(0),
    _owner(nullptr),
    _onBorder(true)
{

}

MapPoint::MapPoint(unsigned int x, unsigned int y, Region* owner) :
    _x(x),
    _y(y),
    _owner(owner),
    _onBorder(true)
{

}

bool MapPoint::compAngle(const MapPoint& mp1, const MapPoint& mp2)
{
    return mp1._capitalAngle > mp2._capitalAngle;
}

unsigned int MapPoint::id() const
{
    if (_owner)
        return _owner->id();

    return 0;
}

void MapPoint::computeAngle()
{
    if (!_owner)
        return;

    double xCapital = _owner->capital()._x;
    double yCapital = _owner->capital()._y;

    double vx = _x-xCapital;
    double vy = _y-yCapital;

    double dist = sqrt(vx*vx + vy*vy);

    _capitalAngle = acos(vx/dist);
    if (vy < 0)
        _capitalAngle *= -1;

    //std::cout << _owner->id() << std::endl;
}

