#pragma once

#include "pooled_game_object.hpp"
#include "pointer_builder.hpp"
#include <string>
#include <list>


struct Zombie : public PooledGameObject<Zombie>
{
	using ptr = std::shared_ptr<Zombie>;

	Zombie();
	Zombie(const Vec2& position_, const std::string& word_, const GameObject::ptr target_);

	char getNextLetter() const;
	void shoot();
	void removeLetter();
	bool isWordDone() const;

	// GameObject overrides
	void update(float dt) override;
	void draw(sf::RenderTarget& target) const override;
	bool isDead() const override;

	static void init();
	static void loadFont(const std::string& font_location);

	uint64_t life;
	std::string word;
	GameObject::ptr active_target;
	static sf::Font font;
	static std::list<Zombie::ptr> zombies;
};
