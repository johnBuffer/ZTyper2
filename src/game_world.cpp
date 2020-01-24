#include "..\include\game_world.hpp"


void GameWorld::addObject(GameObject::ptr object)
{
	objects.push_back(object);
}
