#pragma once

#include "game_object.hpp"
#include "drawable.hpp"
#include "pointer_builder.hpp"
#include <string>



struct Zombie : public GameObject, public Drawable, public PointerBuilder<Zombie>
{
	using ptr = std::shared_ptr<Zombie>;

	Zombie();
	Zombie(const Vec2& position_, const std::string& word_, const GameObject::ptr target_);

	void update(float dt) override;

	void draw(sf::RenderTarget& target) const override;

	std::string word;
	GameObject::ptr active_target;
};
