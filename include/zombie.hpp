#pragma once

#include "pooled_game_object.hpp"
#include "animation.hpp"
#include <string>
#include <list>


struct Zombie : public PooledGameObject<Zombie>
{
	using ptr = std::unique_ptr<Zombie>;

	Zombie();
	Zombie(const Vec2& position_, const std::string& word_, GameObject* target_);

	char getLetter() const;
	void shoot(const Vec2& recoil);
	void removeLetter();
	bool isWordDone() const;

	float getShotWidth() const;
	float getRemainingWidth() const;

	// GameObject overrides
	void update(float dt) override;
	void render() const override;
	bool isDone() const override;
	void onDone() override;

	static void init();

	float walk_time;
	uint64_t life;
	std::string word;
	std::string shot_letters;
	GameObject* active_target;

	static Animation walk_animation;

	const uint32_t character_size = 32U;
};
