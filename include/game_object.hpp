#pragma once

#include "vec2.hpp"
#include <memory>
#include <SFML/Graphics.hpp>
#include <cstdint>


struct GameObject
{
	using ptr = std::shared_ptr<GameObject>;

	GameObject()
		: position(0.0f, 0.0f)
		, angle(0.0f)
		, dead(false)
	{}

	GameObject(const Vec2& position_, float angle_)
		: position(position_)
		, angle(angle_)
		, dead(false)
	{}

	GameObject(float x, float y, float angle_)
		: GameObject(Vec2(x, y), angle_)
	{}

	float getTargetAlignement(const GameObject::ptr target) const
	{
		if (!target) {
			return 1.0f;
		}

		const Vec2& target_position = target->position;
		const Vec2 to_target = (target_position - position).getNormalized();
		const Vec2 object_vec(cos(angle), sin(angle));
		const Vec2 normal = object_vec.getNormal();

		return dot(to_target, normal);
	}

	void orientTowards(const GameObject::ptr target, float rotation_speed)
	{
		angle += getTargetAlignement(target) * rotation_speed;
	}

	virtual void update(float dt) {}
	virtual void render() const {}
	virtual bool isDone() const { return false; }
	virtual void onDone() {};
	bool isDead() const { return dead; }

	Vec2 position;
	float angle;
	bool dead;
};
