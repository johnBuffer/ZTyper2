#pragma once

#include "game_object.hpp"
#include "drawable.hpp"


struct Turret : public GameObject, public Drawable
{
	Turret() = default;
	Turret(float x, float y, float angle);

	void draw(sf::RenderTarget& target) const override;
};
