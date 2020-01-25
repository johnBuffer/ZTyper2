#include "..\include\game_world.hpp"


GameWorld::GameWorld()
	: add_lock(false)
{
}

void GameWorld::addObject(GameObject::ptr object)
{
	if (!add_lock) {
		objects.push_back(object);
	}
	else {
		waiting_add.push_back(object);
	}
}

void GameWorld::addWaitingObjects()
{
	objects.insert(objects.end(), waiting_add.begin(), waiting_add.end());
	waiting_add.clear();
}
