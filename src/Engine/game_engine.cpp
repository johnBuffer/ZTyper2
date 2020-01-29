#include "game_engine.hpp"


GameEngine* GameEngine::global_instance = nullptr;


void GameEngine::initialize(uint32_t win_width, uint32_t win_height)
{
	global_instance = new GameEngine(win_width, win_height);
	global_instance->resources.registerFont("resources/fonts/font.ttf");
	//global_instance->resources.registerFont("font_med.ttf");
}

void GameEngine::exit()
{
	if (global_instance) {
		global_instance->clean();
		delete global_instance;
	}
}

GameEngine::GameEngine(uint32_t win_width, uint32_t win_height)
	: renderer(win_width, win_height)
	, global_time(0.0f)
{
}

void GameEngine::update(float dt)
{
	renderer.clear();
	updateObjects(dt);
	execute_modules(dt);
	world.addWaitingObjects();
}

void GameEngine::execute_modules(float dt)
{
	for (Module::ptr module : modules) {
		module->process(dt);
	}
}

void GameEngine::render_in(sf::RenderTarget& target) const
{
	for (const GameObject::ptr obj : world.objects) {
		obj->render();
	}
	renderer.render(target);
}

void GameEngine::clean()
{
	resources.clear();
	for (auto clean_fun : clean_functions) {
		clean_fun();
	}
}

GameEngine& GameEngine::getInstance()
{	
	return *global_instance;
}

float GameEngine::getTime() const
{
	return global_time;
}

void GameEngine::updateObjects(float forced_dt)
{
	const float dt = forced_dt ? forced_dt : frame_time.restart().asSeconds();
	global_time += dt;
	world.lock();
	for (GameObject::ptr object : world.objects) {
		object->update(dt);
	}
	cleanDeadObjects();
	world.unlock();
}

void GameEngine::cleanDeadObjects()
{
	const uint64_t objects_count = world.objects.size();
	uint64_t deleted_count = 0U;

	for (uint64_t i(0U); i < objects_count - deleted_count; ++i) {
		GameObject::ptr& obj = world.objects[i];
		if (obj->isDead()) {
			const uint64_t last_object_rank = objects_count - deleted_count - 1U;
			GameObject::ptr& last_obj = world.objects[last_object_rank];
			std::swap(obj, last_obj);
			++deleted_count;
			--i;
		}
	}

	world.objects.resize(objects_count - deleted_count);
}
