#include "smoke.hpp"

Smoke::Smoke(const Vec2& position, const Vec2& speed_)
	: PooledGameObject(position, 0.0f)
	, speed(speed_)
{
}

void Smoke::update(float dt)
{
	position += speed * dt;
}

void Smoke::render() const
{
}

bool Smoke::isDone() const
{
	return false;
}

void Smoke::onDone()
{
}

void Smoke::init()
{
}
