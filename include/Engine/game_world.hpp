#pragma once

#include <vector>
#include "game_object.hpp"


struct GameWorld
{
	GameWorld();

	void addObject(GameObject::ptr object);

private:
	friend struct GameEngine;

	bool add_lock;

	void lock();
	void unlock();
	void addWaitingObjects();

	std::vector<GameObject::ptr> objects;
	std::vector<GameObject::ptr> waiting_add;
};