#include "turret.hpp"

Turret::Turret(float x, float y, float angle)
	: GameObject(x, y, angle)
{
}

void Turret::draw(sf::RenderTarget& target) const
{
	const float side_size(50.0f);
	sf::RectangleShape base(sf::Vector2f(side_size, side_size));
	base.setOrigin(side_size * 0.5f, side_size * 0.5f);
	base.setFillColor(sf::Color::White);
	base.setPosition(position.x, position.y);

	target.draw(base);
}
