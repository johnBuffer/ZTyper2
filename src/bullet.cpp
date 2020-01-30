#include "bullet.hpp"
#include "explosion.hpp"
#include "utils.hpp"


Bullet::Bullet(const Vec2& position_, Zombie* target, float angle_)
	: PooledGameObject(position_, angle_)
	, direction(cos(angle_), sin(angle_))
	, active_target(target)
{
}

bool Bullet::isDone() const
{
	const Vec2& to_target = active_target->position - position;
	return (dot(direction, to_target) < 0.0f);
}

void Bullet::update(float dt)
{
	position += direction * speed * getTimeRatio(dt);
	checkDead(this);
}

void Bullet::render() const
{
	const float width = 200.0f;
	const float height = 30.0f;
	auto shape = create_obj<sf::RectangleShape>(sf::Vector2f(width, height));
	shape->setTexture(&resources.getTexture(0));
	shape->setOrigin(width, height * 0.5f);
	shape->setRotation(radToDeg(angle));
	shape->setPosition(position.x, position.y);

	GameEngine::getInstance().renderer.addDrawable(shape);
	GameEngine::getInstance().renderer.addDrawable(shape, GameRenderer::Bloom);
}

void Bullet::onDone()
{
	const float restitution = 0.2f;
	active_target->shoot(direction * (speed * restitution));
	GameEngine::getInstance().world.addObject(Explosion::create(position, 20, 80.0f, 0.25f));
}

void Bullet::init()
{
	resources.registerTexture("resources/textures/bullet.png");
}
