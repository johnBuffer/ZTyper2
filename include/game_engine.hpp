#pragma once

#include "game_world.hpp"
#include <SFML/Graphics.hpp>


struct GameEngine
{
	void update(float dt);

	void render_in(sf::RenderTarget& target) const;

	GameWorld world;
};