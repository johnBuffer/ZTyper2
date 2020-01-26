#include "..\include\zombie.hpp"
#include "utils.hpp"
#include "letter.hpp"
#include <iostream>


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
	GameEngine::getInstance().world.addObject(Letter::create(position, letter));
	position += recoil;

}

void Zombie::removeLetter()
{
	shot_letters += getLetter();
	word = word.substr(1);
	//std::cout << "Remove " << word << " " << life << std::endl;
}

bool Zombie::isWordDone() const
{
	return word.size() == 0U;
}

void Zombie::update(float dt)
{
	if (active_target) {
		const float speed = 0.75f;
		const Vec2 direction = (active_target->position - position).getNormalized();
		position += direction * speed;
	}

	checkDead(this);
}

void Zombie::render() const
{
	const size_t radius = 25U;
	auto c = create_obj<sf::CircleShape>(radius, radius);
	c->setOrigin(radius, radius);
	c->setPosition(position.x, position.y);
	c->setFillColor(sf::Color::White);

	const sf::Font& font = GameEngine::getInstance().resources.getFont();
	auto text_shot = create_obj<sf::Text>();
	auto text_remain = create_obj<sf::Text>();
	text_shot->setFont(font);
	text_shot->setFillColor(sf::Color(128, 128, 128));
	text_shot->setCharacterSize(32);
	text_shot->setString(shot_letters);
	text_remain->setFont(font);
	text_remain->setFillColor(sf::Color::White);
	text_remain->setCharacterSize(32);
	text_remain->setString(word);
	auto bounds_shot = text_shot->getGlobalBounds();
	auto bounds_remain = text_remain->getGlobalBounds();

	const float text_height = std::max(bounds_remain.height, bounds_shot.height);

	text_shot->setOrigin(0.0f, text_height + 2 * radius);
	text_remain->setOrigin(0.0f, text_height + 2 * radius);

	const float shot_width = getStringWidth(shot_letters, font, 32);
	const float remain_width = getStringWidth(word, font, 32);
	const float total_width = shot_width + remain_width;
	const float x_offset = - total_width * 0.5f;

	text_shot->setPosition(position.x + x_offset, position.y);
	text_remain->setPosition(position.x + x_offset + shot_width, position.y);

	GameEngine::getInstance().renderer.addDrawable(c);
	GameEngine::getInstance().renderer.addDrawable(text_shot);
	GameEngine::getInstance().renderer.addDrawable(text_remain);
}

bool Zombie::isDone() const
{
	return !life;
}

void Zombie::init()
{
}
