#ifndef REGION_HPP_INCLUDED
#define REGION_HPP_INCLUDED

#include "MapPoint.hpp"
#include <vector>
#include <list>

class Region
{
public:
    Region(unsigned int id=0);
    Region(unsigned int x, unsigned int y, unsigned int id);

    unsigned int                 id()        const {return _id;}
    const std::vector<MapPoint>& points()    const {return _points;}
    const std::vector<Region*>&  neighbors() const {return _neighbors;}
    const MapPoint               capital()   const {return _points[0];}

    void addPoint(unsigned int x, unsigned int y);
    void addNeighbour(Region*);
    void computeBorderPoints(std::vector<std::vector<MapPoint>>& pMap);

private:
    unsigned int _id;

    std::vector<MapPoint> _points;
    std::vector<Region*>  _neighbors;
};

#endif // REGION_HPP_INCLUDED
