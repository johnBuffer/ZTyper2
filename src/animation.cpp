#include "..\include\animation.hpp"
#include <iostream>


Animation::Animation()
	: texture(nullptr)
{
}

Animation::Animation(const sf::Texture& texture_, uint32_t width_, uint32_t height_, uint32_t count_, bool loop_)
	: texture(&texture_)
	, width(width_)
	, height(height_)
	, count(count_)
	, texture_size(texture_.getSize())
	, loop(loop_)
{
	tile_size = sf::Vector2u(texture_size.x / width, texture_size.y / height);
}

void Animation::applyOn(sf::RectangleShape& shape, float time) const
{
	const uint32_t index = loop ? uint32_t(time)%count : static_cast<uint32_t>(std::min((float)count, time));

	const uint32_t tile_x = index % width;
	const uint32_t tile_y = index / width;

	shape.setTexture(texture);
	shape.setTextureRect(sf::IntRect(tile_x * tile_size.x, tile_y * tile_size.y, tile_size.x, tile_size.y));
}

void Animation::applyOn(std::shared_ptr<sf::RectangleShape> shape, float time) const
{
	applyOn(*shape, time);
}
