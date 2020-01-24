#include "..\include\zombie.hpp"



Zombie::Zombie()
	: GameObject()
	, active_target(nullptr)
{
}

Zombie::Zombie(const Vec2& position_, const GameObject& target_)
	: GameObject(position_, 0.0f)
	, active_target(&target_)
{
}

void Zombie::update(float dt)
{
	if (active_target) {
		const float speed = 1.0f;
		const Vec2 direction = (active_target->position - position).getNormalized();

		position += direction * speed;
	}
}

void Zombie::draw(sf::RenderTarget& target) const
{
	const float radius = 25.0f;
	sf::CircleShape c(radius, radius);
	c.setOrigin(radius, radius);
	c.setPosition(position.x, position.y);
	c.setFillColor(sf::Color::White);
	target.draw(c);
}
