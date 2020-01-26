#pragma once

#include <SFML/Graphics.hpp>
#include <vector>


struct ResourcesManager
{
	using ID = uint64_t;

	ID registerTexture(const std::string& filename);
	ID registerFont(const std::string& filename);

	const sf::Texture& getTexture(ID texture_id) const;
	const sf::Font& getFont(ID font_id = 0U) const;

	std::vector<sf::Texture> textures;
	std::vector<sf::Font> fonts;
};
