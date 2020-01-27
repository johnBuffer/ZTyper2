#include <SFML/Graphics.hpp>
#include "turret.hpp"
#include "zombie.hpp"
#include "game_engine.hpp"
#include "bullet.hpp"
#include "explosion.hpp"
#include "letter.hpp"
#include "utils.hpp"
#include <event_manager.hpp>

#include <iostream>


int32_t main()
{
    const uint32_t win_width(1600);
    const uint32_t win_height(900);

    sf::RenderWindow window(sf::VideoMode(win_width, win_height), "ZTyper2");
    window.setFramerateLimit(60);

    // Various initializations
    GameEngine::initialize(win_width, win_height);
    Zombie::initialize();
    Bullet::initialize();
    Turret::initialize();
    Explosion::initialize();

    Turret::ptr turret = Turret::create(win_width * 0.5f, win_height - 75.0f, -3.1415926f * 0.5f);

    float time = 0.0f;

    Zombie::ptr zombie_1 = Zombie::create(Vec2(0.0f, 0.0f), "alol", turret);
    Zombie::ptr zombie_2 = Zombie::create(Vec2(800.0f, 0.0f), "blol", turret);
    Zombie::ptr zombie_3 = Zombie::create(Vec2(400.0f, -50.0f), "clol", turret);

    const std::vector<std::string> words = { "the", "be", "of", "and", "a", "to", "in", "he", "have", "it", "that", "for", "they", "I", "with", "as", "not", "on", "she", "at", "by", "this", "we", "you", "do", "but", "from", "or", "which", "one", "would", "all", "will", "there", "say", "who", "make", "when", "can", "more", "if", "no", "man", "out", "other", "so", "what", "time", "up", "go", "about", "than", "into", "could", "state", "only", "new", "year", "some", "take", "come", "these", "know", "see", "use", "get", "like", "then", "first", "any", "work", "now", "may", "such", "give", "over", "think", "most", "even", "find", "day", "also", "after", "way", "many", "must", "look", "before", "great", "back", "through", "long", "where", "much", "should", "well", "people", "down", "own", "just", "because", "good", "each", "those", "feel", "seem", "how", "high", "too", "place", "little", "world", "very", "still", "nation", "hand", "old", "life", "tell", "write", "become", "here", "show", "house", "both", "between", "need", "mean", "call", "develop", "under", "last", "right", "move", "thing", "general", "school", "never", "same", "another", "begin", "while", "number", "part", "turn", "real", "leave", "might", "want", "point", "form", "off", "child", "few", "small", "since", "against", "ask", "late", "home", "interest", "large", "person", "end", "open", "public", "follow", "during", "present", "without", "again", "hold", "govern", "around", "possible", "head", "consider", "word", "program", "problem", "however", "lead", "system", "set", "order", "eye", "plan", "run", "keep", "face", "fact", "group", "play", "stand", "increase", "early", "course", "change", "help", "line" };

    GameEngine& engine = GameEngine::getInstance();
    engine.world.addObject(turret);
    engine.world.addObject(zombie_1);
    engine.world.addObject(zombie_2);
    engine.world.addObject(zombie_3);

    // Register events callbacks
    sfev::EventManager event_manager(window);
    event_manager.addEventCallback(sf::Event::Closed, [&](sfev::CstEv) {window.close(); });
    event_manager.addKeyReleasedCallback(sf::Keyboard::Space, [&](sfev::CstEv) {turret->resetTarget(); });
    event_manager.addEventCallback(sf::Event::TextEntered, [&](sfev::CstEv ev) {turret->charTyped(ev.text.unicode); });

    sf::Clock frame_clock;
    float last_zombie = 10.0f;
    while (window.isOpen()) {
        const sf::Vector2i mouse_position = sf::Mouse::getPosition(window);

        event_manager.processEvents();

        if (last_zombie > 1.0f) {
            const float x_z = static_cast<const float>(rand() % win_width);
            const float y_z = static_cast<const float>(-50 - rand() % 1000);
            engine.world.addObject(Zombie::create(Vec2(x_z, y_z), getRandomElemFromVector(words), turret));
            last_zombie = 0.0f;
        }

        // std::cout << Letter::pool.size() << std::endl;

        const float dt = frame_clock.restart().asSeconds();
        last_zombie += dt;
        time += dt;
        engine.update(dt);

        window.clear();
        
        engine.render_in(window);

        window.display();

        engine.clear();
    }

    return 0;
}