#include "Region.hpp"
#include <iostream>

Region::Region(unsigned int id) :
    _id(id)
{

}

Region::Region(unsigned int x, unsigned int y, unsigned int id) :
    _id(id)
{
    addPoint(x, y);
}

void Region::addPoint(unsigned int x, unsigned int y)
{
    _points.push_back(MapPoint(x, y, this));
}

void Region::addNeighbour(Region* newNeighbour)
{
    for (auto& region : _neighbors)
    {
        if (region == newNeighbour)
            return;
    }

    _neighbors.push_back(newNeighbour);
}

void Region::computeBorderPoints(std::vector<std::vector<MapPoint>>& pMap)
{
    unsigned int WIDTH = pMap.size();
    unsigned int HEIGHT = pMap[0].size();

    unsigned int MAXX = WIDTH-1;
    unsigned int MAXY = HEIGHT-1;

    for (auto& point : _points)
    {
        unsigned int x = point._x;
        unsigned int y = point._y;

        if (x > 0 && x < MAXX && y > 0 && y < MAXY)
        {
            if (pMap[x+1][y].id() != _id)
            {
                if (pMap[x+1][y].id()) addNeighbour(pMap[x+1][y]._owner);
            }
            else if (pMap[x-1][y].id() != _id)
            {
                if (pMap[x-1][y].id()) addNeighbour(pMap[x-1][y]._owner);
            }
            else if (pMap[x][y+1].id() != _id)
            {
               if (pMap[x][y+1].id()) addNeighbour(pMap[x][y+1]._owner);
            }
            else if (pMap[x][y-1].id() != _id)
            {
                if (pMap[x][y-1].id()) addNeighbour(pMap[x][y-1]._owner);
            }
            else
            {
                pMap[x][y]._onBorder = false;
            }
        }
    }
}
