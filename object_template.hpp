#pragma once

#include "pooled_game_object.hpp"


struct Object : PooledGameObject<Object>
{
	Object() = default;
	Object(const Vec2& position, float angle);

	void update(float dt) override;
	void render() const override;
	bool isDone() const;
	void onDone() override;

	static void init();
};