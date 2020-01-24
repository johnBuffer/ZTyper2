#pragma once

#include "vec2.hpp"


struct GameObject
{
	GameObject()
		: position(0.0f, 0.0f)
		, angle(0.0f)
	{}

	GameObject(const Vec2& position_, float angle_)
		: position(position_)
		, angle(angle_)
	{}

	GameObject(float x, float y, float angle_)
		: GameObject(Vec2(x, y), angle_)
	{}

	virtual void update(float dt) {};

	Vec2 position;
	float angle;
};
