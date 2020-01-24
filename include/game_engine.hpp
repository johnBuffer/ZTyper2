#pragma once

#include "game_world.hpp"

struct GameEngine
{
	void update(float dt);

	GameWorld world;
};