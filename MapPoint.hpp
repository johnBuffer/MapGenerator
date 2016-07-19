#ifndef MAPPOINT_HPP_INCLUDED
#define MAPPOINT_HPP_INCLUDED

class Region;

struct MapPoint
{
    MapPoint();
    MapPoint(unsigned int x, unsigned int y, Region* owner);
    void computeAngle();

    static bool compAngle(const MapPoint& mp1, const MapPoint& mp2);

    unsigned int id() const;

    int    _x;
    int    _y;
    double _capitalAngle;
    unsigned int _type;

    Region* _owner;
    bool    _onBorder;
};

#endif // MAPPOINT_HPP_INCLUDED
