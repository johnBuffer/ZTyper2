#pragma once

#include "pooled_game_object.hpp"
#include "zombie.hpp"


struct Bullet : public PooledGameObject<Bullet>
{
	using ptr = std::unique_ptr<Bullet>;
	Bullet() = default;
	Bullet(const Vec2& position_, Zombie* target, float angle_);

	bool isDone() const override;
	void update(float dt) override;
	void render() const override;
	void onDone() override;

	static void init();

	const Vec2 direction;

	Zombie* active_target;

	const float speed = 60.0f;
};