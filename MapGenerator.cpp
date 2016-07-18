#include "MapGenerator.hpp"

IterationResult stagger(std::vector<Region>& regions, std::vector<std::vector<MapPoint>>& pMap, int sharpness)
{
    IterationResult result;

    unsigned int WIDTH = pMap.size();
    unsigned int HEIGHT = pMap[0].size();

    unsigned int MAXX = WIDTH-1;
    unsigned int MAXY = HEIGHT-1;

    for (auto& region : regions)
    {
        for (auto& point : region.points())
        {
            unsigned int x = point._x;
            unsigned int y = point._y;

            if (x > 0 && x < MAXX && y > 0 && y < MAXY)
            {
                if (!pMap[x+1][y].id() && isOK(sharpness))
                {
                    result.changes++;
                    result.addRP(x+1, y, &region);
                    pMap[x+1][y]._owner = &region;
                }

                else if (!pMap[x-1][y].id() && isOK(sharpness))
                {
                    result.changes++;
                    result.addRP(x-1, y, &region);
                    pMap[x-1][y]._owner = &region;
                }

                else if (!pMap[x][y+1].id() && isOK(sharpness))
                {
                   result.changes++;
                   result.addRP(x, y+1, &region);
                   pMap[x][y+1]._owner = &region;
                }

                else if (!pMap[x][y-1].id() && isOK(sharpness))
                {
                    result.changes++;
                    result.addRP(x, y-1, &region);
                    pMap[x][y-1]._owner = &region;
                }
            }
        }
    }

    return result;
}

void generateMap(std::vector<Region>& regions, std::vector<std::vector<MapPoint>>& pMap, int sharpness)
{
    IterationResult result;
    do
    {
        result = stagger(regions, pMap, sharpness);

        for (auto& rp : result.newRegionPoints)
        {
            rp.region->addPoint(rp.x, rp.y);
        }
    }
    while(result.changes);
}
