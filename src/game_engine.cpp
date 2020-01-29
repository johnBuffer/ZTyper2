#include "..\include\game_engine.hpp"


GameEngine* GameEngine::global_instance = nullptr;


void GameEngine::initialize(uint32_t win_width, uint32_t win_height)
{
	global_instance = new GameEngine(win_width, win_height);
	global_instance->resources.registerFont("resources/fonts/font.ttf");
	//global_instance->resources.registerFont("font_med.ttf");
}

GameEngine::GameEngine(uint32_t win_width, uint32_t win_height)
	: renderer(win_width, win_height)
	, global_time(0.0f)
{
}

void GameEngine::update(float dt)
{
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
	renderer.clear();
	for (const GameObject::ptr obj : world.objects) {
		obj->render();
	}
	renderer.render(target);
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
	for (auto it = world.objects.begin(); it != world.objects.end(); ++it) {
		if ((*it)->isDead()) {
			world.objects.erase(it--);
		}
	}
}
