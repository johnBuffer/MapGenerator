#ifndef MAPPOINT_HPP_INCLUDED
#define MAPPOINT_HPP_INCLUDED

class Region;

struct MapPoint
{
    MapPoint();
    MapPoint(unsigned int x, unsigned int y, Region* owner);

    unsigned int id() const;

    int _x;
    int _y;
    unsigned int _type;

    Region* _owner;
    bool    _onBorder;
};

#endif // MAPPOINT_HPP_INCLUDED
