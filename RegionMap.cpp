#include "RegionMap.hpp"

#include "MapGenerator.hpp"

#include <list>
#include <iostream>
#include <cmath>

RegionMap::RegionMap()
{

}

RegionMap::RegionMap(unsigned int regions, unsigned int sharpness)
{
    _N_REGIONS = regions;
    _regions.resize(regions);
    _worldMap.resize(_WIDTH);
    for (auto& v : _worldMap) v.resize(_HEIGHT);

    _generateMap();
}

void RegionMap::_generateMap()
{
    for (unsigned int i=0; i<_N_REGIONS; ++i)
    {
        int x = rand()%_WIDTH;
        int y = rand()%_HEIGHT;
        _regions[i] = Region(x, y, i+1);
        _worldMap[x][y] = MapPoint(x, y, &_regions[i]);
    }

    generateMap(_regions, _worldMap, 80);

    _computeBorders();
}

void RegionMap::_computeBorders()
{
    for (auto& region : _regions)
    {
        region.computeBorderPoints(_worldMap);
    }
}

void RegionMap::_computeRoutes()
{

}


std::vector<Region*> RegionMap::getRoute(Region* region1, Region* region2)
{
    std::vector<Region*> path;

    if (!region2 || !region1)
        return path;

    for (auto& region : _regions)
    {
        region.marked = false;
        region.dist   = -1;
        region.last   = nullptr;
    }

    region1->dist = 0;
    Region* currentRegion = region1;

    while (!region2->marked)
    {
        for (auto& region : currentRegion->neighbors())
        {
            if (!region->marked)
            {
                double vx = currentRegion->capital()._x-region->capital()._x;
                double vy = currentRegion->capital()._y-region->capital()._y;

                double dist = currentRegion->dist + sqrt(vx*vx+vy*vy);

                if (dist < region->dist || region->dist == -1)
                {
                    region->dist = dist;
                    region->last = currentRegion;
                }
            }
        }

        currentRegion->marked = true;
        double minDist = -1;
        for (auto& region : _regions)
        {
            if (!region.marked && region.dist > -1)
            {
                if (minDist == -1 || region.dist < minDist)
                {
                    minDist = region.dist;
                    currentRegion = &region;
                }
            }
        }
    }

    Region* reversePathRegion = region2;

    while (reversePathRegion)
    {
        path.push_back(reversePathRegion);
        reversePathRegion = reversePathRegion->last;
    }

    return path;
}

Region* RegionMap::getRegionAt(unsigned int x, unsigned int y) const
{
    if (x > 0 && x < _WIDTH && y > 0 && y < _HEIGHT)
        return _worldMap[x][y]._owner;

    return nullptr;
}

void RegionMap::render(sf::RenderTarget* target) const
{
    sf::VertexArray routes(sf::Lines, 0);
    for (auto& region : _regions)
    {
        for (auto& neighbour : region.neighbors())
        {
            unsigned int x = neighbour->capital()._x;
            unsigned int y = neighbour->capital()._y;

            sf::Vertex routePoint;
            routePoint.position = sf::Vector2f(x, y);
            routePoint.color    = sf::Color::Black;

            routes.append(routePoint);

            routePoint.position = sf::Vector2f(region.capital()._x, region.capital()._y);
            routePoint.color    = sf::Color::Black;

            routes.append(routePoint);
        }
    }

    sf::VertexArray map(sf::Points, 0);
    for (unsigned int x(0); x<_WIDTH; ++x)
    {
        for (unsigned int y(0); y<_HEIGHT; ++y)
        {
            int owner   = _worldMap[x][y].id();
            bool isNull = owner == 0 || !(_worldMap[x][y]._onBorder);

            if (!isNull)
            {
                sf::Vertex vert;
                vert.position = sf::Vector2f(x, y);
                vert.color    = sf::Color(0, 0, 0);
                map.append(vert);
            }
        }
    }

    target->draw(map);
    //target->draw(routes);

    for (auto& region : _regions)
    {
        sf::CircleShape capital(4);
        capital.setOrigin(4, 4);
        capital.setFillColor(sf::Color::Red);
        capital.setPosition(region.capital()._x, region.capital()._y);
        target->draw(capital);
    }
}
