#pragma once

#include "game_world.hpp"
#include "pooled_game_object.hpp"
#include "pointer_builder.hpp"
#include "zombie.hpp"
#include "animation.hpp"


struct Turret : public PooledGameObject<Turret>
{
	using ptr = std::unique_ptr<Turret>;
	Turret() = default;
	Turret(float x, float y, float angle);
	
	// Turret specific
	void aim_at(Zombie* target);
	void charTyped(uint32_t code);
	void shoot(uint32_t code);
	void findNewTarget(uint32_t code);
	void resetTarget();

	// GameObjects overrides
	void update(float dt) override;
	void render() const override;
	bool isDone() const override;

	float getDistanceWithTarget() const;

	static void init();

private:
	Zombie* active_target;
	std::vector<Zombie*> waiting_shots;

	static Animation fire_animation;

	int32_t life;
	float shot_time;
	float recoil;

	void checkZombiesCollisions();
};
