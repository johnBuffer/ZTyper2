#pragma once

#include <memory>


struct Module
{
	using ptr = std::shared_ptr<Module>;
	virtual void process(float dt) = 0;
};