#pragma once

#include "pooled_game_object.hpp"


struct Letter : PooledGameObject<Letter>
{
	Letter() = default;
	Letter(const Vec2& position_, char c);

	void update(float dt) override;
	bool isDone() const override;

	void render() const override;

	char glyph;
	float time;
	const float max_time = 0.5f;
	Vec2 speed;
	float angular_velocity;
};
