#include "connexity.hpp"

IterationResult connexity(Province2DMap& pMap, int sharpness, Mode mode)
{
    int WIDTH = pMap.size();
    int HEIGHT = pMap[0].size();

    int MAXX = WIDTH-1;
    int MAXY = HEIGHT-1;

    IterationResult result;
    for (int x=1; x<MAXX; ++x)
    {
        for (int y=1; y<MAXY-1; ++y)
        {
            int currentP = pMap[x][y].id;
            if (!currentP)
            {
                if (pMap[x+1][y].id && isOK(sharpness))
                {
                    result.changes++;
                    result.addRP(x, y, pMap[x+1][y].id);
                }

                else if (pMap[x-1][y].id && isOK(sharpness))
                {
                    result.changes++;
                    result.addRP(x, y, pMap[x-1][y].id);
                }

                else if (pMap[x][y+1].id && isOK(sharpness))
                {
                   result.changes++;
                   result.addRP(x, y, pMap[x][y+1].id);
                }

                else if (pMap[x][y-1].id && isOK(sharpness))
                {
                    result.changes++;
                    result.addRP(x, y, pMap[x][y-1].id);
                }
                else if (mode == Mode::EIGHT)
                {
                    if (pMap[x+1][y+1].id && isOK(sharpness))
                    {
                        result.changes++;
                        result.addRP(x, y, pMap[x+1][y+1].id);
                    }

                    else if (pMap[x-1][y+1].id && isOK(sharpness))
                    {
                        result.changes++;
                        result.addRP(x, y, pMap[x-1][y+1].id);
                    }

                    else if (pMap[(x-1)%MAXX][y-1].id && isOK(sharpness))
                    {
                       result.changes++;
                       result.addRP(x, y, pMap[x-1][y-1].id);
                    }

                    else if (pMap[(x+1)%MAXX][y-1].id && isOK(sharpness))
                    {
                        result.changes++;
                        result.addRP(x, y, pMap[x+1][y-1].id);
                    }
                }
            }
        }
    }

    return result;
}
