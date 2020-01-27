#include "..\include\zombie_physics.hpp"
#include "zombie.hpp"


void ZombiePhysics::process(float dt)
{
	const float z_radius = 80.0f;
	const float min_dist = 2.0f * z_radius;
	const uint64_t z_count = Zombie::pool.size();
	for (uint64_t i(0U); i < z_count; ++i) {
		Zombie::ptr z1 = Zombie::pool[i];
		for (uint64_t k(i+1); k < z_count; ++k) {
			 Zombie::ptr z2 = Zombie::pool[k];
			const Vec2 z1_to_z2 = z2->position - z1->position;
			const float distance = z1_to_z2.getLength();
			if (distance < min_dist) {
				const Vec2 axis = z1_to_z2.getNormalized();
				const float delta = 0.5f * (min_dist - distance);
				z1->position -= axis * delta;
				z2->position += axis * delta;
			}
		}
	}
}
