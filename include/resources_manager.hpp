#pragma once

#include <SFML/Graphics.hpp>
#include <vector>


struct ResourcesManager
{
	using ID = uint64_t;

	ID registerTexture(const std::string& filename);

	const sf::Texture& getTexture(ID texture_id) const;

	std::vector<sf::Texture> textures;
};
