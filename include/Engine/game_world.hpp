#pragma once

#include <vector>
#include "game_object.hpp"


struct GameWorld
{
	GameWorld();

	void addObject(GameObject& object);

private:
	friend struct GameEngine;

	bool add_lock;

	void lock();
	void unlock();
	void addWaitingObjects();

	std::vector<GameObject*> objects;
	std::vector<GameObject*> waiting_add;
};