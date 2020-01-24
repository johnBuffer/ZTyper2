#pragma once

#include "game_object.hpp"
#include "drawable.hpp"
#include "pointer_builder.hpp"


struct Turret : public GameObject, public Drawable, public PointerBuilder<Turret>
{
	using ptr = std::shared_ptr<Turret>;
	Turret() = default;
	Turret(float x, float y, float angle);

	void aim_at(GameObject::ptr target);

	void update(float dt) override;

	void draw(sf::RenderTarget& target) const override;

	float getDistanceWithTarget() const;

	GameObject::ptr active_target;
};
