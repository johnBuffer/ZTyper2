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

	char getLetter() const;
	void shoot(const Vec2& recoil);
	void removeLetter();
	bool isWordDone() const;

	// GameObject overrides
	void update(float dt) override;
	void render() const override;
	bool isDone() const override;

	static void init();

	uint64_t life;
	std::string word;
	std::string shot_letters;
	GameObject::ptr active_target;
};
