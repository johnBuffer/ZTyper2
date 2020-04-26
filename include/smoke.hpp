#pragma once

#include "Engine/pooled_game_object.hpp"


struct Smoke : PooledGameObject<Smoke>
{
	Smoke() = default;
	Smoke(const Vec2& position, float angle_, float speed_, float size_ = 200.0f);

	void update(float dt) override;
	void render() const override;
	bool isDone() const;
	void onDone() override;
	float getLifeRatio() const;

	static void init();

	Vec2 direction;
	float speed;
	float angular_speed;
	float life_time;
	const float max_life_time;
	const float size;
};
