#pragma once

#include "game_world.hpp"
#include "module.hpp"
#include <SFML/Graphics.hpp>
#include <list>


struct GameEngine
{
	void update(float dt);

	void execute_modules(float dt);

	void render_in(sf::RenderTarget& target) const;

	static GameEngine* getInstance();

	GameWorld world;
	std::list<Module::ptr> modules;

	static GameEngine* global_instance;
};