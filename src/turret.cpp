#include "turret.hpp"
#include "utils.hpp"

#include <iostream>


Turret::Turret(float x, float y, float angle)
	: GameObject(x, y, angle)
	, active_target(nullptr)
{
}

void Turret::aim_at(Zombie::ptr target)
{
	active_target = target;
}

void Turret::charTyped(uint32_t code, GameWorld& world)
{
	if (active_target) {
		shoot(code, world);
	}
	else {
		findNewTarget(code);
	}
}

void Turret::shoot(uint32_t code, GameWorld& world)
{
	char next_letter = active_target->getNextLetter();
	if (next_letter == code) {
		active_target->shoot();
		if (active_target->isDead()) {
			active_target = nullptr;
		}
	}
}

void Turret::findNewTarget(uint32_t code)
{
	std::list<Zombie::ptr> potential_targets;

	for (Zombie::ptr zombie : Zombie::pool) {
		if (zombie->getNextLetter() == code) {
			potential_targets.push_back(zombie);
		}
	}

	Zombie::ptr next_target = nullptr;
	float min_dist = -1.0f;
	for (Zombie::ptr zombie : potential_targets) {
		const float dist = getDistance(position, zombie->position);
		if (dist < min_dist || min_dist == -1.0f) {
			min_dist = dist;
			next_target = zombie;
		}
	}

	if (next_target) {
		next_target->shoot();
	}

	active_target = next_target;
}

void Turret::update(float dt)
{
	if (active_target) {
		const Vec2& target_position = active_target->position;
		const Vec2 to_target = (target_position - position).getNormalized();
		const Vec2 turret_vec(cos(angle), sin(angle));
		const Vec2 normal = turret_vec.getNormal();

		const float dot_value = dot(to_target, normal);

		const float rotation_speed = 0.15f;
		angle += dot_value * rotation_speed;
	}
}

void Turret::draw(sf::RenderTarget& target) const
{
	const float side_size(50.0f);
	const float barrel_length(60.0F);
	const float barrel_width(15.0f);
	
	// Base
	sf::RectangleShape base(sf::Vector2f(side_size, side_size));
	base.setOrigin(side_size * 0.5f, side_size * 0.5f);
	base.setFillColor(sf::Color::White);
	base.setPosition(position.x, position.y);

	// Barrel
	sf::RectangleShape barrel(sf::Vector2f(barrel_length, barrel_width));
	barrel.setOrigin(barrel_length * 0.2f, barrel_width * 0.5f);
	barrel.setFillColor(sf::Color::Red);
	barrel.setPosition(position.x, position.y);
	barrel.setRotation(radToDeg(angle));

	// Laser
	sf::VertexArray laser(sf::Lines, 2);
	laser[0].position = sf::Vector2f(position.x, position.y);
	laser[0].color = sf::Color::Green;
	const float laser_length = getDistanceWithTarget();
	laser[1].position = sf::Vector2f(position.x + laser_length*cos(angle), position.y + laser_length * sin(angle));
	laser[1].color = sf::Color(0, 255, 0, 0);

	target.draw(base);
	target.draw(laser);
	target.draw(barrel);
}

bool Turret::isDead() const
{
	return false;
}

float Turret::getDistanceWithTarget() const
{
	if (!active_target) {
		return 0.0f;
	}

	return (position - active_target->position).getLength();
}
