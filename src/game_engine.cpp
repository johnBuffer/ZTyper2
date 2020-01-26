#include "..\include\game_engine.hpp"


GameEngine* GameEngine::global_instance = nullptr;


void GameEngine::update(float dt)
{
	world.add_lock = true;
	for (GameObject::ptr object : world.objects) {
		object->update(dt);
	}

	for (auto it = world.objects.begin(); it != world.objects.end(); ++it) {
		if ((*it)->isDead()) {
			world.objects.erase(it);
			--it;
		}
	}
	world.add_lock = false;
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
		obj->draw(target);
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
	}
	
	return *global_instance;
}
