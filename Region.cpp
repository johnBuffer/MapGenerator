#include "Region.hpp"
#include <iostream>
#include <algorithm>

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
                _borderPoints.push_back(point);
            }
            else if (pMap[x-1][y].id() != _id)
            {
                if (pMap[x-1][y].id()) addNeighbour(pMap[x-1][y]._owner);
                _borderPoints.push_back(point);
            }
            else if (pMap[x][y+1].id() != _id)
            {
               if (pMap[x][y+1].id()) addNeighbour(pMap[x][y+1]._owner);
               _borderPoints.push_back(point);
            }
            else if (pMap[x][y-1].id() != _id)
            {
                if (pMap[x][y-1].id()) addNeighbour(pMap[x][y-1]._owner);
                _borderPoints.push_back(point);
            }
            else
            {
                pMap[x][y]._onBorder = false;
            }
        }
    }

    for (auto& point : _borderPoints)
    {
        //pMap[point._x][point._y].computeAngle();
        point.computeAngle();
    }

    sort(_borderPoints.begin(), _borderPoints.end(), MapPoint::compAngle);
}

void Region::render(sf::RenderTarget* target) const
{
    int nBorderPoints = _borderPoints.size();
    sf::VertexArray border(sf::Lines, 2*nBorderPoints);

    for (int i(0); i<nBorderPoints-1; ++i)
    {
        double x  = _borderPoints[i  ]._x;
        double y  = _borderPoints[i  ]._y;
        double x1 = _borderPoints[i+1]._x;
        double y1 = _borderPoints[i+1]._y;

        border[2*i  ].position = sf::Vector2f(x, y);
        border[2*i  ].color = sf::Color::Black;

        border[2*i+1].position = sf::Vector2f(x1, y1);
        border[2*i+1].color = sf::Color::Black;
    }

    target->draw(border);
}

