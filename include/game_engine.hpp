#pragma once

#include "game_world.hpp"
#include "game_renderer.hpp"
#include "resources_manager.hpp"
#include "module.hpp"
#include <SFML/Graphics.hpp>
#include <list>


struct GameEngine
{
	static void initialize(uint32_t win_width, uint32_t win_height);

	GameEngine(uint32_t win_width, uint32_t win_height);

	void update(float forced_dt = 0.0f);
	void execute_modules(float dt);
	void render_in(sf::RenderTarget& target) const;

	float getTime() const;

	static GameEngine& getInstance();


	GameWorld world;
	mutable GameRenderer renderer;
	ResourcesManager resources;
	std::list<Module::ptr> modules;

	static GameEngine* global_instance;

private:
	sf::Clock frame_time;
	float global_time;

	void updateObjects(float dt);
	void cleanDeadObjects();
};