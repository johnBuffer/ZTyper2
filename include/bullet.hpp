#pragma once

#include "pooled_game_object.hpp"
#include "zombie.hpp"


struct Bullet : public PooledGameObject<Bullet>
{
	using ptr = std::shared_ptr<Bullet>;
	Bullet() = default;
	Bullet(const Vec2& position_, Zombie::ptr target, float angle_);

	bool isDone() const override;
	void update(float dt) override;
	void render() const override;
	void onDone() override;

	static void init();

	const Vec2 direction;

	Zombie::ptr active_target;

	const float speed = 60.0f;
};