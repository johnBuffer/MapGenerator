#ifndef UTILS_HPP_INCLUDED
#define UTILS_HPP_INCLUDED

#include <vector>
#include <cstdlib>
#include "Region.hpp"

bool isOK(int percent);

struct DijkstraPoint
{
    const Region* region;
    double dist;
    bool   marked;

    DijkstraPoint() : region(nullptr) {}
    DijkstraPoint(const Region* r, double arg_dist=-1) : region(r), dist(arg_dist), marked(false) {}
};

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
