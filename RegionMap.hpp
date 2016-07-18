#ifndef REGIONMAP_HPP_INCLUDED
#define REGIONMAP_HPP_INCLUDED

#include <vector>
#include <SFML/Graphics.hpp>

#include "Region.hpp"
#include "MapPoint.hpp"
#include "utils.hpp"

class RegionMap
{
public:
    RegionMap();
    RegionMap(unsigned int regions, unsigned int sharpness);

    void render(sf::RenderTarget* target) const;

    std::vector<Region*> getRoute    (Region* region1, Region* region2);
    Region*              getRegionAt (unsigned int x, unsigned int y) const;

private:
    unsigned int _WIDTH  = 750;
    unsigned int _HEIGHT = 750;
    unsigned int _N_REGIONS;

    std::vector<Region> _regions;
    std::vector<std::vector<MapPoint>> _worldMap;

    void _generateMap();
    void _computeBorders();
    void _computeRoutes();
};

#endif // REGIONMAP_HPP_INCLUDED
