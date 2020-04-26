#include "smoke.hpp"
#include "utils.hpp"


Smoke::Smoke(const Vec2& position, float angle_, float speed_, float size_)
	: PooledGameObject(position, 0.0f)
	, direction(cos(angle_), sin(angle_))
	, speed(speed_)
	, angular_speed(getRandRange(3.0f))
	, life_time(1.0f)
	, max_life_time(0.75f)
	, size(size_)
{
	life_time = max_life_time;
}

void Smoke::update(float dt)
{
	angle = getDecrease(1.0f - getLifeRatio()) * angular_speed;

	life_time -= dt;
	if (life_time < 0.0f) life_time = 0.0f;

	checkDead(this);
}

void Smoke::render() const
{
	const float side_size = size * (1.5f + std::pow(1.0f - getLifeRatio(), 2.0f));
	auto shape = create_obj<sf::RectangleShape>(sf::Vector2f(side_size, side_size));
	shape->setOrigin(side_size * 0.5f, side_size * 0.5f);

	const Vec2 p = position + direction * (speed * getDecrease(1.0f - getLifeRatio()));
	shape->setPosition(p.x, p.y);
	shape->setTexture(&resources.getTexture(0));
	shape->setRotation(57.2958f * angle);
	shape->setFillColor(sf::Color(255, 255, 255, 50.0f * getLifeRatio()));

	GameRenderer& renderer = GameEngine::getInstance().renderer;
	renderer.addDrawable(shape, layer_id);
}

bool Smoke::isDone() const
{
	return life_time <= 0.0f;
}

void Smoke::onDone()
{
}

float Smoke::getLifeRatio() const
{
	return life_time / max_life_time;
}

void Smoke::init()
{
	layer_id = GameEngine::getInstance().renderer.addLayer();
	resources.registerTexture("resources/textures/smoke.png");
}
