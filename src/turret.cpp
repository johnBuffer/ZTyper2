#include "turret.hpp"

Turret::Turret(float x, float y, float angle)
	: GameObject(x, y, angle)
{
}

void Turret::draw(sf::RenderTarget& target) const
{
	const float side_size(50.0f);
	const float barrel_length(60.0F);
	const float barrel_width(15.0f);

	sf::RectangleShape base(sf::Vector2f(side_size, side_size));
	base.setOrigin(side_size * 0.5f, side_size * 0.5f);
	base.setFillColor(sf::Color::White);
	base.setPosition(position.x, position.y);

	sf::RectangleShape barrel(sf::Vector2f(barrel_width, barrel_length));
	barrel.setOrigin(barrel_width * 0.5f, barrel_length * 0.8f);
	barrel.setFillColor(sf::Color::Red);
	barrel.setPosition(position.x, position.y);
	barrel.setRotation(angle);

	target.draw(base);
	target.draw(barrel);
}
