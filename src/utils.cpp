#include "utils.hpp"


float radToDeg(const float r)
{
	return 57.2958f * r;
}

float getSign(const float value)
{
	return value < 0.0f ? -1.0f : 1.0f;
}