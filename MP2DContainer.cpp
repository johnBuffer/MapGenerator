#include "MP2DContainer.hpp"
#include "utils.hpp"

MP2DContainer::MP2DContainer(int width, int height) :
    _WIDTH(width),
    _HEIGHT(height)
{
    _2dMap.resize(_WIDTH);
    for (auto& v : _2dMap) v.resize(_HEIGHT);

    for (int x(0); x<_WIDTH; ++x)
    {
        for (int y(0); y<_HEIGHT; ++y)
        {
            _2dMap[x][y] = MapPoint(x, y, nullptr);
        }
    }
}

MapPoint& MP2DContainer::operator()(int x, int y)
{
    int dataX = mod(x, _WIDTH);
    int dataY = y < 0 ? 0 : (y >= _HEIGHT ? _HEIGHT-1 : y);

    return _2dMap[dataX][dataY];
}
