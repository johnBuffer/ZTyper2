#pragma once

#include "game_object.hpp"
#include "drawable.hpp"
#include <string>


struct Zombie : public GameObject, public Drawable
{
	Zombie();
	Zombie(const Vec2& position_, const GameObject& target_);

	void update(float dt) override;

	void draw(sf::RenderTarget& target) const override;

	std::string word;
	const GameObject* active_target;
};
