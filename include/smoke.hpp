#pragma once

#include "Engine/pooled_game_object.hpp"


struct Smoke : PooledGameObject<Smoke>
{
	Smoke() = default;
	Smoke(const Vec2& position, const Vec2& speed);

	void update(float dt) override;
	void render() const override;
	bool isDone() const;
	void onDone() override;

	static void init();

	Vec2 speed;
};
