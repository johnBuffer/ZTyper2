#pragma once

#include <SFML/Graphics.hpp>

template<typename T>
struct CustomDrawable : public sf::Drawable
{
	template<typename... Args>
	CustomDrawable(Args&&... args)
		: shape(args...)
	{
	}

	void draw(sf::RenderTarget& target, const sf::RenderStates state) const override
	{
		target.draw(shape, rs);
	}

	T shape;
	sf::RenderStates rs;
};
