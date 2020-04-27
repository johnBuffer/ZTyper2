#pragma once

#include "Engine/module.hpp"


struct ZombiePhysics : public Module
{
	void process(float dt) override;
};
