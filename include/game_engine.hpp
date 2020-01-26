#pragma once

#include "game_world.hpp"
#include "game_renderer.hpp"
#include "resources_manager.hpp"
#include "module.hpp"
#include <SFML/Graphics.hpp>
#include <list>


struct GameEngine
{
	void initialize();

	void update(float dt);

	void execute_modules(float dt);

	void render_in(sf::RenderTarget& target) const;

	void clear();

	static GameEngine& getInstance();

	GameWorld world;
	GameRenderer renderer;
	ResourcesManager resources;
	std::list<Module::ptr> modules;

	static GameEngine* global_instance;
};