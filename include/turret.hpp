#pragma once

#include "game_object.hpp"
#include "drawable.hpp"


struct Turret : public GameObject, public Drawable
{
	Turret() = default;
	Turret(float x, float y, float angle);

	void aim_at(const GameObject& target);

	void update(float dt);

	void draw(sf::RenderTarget& target) const override;

	float getDistanceWithTarget() const;

	const GameObject* active_target;
};
