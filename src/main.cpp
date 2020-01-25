#include <SFML/Graphics.hpp>
#include "turret.hpp"
#include "zombie.hpp"
#include "game_engine.hpp"
#include "bullet.hpp"
#include <event_manager.hpp>

#include <iostream>


int32_t main()
{
    const uint32_t win_width(1600);
    const uint32_t win_height(900);

    sf::RenderWindow window(sf::VideoMode(win_width, win_height), "ZTyper2");
    window.setFramerateLimit(60);

    // Various initializations
    Zombie::initialize();
    Bullet::initialize();
    Turret::initialize();

    Turret::ptr turret = Turret::create(win_width * 0.5f, win_height - 75.0f, -3.1415926f * 0.5f);

    float time = 0.0f;

    Zombie::ptr zombie_1 = Zombie::create(Vec2(0.0f, 0.0f), "alol", turret);
    Zombie::ptr zombie_2 = Zombie::create(Vec2(800.0f, 0.0f), "blol", turret);
    Zombie::ptr zombie_3 = Zombie::create(Vec2(400.0f, -50.0f), "clol", turret);

    GameEngine& engine = *GameEngine::getInstance();
    engine.world.addObject(turret);
    engine.world.addObject(zombie_1);
    engine.world.addObject(zombie_2);
    engine.world.addObject(zombie_3);

    // Register events callbacks
    sfev::EventManager event_manager(window);
    event_manager.addEventCallback(sf::Event::Closed, [&](sfev::CstEv) {window.close(); });
    event_manager.addEventCallback(sf::Event::TextEntered, [&](sfev::CstEv ev) {turret->charTyped(ev.text.unicode); });
    //event_manager.addKeyPressedCallback(sf::Keyboard::BackSpace, [&](sfev::CstEv ev) {challenge.removeChar(); });

    sf::Clock frame_clock;
    while (window.isOpen()) {
        const sf::Vector2i mouse_position = sf::Mouse::getPosition(window);

        event_manager.processEvents();

        // std::cout << Bullet::pool.size() << std::endl;

        const float dt = frame_clock.restart().asSeconds();
        time += dt;
        engine.update(dt);

        window.clear();
        
        engine.render_in(window);

        window.display();
    }

    return 0;
}