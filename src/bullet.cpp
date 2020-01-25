#include "..\include\bullet.hpp"

Bullet::Bullet(const Vec2& position_, Zombie::ptr target)
	: PooledGameObject(position_, 0.0f)
	, direction((target->position - position_).getNormalized())
	, active_target(target)
{

}

bool Bullet::isDead() const
{
	const Vec2& to_target = active_target->position - position;
	return (dot(direction, to_target) < 0.0f);
}

void Bullet::update(float dt)
{
	const float speed = 10.0f;
	position += direction * speed;
	if (isDead()) {
		active_target->shoot();
		Bullet::remove(*this);
	}
}

void Bullet::draw(sf::RenderTarget& target) const
{
	const size_t radius = 6U;
	sf::CircleShape c(radius, radius);
	c.setOrigin(radius, radius);
	c.setPosition(position.x, position.y);
	c.setFillColor(sf::Color::White);

	target.draw(c);
}
