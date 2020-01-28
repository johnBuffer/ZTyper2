#pragma once

#include "pooled_game_object.hpp"
#include "game_renderer.hpp"
#include "utils.hpp"


struct Ground : public PooledGameObject<Ground>
{
	void render() const override
	{
		
	}

	static void init()
	{
		resources.registerTexture("resources/textures/ground.jpg");
	}
};
