#include "utils.hpp"
#include <cstdint>
#include <stdlib.h>


float radToDeg(const float r)
{
	return 57.2958f * r;
}

float getSign(const float value)
{
	return value < 0.0f ? -1.0f : 1.0f;
}

float getRandRange(float width)
{
	constexpr int32_t max_value = 10000;
	constexpr int32_t half = max_value / 2;
	constexpr float div = 1.0f / float(max_value);
	const float val = (rand() % max_value - half) * div * width;
	return val;
}