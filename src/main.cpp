#include <SFML/Graphics.hpp>
#include "turret.hpp"


int32_t main()
{
    const uint32_t win_width(800);
    const uint32_t win_height(600);

    sf::RenderWindow window(sf::VideoMode(win_width, win_height), "ZTyper2");

    Turret turret(win_width / 2U, win_height - 75, 0.0f);


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        
        turret.draw(window);

        window.display();
    }

    return 0;
}