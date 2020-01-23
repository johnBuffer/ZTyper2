#include "turret.hpp"
#include "utils.hpp"

#include <iostream>


Turret::Turret(float x, float y, float angle)
	: GameObject(x, y, angle)
{
}

void Turret::aim_at(const Vec2& target_position)
{
	const Vec2 to_target = (target_position - position).getNormalized();

	const Vec2 turret_vec(cos(angle), sin(angle));
	const Vec2 normal = turret_vec.getNormal();

	const float dot_value = dot(to_target, normal);

	const float rotation_speed = 0.2f;
	angle += dot_value * rotation_speed;
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


	target.draw(base);
	target.draw(barrel);
}
