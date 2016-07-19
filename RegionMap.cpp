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

    for (unsigned int x(0); x<_WIDTH; ++x)
    {
        for (unsigned int y(0); y<_HEIGHT; ++y)
        {
            _worldMap[x][y] = MapPoint(x, y, nullptr);
        }
    }

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
    sf::Clock clock;
    std::cout << "Starting map generation... ";
    generateMap(_regions, _worldMap, 80);
    std::cout << clock.restart().asMilliseconds() << "ms" << std::endl;

    std::cout << "Starting borders detection..." << std::endl;
    _computeBorders();
    std::cout << "Starting route construction..." << std::endl;
    _computeRoutes();
    std::cout << "DONE." << std::endl;
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
    for (auto& region1 : _regions)
    {
        for (auto& region2 : region1.neighbors())
        {
            _abstractMap.addConnection(&region1, region2);
        }
    }
}

std::vector<Region*> RegionMap::getRoute(Region* region1, Region* region2)
{
    return _abstractMap.getPath(region1, region2);
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

                srand(owner);

                //double color = rand()%255;
                //vert.color = sf::Color(color, rand()%255, rand()%255);
                vert.color = sf::Color::Black;
                map.append(vert);
            }
        }
    }

    target->draw(map);

    //target->draw(routes);

    for (auto& region : _regions)
    {
        //region.render(target);

        sf::CircleShape capital(4);
        capital.setOrigin(4, 4);
        capital.setFillColor(sf::Color::Red);
        capital.setPosition(region.capital()._x, region.capital()._y);
        target->draw(capital);
    }
}
