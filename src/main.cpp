#include <SFML/Graphics.hpp>
#include "turret.hpp"


int32_t main()
{
    const uint32_t win_width(800);
    const uint32_t win_height(600);

    sf::RenderWindow window(sf::VideoMode(win_width, win_height), "ZTyper2");
    window.setFramerateLimit(60);

    Turret turret(win_width / 2U, win_height - 75, 0.0f);

    float time = 0.0f;

    while (window.isOpen()) {
        const sf::Vector2i mouse_position = sf::Mouse::getPosition(window);

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        time += 0.016f;

        turret.aim_at(Vec2(mouse_position.x, mouse_position.y));

        window.clear();
        
        turret.draw(window);

        window.display();
    }

    return 0;
}