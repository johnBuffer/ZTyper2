#pragma once

#include "Engine/pooled_game_object.hpp"
#include <SFML/Graphics.hpp>


struct Particule
{
	sf::Vector2f position;
	Vec2 speed;
	float size;
	float angle;
	float color_intensity;

	void update(float dt);
};


struct Explosion : public PooledGameObject<Explosion>
{
	Explosion() = default;
	Explosion(const Vec2& position_, uint32_t n, float size, float life_time_, bool ground_trace_ = false);

	void update(float dt) override;
	void render() const override;
	bool isDone() const override;
	void onDone() override;

	static void init();

private:
	void addParticuleToVA(sf::VertexArray& va, uint64_t i) const;

	float time;
	float life_time;
	bool ground_trace;

	std::vector<Particule> particules;
};