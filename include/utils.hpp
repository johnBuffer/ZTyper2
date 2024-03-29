#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <cmath>


constexpr float PI = 3.1415928f;

float radToDeg(const float r);

float getSign(const float value);

float getRandRange(float width);

float getRandUnder(float max);

template<typename T>
const T& getRandomElemFromVector(const std::vector<T>& vector)
{
	const std::size_t vector_size(vector.size());
	const std::size_t rand_index(rand() % vector_size);

	return vector[rand_index];
}

template<typename T, typename... Args>
static std::shared_ptr<T> create_obj(Args&&... args)
{
	return std::make_shared<T>(args...);
}

float getStringWidth(const std::string str, const sf::Font& font, uint32_t char_size);

float getTimeRatio(float dt);

float getDecrease(float dt, float power = 0.0f);
