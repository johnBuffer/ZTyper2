#include "letter.hpp"
#include "utils.hpp"


Letter::Letter(const Vec2& position_, char c)
	: PooledGameObject(position_, 0.0f)
	, glyph(c)
	, time(0.0f)
	, speed(getRandRange(10.0f), -20.0f + getRandRange(5.0f))
	, angular_velocity(getRandRange(20.0f))
{
}

void Letter::update(float dt)
{
	time += dt;
	const float time_factor = getTimeRatio(dt);
	position += speed * time_factor;
	angle += angular_velocity * time_factor;

	speed += Vec2(0.0f, 1.5f) * time_factor;
	//angular_velocity *= 0.95f / time_factor;

	checkDead(this);
}

bool Letter::isDone() const
{
	return time > max_time;
}

void Letter::render() const
{
	const float time_ratio = 1.0f - time / max_time;
	sf::Color color(255*time_ratio, 255 * time_ratio, 255 * time_ratio);

	auto text = create_obj<sf::Text>();
	text->setFont(GameEngine::getInstance().resources.getFont());
	text->setFillColor(color);
	text->setCharacterSize(32);
	text->setString(glyph);
	auto bounds = text->getGlobalBounds();
	text->setOrigin(bounds.width * 0.5f, bounds.height * 0.5f);
	text->setRotation(angle);
	text->setPosition(position.x, position.y);

	GameEngine::getInstance().renderer.addDrawable(text);
}
