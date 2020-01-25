#include "..\include\game_engine.hpp"


void GameEngine::update(float dt)
{
	for (GameObject::ptr object : world.objects) {
		object->update(dt);
	}

	for (auto it = world.objects.begin(); it != world.objects.end(); ++it) {
		if ((*it)->isDead()) {
			world.objects.erase(it);
			--it;
		}
	}
}

void GameEngine::execute_modules(float dt)
{
	for (Module::ptr module : modules) {
		module->process(dt);
	}
}

void GameEngine::render_in(sf::RenderTarget& target) const
{
	for (GameObject::ptr object : world.objects) {
		object->draw(target);
	}
}
