#include "..\include\zombie.hpp"


sf::Font Zombie::font;

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

char Zombie::getNextLetter() const
{
	if (isDead()) {
		return 0;
	}

	return word[0];
}

void Zombie::shoot()
{
	--life;
}

void Zombie::removeLetter()
{
	word = word.substr(1);
}

bool Zombie::isWordDone() const
{
	return word.empty();
}

bool Zombie::isDead() const
{
	return !life;
}

void Zombie::update(float dt)
{
	if (active_target) {
		const float speed = 0.5f;
		const Vec2 direction = (active_target->position - position).getNormalized();
		position += direction * speed;
	}

	if (isDead()) {
		Zombie::remove(*this);
	}
}

void Zombie::draw(sf::RenderTarget& target) const
{
	const size_t radius = 25U;
	sf::CircleShape c(radius, radius);
	c.setOrigin(radius, radius);
	c.setPosition(position.x, position.y);
	c.setFillColor(sf::Color::White);

	sf::Text text;
	text.setFont(Zombie::font);
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(32);
	text.setString(word);
	auto bounds = text.getGlobalBounds();
	text.setOrigin(bounds.width * 0.5f, bounds.height + 2*radius);
	text.setPosition(position.x, position.y);

	target.draw(c);
	target.draw(text);
}

void Zombie::loadFont(const std::string& font_location)
{
	Zombie::font.loadFromFile(font_location);
}
