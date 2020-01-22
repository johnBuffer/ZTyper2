#pragma once

#include <SFML/Graphics.hpp>


struct Drawable
{
	virtual void draw(sf::RenderTarget& target) const {};
};
