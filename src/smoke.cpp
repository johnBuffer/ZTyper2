#include "smoke.hpp"
#include "utils.hpp"


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
	const float side_size = 100.0f;
	auto shape = create_obj<sf::RectangleShape>(sf::Vector2f(side_size, side_size));
	shape->setOrigin(side_size * 0.5f, side_size * 0.5f);
	shape->setPosition(position.x, position.y);
	shape->setTexture(&resources.getTexture(0));

	GameRenderer& renderer = GameEngine::getInstance().renderer;
	renderer.addDrawable(shape, layer_id);
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
	layer_id = GameEngine::getInstance().renderer.addLayer();
	resources.registerTexture("resources/textures/smoke.png");
}
