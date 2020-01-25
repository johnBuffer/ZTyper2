#include "..\include\bullet.hpp"
#include "utils.hpp"


Bullet::Bullet(const Vec2& position_, Zombie::ptr target, float angle_)
	: PooledGameObject(position_, angle_)
	, direction(cos(angle_), sin(angle_))
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
	const float speed = 40.0f;
	position += direction * speed;
	if (isDead()) {
		active_target->shoot();
		Bullet::remove(*this);
	}
}

void Bullet::draw(sf::RenderTarget& target) const
{
	const float width = 200.0f;
	const float height = 40.0f;
	sf::RectangleShape shape(sf::Vector2f(width, height));
	shape.setTexture(&resources.getTexture(0));
	shape.setOrigin(width, height * 0.5f);
	shape.setRotation(radToDeg(angle));
	shape.setPosition(position.x, position.y);

	target.draw(shape);
}

void Bullet::init()
{
	resources.registerTexture("resources/textures/bullet.png");
}
