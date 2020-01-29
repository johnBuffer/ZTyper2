#include "vec2.hpp"


Vec2 operator+(const Vec2& v1, const Vec2& v2)
{
	return Vec2(v1.x + v2.x, v1.y + v2.y);
}

Vec2 operator-(const Vec2& v1, const Vec2& v2)
{
	return Vec2(v1.x - v2.x, v1.y - v2.y);
}

Vec2 operator*(const Vec2& v, float f)
{
	return Vec2(v.x * f, v.y * f);
}

float dot(const Vec2& v1, const Vec2& v2)
{
	return v1.x*v2.x + v1.y*v2.y;
}

float getDistance(const Vec2& v1, const Vec2& v2)
{
	return (v1 - v2).getLength();
}
