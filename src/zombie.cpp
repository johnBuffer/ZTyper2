#include "..\include\zombie.hpp"
#include "utils.hpp"
#include "letter.hpp"
#include <iostream>


Animation Zombie::walk_animation;

Zombie::Zombie()
	: PooledGameObject()
	, word("")
	, active_target(nullptr)
	, life(0U)
{
}

Zombie::Zombie(const Vec2& position_, const std::string& word_, GameObject::ptr target_)
	: PooledGameObject(position_, 0.0f)
	, word(word_)
	, active_target(target_)
	, life(word_.size())
	, walk_time(0.0f)
{
}

char Zombie::getLetter() const
{
	if (isWordDone()) {
		return 0;
	}

	return word.front();
}

void Zombie::shoot(const Vec2& recoil)
{
	--life;
	const char letter = shot_letters.front();
	shot_letters = shot_letters.substr(1);
	const float word_width = getShotWidth() + getRemainingWidth();
	const Vec2 letter_position(position.x - word_width * 0.5f, position.y + 30.0f);
	GameEngine::getInstance().world.addObject(Letter::create(letter_position, letter));
	position += recoil;
}

void Zombie::removeLetter()
{
	shot_letters += getLetter();
	word = word.substr(1);
}

bool Zombie::isWordDone() const
{
	return word.size() == 0U;
}

float Zombie::getShotWidth() const
{
	const sf::Font& font = GameEngine::getInstance().resources.getFont();
	return getStringWidth(shot_letters, font, character_size);
}

float Zombie::getRemainingWidth() const
{
	const sf::Font& font = GameEngine::getInstance().resources.getFont();
	return getStringWidth(word, font, character_size);
}

void Zombie::update(float dt)
{
	if (active_target) {
		orientTowards(active_target, 0.05f * getTimeRatio(dt));
		walk_time += getTimeRatio(dt);
		const float speed = 0.75f * getTimeRatio(dt);
		const Vec2 direction = (active_target->position - position).getNormalized();
		position += direction * speed;
	}

	checkDead(this);
}

void Zombie::render() const
{
	const float radius = 50.0f;
	const float animation_speed = 0.3f;
	auto body = create_obj<sf::RectangleShape>(sf::Vector2f(288.0f, 311.0f));
	body->setOrigin(100.0f, 170.0f);
	body->setPosition(position.x, position.y);
	body->setRotation(radToDeg(angle));
	body->setScale(0.5f, 0.5f);
	walk_animation.applyOn(body, animation_speed * walk_time);

	const sf::Font& font = GameEngine::getInstance().resources.getFont();
	auto text_shot = create_obj<sf::Text>();
	auto text_remain = create_obj<sf::Text>();
	text_shot->setFont(font);
	text_shot->setFillColor(sf::Color(128, 128, 128));
	text_shot->setCharacterSize(character_size);
	text_shot->setString(shot_letters);
	text_remain->setFont(font);
	text_remain->setFillColor(sf::Color::White);
	text_remain->setCharacterSize(character_size);
	text_remain->setString(word);
	auto bounds_shot = text_shot->getGlobalBounds();
	auto bounds_remain = text_remain->getGlobalBounds();

	const float text_height = std::max(bounds_remain.height, bounds_shot.height);

	text_shot->setOrigin(0.0f,    - radius);
	text_remain->setOrigin(0.0f,  - radius);

	const float shot_width = getStringWidth(shot_letters, font, character_size);
	const float remain_width = getStringWidth(word, font, character_size);
	const float total_width = shot_width + remain_width;
	const float x_offset = - total_width * 0.5f;

	text_shot->setPosition(position.x + x_offset, position.y);
	text_remain->setPosition(position.x + x_offset + shot_width, position.y);

	GameEngine::getInstance().renderer.addDrawable(body);
	GameEngine::getInstance().renderer.addDrawable(text_shot);
	GameEngine::getInstance().renderer.addDrawable(text_remain);
}

bool Zombie::isDone() const
{
	return !life;
}

void Zombie::onDone()
{
	
}

void Zombie::init()
{
	resources.registerTexture("resources/textures/zombie_move.png");

	walk_animation = Animation(resources.getTexture(0), 3, 6, 17);
}
