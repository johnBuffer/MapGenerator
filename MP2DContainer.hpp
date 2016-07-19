#ifndef MP2DCONTAINER_HPP_INCLUDED
#define MP2DCONTAINER_HPP_INCLUDED

#include <vector>

#include "MapPoint.hpp"


class MP2DContainer
{
public:
    MP2DContainer(int width, int height);

    MapPoint& operator()(int x, int y);

private:
    int _WIDTH, _HEIGHT;
    std::vector<std::vector<MapPoint>> _2dMap;
};

#endif // MP2DCONTAINER_HPP_INCLUDED
