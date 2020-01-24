#include "..\include\game_engine.hpp"


void GameEngine::update(float dt)
{
	for (GameObject::ptr object : world.objects) {
		object->update(dt);
	}
}
