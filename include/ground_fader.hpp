#pragma once

#include "game_object.hpp"


struct GroundFader : public GameObject
{
	void update(float dt) override;
	void render() const override;
};