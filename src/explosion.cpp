#include "explosion.hpp"
#include "utils.hpp"
#include "textured_va.hpp"

#include <iostream>


Explosion::Explosion(const Vec2& position_, uint32_t n, float size, float life_time_, bool ground_trace_)
	: life_time(life_time_)
	, time(0.0f)
	, ground_trace(ground_trace_)
{
	for (uint32_t i(n); i--;) {
		particules.emplace_back();
		Particule& particule = particules.back();
		particule.angle = getRandUnder(2 * PI);
		particule.position.x = position_.x;
		particule.position.y = position_.y;
		const float speed_direction = getRandUnder(2 * PI);
		const float speed = getRandUnder(10.0f);
		particule.speed = Vec2(speed * cos(speed_direction), speed * sin(speed_direction));
		particule.size = size * 0.5f + getRandUnder(size * 0.5f);
		particule.color_intensity = getRandUnder(200.0f);
	}
}

void Explosion::update(float dt)
{
	time += dt;
	for (Particule& p : particules) {
		p.update(dt);
	}

	checkDead(this);
}

void Explosion::render() const
{
	const uint64_t n = particules.size();
	auto tva = create_obj<TexturedVa>(sf::Quads, 4 * n);
	tva->rs.texture = &resources.getTexture(0);

	for (uint64_t i(n); i--;) {
		addParticuleToVA(tva->va, i);
	}

	GameEngine::getInstance().renderer.addDrawable(tva, ground_trace ? GameRenderer::Ground : layer_id);
}

bool Explosion::isDone() const
{
	return time + 0.1f > life_time;
}

void Explosion::onDone()
{
	const uint64_t n = particules.size();
	auto tva = create_obj<TexturedVa>(sf::Quads, 4 * n);
	tva->rs.texture = &resources.getTexture(0);

	for (uint64_t i(n); i--;) {
		addParticuleToVA(tva->va, i);
	}

	GameEngine::getInstance().renderer.addDrawable(tva, GameRenderer::Ground);
}

void Explosion::init()
{
	layer_id = GameEngine::getInstance().renderer.addLayer();

	resources.registerTexture("resources/textures/blood.png");
}

void Explosion::addParticuleToVA(sf::VertexArray& va, uint64_t i) const
{
	const Particule& particule = particules[i];
	const float p_angle = ground_trace ? getRandUnder(2.0f * PI) : particule.angle;
	const float cosa = cos(p_angle);
	const float sina = sin(p_angle);
	const float x = particule.position.x;
	const float y = particule.position.y;
	const float size = particule.size * (1.0f - time / life_time);
	const uint8_t color_component = static_cast<uint8_t>(particule.color_intensity);
	const uint8_t alpha = ground_trace ? 128U : 255U;
	const sf::Color color = sf::Color(color_component, color_component, color_component, alpha);

	va[4 * i + 0].position = sf::Vector2f(x + size * cosa, y + size * sina);
	va[4 * i + 1].position = sf::Vector2f(x - size * sina, y + size * cosa);
	va[4 * i + 2].position = sf::Vector2f(x - size * cosa, y - size * sina);
	va[4 * i + 3].position = sf::Vector2f(x + size * sina, y - size * cosa);

	va[4 * i + 0].texCoords = sf::Vector2f(0.0f, 0.0f);
	va[4 * i + 1].texCoords = sf::Vector2f(70.0f, 0.0f);
	va[4 * i + 2].texCoords = sf::Vector2f(70.0f, 76.0f);
	va[4 * i + 3].texCoords = sf::Vector2f(0.0f, 76.0f);

	va[4 * i + 0].color = color;
	va[4 * i + 1].color = color;
	va[4 * i + 2].color = color;
	va[4 * i + 3].color = color;
}

void Particule::update(float dt)
{
	const float tr = getTimeRatio(dt);
	position.x += speed.x * tr;
	position.y += speed.y * tr;
}
