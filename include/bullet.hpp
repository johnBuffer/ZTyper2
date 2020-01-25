#pragma once

#include "pooled_game_object.hpp"
#include "zombie.hpp"


struct Bullet : public PooledGameObject<Bullet>
{
	Bullet() = default;
	Bullet(const Vec2& position_, Zombie::ptr target);

	bool isDead() const override;
	void update(float dt) override;
	void draw(sf::RenderTarget& target) const;

	const Vec2 direction;

	Zombie::ptr active_target;
};