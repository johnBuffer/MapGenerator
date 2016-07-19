#ifndef UTILS_HPP_INCLUDED
#define UTILS_HPP_INCLUDED

#include <vector>
#include <cstdlib>
#include "Region.hpp"

bool isOK(int percent);
int mod(int a, int b);

struct RegionPoint
{
    unsigned int x, y;
    Region* region;

    RegionPoint(int arg_x, int arg_y, Region* arg_region);
};

struct IterationResult
{
    int changes;
    std::vector<RegionPoint> newRegionPoints;

    IterationResult();

    void addRP(int x, int y, Region* region);
};

#endif // UTILS_HPP_INCLUDED
