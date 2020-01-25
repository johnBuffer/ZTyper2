#pragma once

#include <vector>
#include "game_object.hpp"


struct GameWorld
{
	GameWorld();

	void addObject(GameObject::ptr object);
	void addWaitingObjects();

	std::vector<GameObject::ptr> objects;

	bool add_lock;
	std::vector<GameObject::ptr> waiting_add;
};