#pragma once

#include <vector>
#include <memory>


constexpr float PI = 3.1415928f;

float radToDeg(const float r);

float getSign(const float value);

float getRandRange(float width);

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
