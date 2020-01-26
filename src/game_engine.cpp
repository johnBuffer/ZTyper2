#include "..\include\game_engine.hpp"


GameEngine* GameEngine::global_instance = nullptr;


void GameEngine::initialize(uint32_t win_width, uint32_t win_height)
{
	global_instance = new GameEngine(win_width, win_height);
	global_instance->resources.registerFont("font_med.ttf");
}

GameEngine::GameEngine(uint32_t win_width, uint32_t win_height)
	: renderer(win_width, win_height)
{
}

void GameEngine::update(float dt)
{
	updateObjects(dt);
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

void GameEngine::clear()
{
	renderer.clear();
}

GameEngine& GameEngine::getInstance()
{	
	return *global_instance;
}

void GameEngine::updateObjects(float dt)
{
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
			world.objects.erase(it);
			--it;
		}
	}
}
