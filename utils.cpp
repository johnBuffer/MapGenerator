#include "utils.hpp"

bool isOK(int percent)
{
    return rand()%100 < percent;
}

int mod(int a, int b)
{
    return a < 0 ? a+b : a%b;
}

RegionPoint::RegionPoint(int arg_x, int arg_y, Region* arg_region) : x(arg_x), y(arg_y), region(arg_region) {}

IterationResult::IterationResult() : changes(0) {}
void IterationResult::addRP(int x, int y, Region* region) {newRegionPoints.push_back(RegionPoint(x, y, region));}
