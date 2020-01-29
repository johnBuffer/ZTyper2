#pragma once

#include "game_world.hpp"
#include "game_renderer.hpp"
#include "resources_manager.hpp"
#include "module.hpp"
#include <SFML/Graphics.hpp>
#include <list>
#include <functional>


struct GameEngine
{
	static GameEngine& getInstance();
	static void initialize(uint32_t win_width, uint32_t win_height);
	static void exit();

	template<typename T>
	void registerObjectClass();
	void update(float forced_dt = 0.0f);
	void execute_modules(float dt);
	void render_in(sf::RenderTarget& target) const;
	void clean();
	float getTime() const;

	GameWorld world;
	mutable GameRenderer renderer;
	ResourcesManager resources;
	std::list<Module::ptr> modules;

	static GameEngine* global_instance;

private:
	sf::Clock frame_time;
	float global_time;

	std::vector<std::function<void(void)>> clean_functions;
	GameEngine(uint32_t win_width, uint32_t win_height);
	void updateObjects(float dt);
	void cleanDeadObjects();
};

template<typename T>
inline void GameEngine::registerObjectClass()
{
	clean_functions.push_back([&]() {T::clean(); });
}
