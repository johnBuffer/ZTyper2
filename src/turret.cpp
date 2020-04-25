#include "turret.hpp"
#include "utils.hpp"

#include <iostream>
#include <limits>
#include "bullet.hpp"
#include <Engine/sound_player.hpp>


Animation Turret::fire_animation;
std::size_t Turret::fire_sound;


Turret::Turret(float x, float y, float angle)
	: PooledGameObject(x, y, angle)
	, active_target(nullptr)
	, waiting_shots(0U)
	, shot_time(std::numeric_limits<float>::max())
	, recoil(0.0f)
	, life(1)
{
}

void Turret::aim_at(Zombie* target)
{
	active_target = target;
}

void Turret::charTyped(uint32_t code)
{
	if (!active_target) {
		findNewTarget(code);
	}

	shoot(code);
}

void Turret::shoot(uint32_t code)
{
	if (active_target && code < 128) {
		const char letter = active_target->getLetter();
		if (letter == char(code)) {
			SoundPlayer::playInstanceOf(fire_sound);
			active_target->removeLetter();
			waiting_shots.push_back(active_target);
			if (active_target->isWordDone()) {
				active_target = nullptr;
			}
		}
	}
}

void Turret::findNewTarget(uint32_t code)
{
	std::list<Zombie*> potential_targets;

	const float position_threshold = -50.0f;
	for (Zombie::ptr& zombie : Zombie::pool) {
		if (zombie->position.y > position_threshold) {
			if (zombie->getLetter() == code) {
				potential_targets.push_back(&(*zombie));
			}
		}
	}

	Zombie* next_target = nullptr;
	float min_dist = -1.0f;
	for (Zombie* zombie : potential_targets) {
		const float dist = getDistance(position, zombie->position);
		if (dist < min_dist || min_dist == -1.0f) {
			min_dist = dist;
			next_target = zombie;
		}
	}

	active_target = next_target;
}

void Turret::resetTarget()
{
	active_target = nullptr;
}

void Turret::update(float dt)
{
	shot_time += dt;
	const float target_alignment = getTargetAlignment(active_target);
	if (active_target) {
		const float rotation_speed = 0.3f * getTimeRatio(dt);
		orientTowards(active_target, rotation_speed);
	}

	if (waiting_shots.size()) {
		const float min_alignment = 0.05f;
		if (std::abs(target_alignment) < min_alignment || !active_target) {
			shot_time = 0.0f;
			recoil = 30.0f;
			GameEngine::getInstance().world.addObject(Bullet::create(position, waiting_shots.back(), angle + getRandRange(min_alignment)));
			waiting_shots.pop_back();
		}
	}

	checkZombiesCollisions();
	
	const float recover_speed = 70.0f;
	const float recover_amount = dt * recover_speed;
	recoil = recoil > recover_amount ? recoil - recover_amount : 0.0f;
}

void Turret::render() const
{
	const float side_size(150.0f);
	const float barrel_length(170.0F);
	const float barrel_width(100.0f);
	const float fire_length(150.0f);
	const float fire_width(40.0f);
	
	// Base
	auto base = create_obj<sf::RectangleShape>(sf::Vector2f(side_size, side_size));
	base->setTexture(&resources.getTexture(1));
	base->setOrigin(side_size * 0.5f, side_size * 0.5f);
	base->setFillColor(sf::Color::White);
	base->setPosition(position.x, position.y);

	// Barrel
	auto barrel = create_obj<sf::RectangleShape>(sf::Vector2f(barrel_length, barrel_width));
	barrel->setTexture(&resources.getTexture(0));
	barrel->setOrigin(barrel_length * 0.2f + recoil, barrel_width * 0.5f);
	barrel->setPosition(position.x, position.y);
	barrel->setRotation(radToDeg(angle));

	// Fire
	const float animation_speed = 70.0f;
	const float barrel_dist = barrel_length * 0.5f;
	auto fire = create_obj<sf::RectangleShape>(sf::Vector2f(fire_length, fire_width));
	fire->setOrigin(0.0f, fire_width * 0.5f);
	fire->setPosition(position.x + barrel_dist * cos(angle), position.y + barrel_dist * sin(angle));
	fire->setRotation(radToDeg(angle));
	fire_animation.applyOn(fire, animation_speed * shot_time);

	// Laser
	auto laser = create_obj<sf::VertexArray>(sf::Lines, 2);
	sf::VertexArray& lsr = *laser;
	const float laser_length = getDistanceWithTarget();
	lsr[0].position = sf::Vector2f(position.x, position.y);
	lsr[0].color = sf::Color::Green;
	lsr[1].position = sf::Vector2f(position.x + laser_length*cos(angle), position.y + laser_length * sin(angle));
	lsr[1].color = sf::Color(0, 255, 0, 0);

	GameRenderer& renderer = GameEngine::getInstance().renderer;
	renderer.addDrawable(base, layer_id);
	renderer.addDrawable(laser, layer_id);
	renderer.addDrawable(barrel, layer_id);
	renderer.addDrawable(fire, layer_id);
	renderer.addDrawable(laser, GameRenderer::Bloom);
	renderer.addDrawable(fire, GameRenderer::Bloom);
}

bool Turret::isDone() const
{
	return life < 1;
}

float Turret::getDistanceWithTarget() const
{
	if (!active_target) {
		return 0.0f;
	}

	return (position - active_target->position).getLength();
}

void Turret::init()
{
	layer_id = GameEngine::getInstance().renderer.addLayer();
	resources.registerTexture("resources/textures/turret.png");
	resources.registerTexture("resources/textures/base.png");
	resources.registerTexture("resources/textures/explosion.png");

	fire_animation = Animation(resources.getTexture(2), 1, 19, 19, false);
	fire_sound = SoundPlayer::registerSound("fire1.wav");
}

void Turret::checkZombiesCollisions()
{
	const float z_radius = 80.0f;
	const float turret_radius = 80.0f;
	const float min_dist = 2.0f * z_radius;
	uint64_t z_count = Zombie::pool.size();
	for (uint64_t i(0U); i < z_count; ++i) {
		Zombie& z1 = *Zombie::pool[i];
		const Vec2 z_to_turret = position - z1.position;
		const float distance = z_to_turret.getLength();
		if (distance < min_dist) {
			z1.setDead(&(z1));
			--life;
			std::cout << life << std::endl;
		}
	}
}
