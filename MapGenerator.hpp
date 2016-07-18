#ifndef MAPGENERATOR_HPP_INCLUDED
#define MAPGENERATOR_HPP_INCLUDED

#include "utils.hpp"
#include "MapPoint.hpp"
#include "Region.hpp"

IterationResult stagger(std::vector<Region>& regions, std::vector<std::vector<MapPoint>>& pMap, int sharpness);
void generateMap(std::vector<Region>& regions, std::vector<std::vector<MapPoint>>& pMap, int sharpness);

#endif // MAPGENERATOR_HPP_INCLUDED
