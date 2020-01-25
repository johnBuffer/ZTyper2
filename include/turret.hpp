#pragma once

#include "game_world.hpp"
#include "game_object.hpp"
#include "pointer_builder.hpp"
#include "zombie.hpp"


struct Turret : public GameObject, public PointerBuilder<Turret>
{
	using ptr = std::shared_ptr<Turret>;
	Turret() = default;
	Turret(float x, float y, float angle);
	
	// Turret specific
	void aim_at(Zombie::ptr target);
	void charTyped(uint32_t code);
	void shoot(uint32_t code, GameWorld& world);
	void findNewTarget(uint32_t code, GameWorld& world);

	// GameObjects overrides
	void update(float dt) override;
	void draw(sf::RenderTarget& target) const override;
	bool isDead() const override;

	float getDistanceWithTarget() const;
	float getTargetAlignement() const;

	Zombie::ptr active_target;
	std::vector<Zombie::ptr> waiting_shots;
};
