#pragma once

#include <cmath>


struct Vec2
{
	Vec2()
		: x(0.0f)
		, y(0.0f)
	{}

	Vec2(float x_, float y_)
		: x(x_)
		, y(y_)
	{}

	float x, y;

	void operator+=(const Vec2& v)
	{
		x += v.x;
		y += v.y;
	}

	void operator-=(const Vec2& v)
	{
		x -= v.x;
		y -= v.y;
	}

	float getLength() const
	{
		return sqrt(x*x + y*y);
	}

	Vec2 getNormalized() const
	{
		const float length = getLength();
		return Vec2(x / length, y / length);
	}
};


Vec2 operator+(const Vec2& v1, const Vec2& v2);

Vec2 operator-(const Vec2& v1, const Vec2& v2);

Vec2 operator*(const Vec2& v, float f);





