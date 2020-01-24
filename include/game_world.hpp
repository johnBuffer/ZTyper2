#pragma once

#include <vector>
#include "game_object.hpp"


struct GameWorld
{
	void addObject(GameObject::ptr object);

	std::vector<GameObject::ptr> objects;
};