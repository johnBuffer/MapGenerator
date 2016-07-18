#include "MapPoint.hpp"

#include "Region.hpp"

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

unsigned int MapPoint::id() const
{
    if (_owner)
        return _owner->id();

    return 0;
}
