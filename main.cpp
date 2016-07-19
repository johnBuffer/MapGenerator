#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <utility>

#include "RegionMap.hpp"

int main()
{
    srand(time(NULL));

    int WIDTH(750), HEIGHT(750);
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "RTest");
    window.setFramerateLimit(60);

    RegionMap world(100, 80);

    Region *region1(nullptr), *region2(nullptr);
    std::vector<Region*> path;

    double offsetX = 0;
    sf::Vector2i clicPos;

    sf::Transform slide, loopSlide;

    while (window.isOpen())
    {
        sf::Vector2i localPosition = sf::Mouse::getPosition(window);

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed)
            {
                clicPos = localPosition;
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            region1 = world.getRegionAt(localPosition.x, localPosition.y);

            int move = localPosition.x-clicPos.x;
            offsetX += move;
            slide.translate(sf::Vector2f(move, 0));

            if (offsetX > 0)
                loopSlide.translate(sf::Vector2f(move-WIDTH, 0));
            else
                loopSlide.translate(sf::Vector2f(move+WIDTH, 0));

            clicPos = localPosition;
        }

        Region* newRegion2 = world.getRegionAt(localPosition.x, localPosition.y);
        if (newRegion2 != region2 && newRegion2)
        {
            region2 = newRegion2;
            path = world.getRoute(region1, region2);
        }

        sf::VertexArray routes(sf::Lines, 0);
        if (path.size())
        {
            for (unsigned int i(0); i<path.size()-1; ++i)
            {
                unsigned int x = path[i]->capital()._x;
                unsigned int y = path[i]->capital()._y;

                sf::Vertex routePoint;
                routePoint.position = sf::Vector2f(x, y);
                routePoint.color    = sf::Color::Red;

                routes.append(routePoint);

                routePoint.position = sf::Vector2f(path[i+1]->capital()._x, path[i+1]->capital()._y);
                routePoint.color    = sf::Color::Red;

                routes.append(routePoint);
            }
        }


        window.clear(sf::Color::White);

        world.render(&window, slide);

        window.draw(routes, slide);
        window.draw(routes, loopSlide);

        window.display();
    }

    return 0;
}
