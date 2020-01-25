#pragma once

#include "module.hpp"


struct ZombiePhysics : public Module
{
	void process(float dt) override;
};
