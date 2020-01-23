#pragma once

#include "game_object.hpp"
#include "drawable.hpp"


struct Turret : public GameObject, public Drawable
{
	Turret() = default;
	Turret(float x, float y, float angle);

	void aim_at(const Vec2& target_position);

	void draw(sf::RenderTarget& target) const override;
};
