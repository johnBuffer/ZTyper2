#pragma once

#include "pooled_game_object.hpp"
#include "zombie.hpp"


struct Bullet : public PooledGameObject<Bullet>
{
	using ptr = std::shared_ptr<Bullet>;
	Bullet() = default;
	Bullet(const Vec2& position_, Zombie::ptr target, float angle_);

	bool isDone() const;
	void update(float dt) override;
	void draw(sf::RenderTarget& target) const;

	static void init();

	const Vec2 direction;

	Zombie::ptr active_target;
};