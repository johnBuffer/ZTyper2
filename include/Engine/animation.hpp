#pragma once

#include <SFML/Graphics.hpp>


struct Animation
{
	Animation();
	Animation(const sf::Texture& texture_, uint32_t width_, uint32_t height_, uint32_t count_, bool loop_ = true);

	void applyOn(sf::RectangleShape& shape, float time) const;
	void applyOn(std::shared_ptr<sf::RectangleShape> shape, float time) const;

	uint32_t width;
	uint32_t height;
	uint32_t count;
	const sf::Texture* texture;
	sf::Vector2u texture_size;
	sf::Vector2u tile_size;
	bool loop;
};
