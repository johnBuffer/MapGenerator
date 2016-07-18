/*for (int x=0; x<WIDTH; ++x)
    {
        for (int y=0; y<WIDTH; ++y)
        {
            double minDist = -1;
            int minId = 0;
            for (int i=0; i<provincesCount; ++i)
            {
                double vx = x-provincesList[i].first;
                double vy = y-provincesList[i].second;

                double dist = vx*vx+vy*vy;

                if (dist < minDist || minDist == -1)
                {
                    minId = i+2;
                    minDist = dist;
                }
            }

            provinces[x][y] = minId;
        }
    }*/
