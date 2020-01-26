#include "..\include\game_engine.hpp"


GameEngine* GameEngine::global_instance = nullptr;


void GameEngine::initialize()
{
	resources.registerFont("font_med.ttf");
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
	if (!global_instance) {
		global_instance = new GameEngine();
		global_instance->initialize();
	}
	
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
