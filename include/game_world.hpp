#pragma once

#include <vector>
#include "game_object.hpp"


struct GameWorld
{
	GameWorld();

	void lock();
	void unlock();

	void addObject(GameObject::ptr object);
	void addWaitingObjects();

	std::vector<GameObject::ptr> objects;

	std::vector<GameObject::ptr> waiting_add;

private:
	bool add_lock;

};