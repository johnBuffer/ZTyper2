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

float getRandUnder(float max)
{
	constexpr int32_t max_value = 10000;
	constexpr int32_t half = max_value / 2;
	constexpr float div = 1.0f / float(max_value);
	const float val = (rand() % max_value) * div * max;
	return val;
}

float getStringWidth(const std::string str, const sf::Font& font, uint32_t char_size)
{
	float result = 0.0f;
	for (char c : str) {
		result += font.getGlyph(c, char_size, false).advance;
	}

	return result;
}

float getTimeRatio(float dt)
{
	return dt/0.016f;
}
