#include "Engine/resources_manager.hpp"


ResourcesManager::~ResourcesManager()
{
	clear();
}

ResourcesManager::ID ResourcesManager::registerTexture(const std::string& filename)
{
	textures.emplace_back();
	textures.back().loadFromFile(filename);

	return textures.size() - 1;
}

ResourcesManager::ID ResourcesManager::registerFont(const std::string& filename)
{
	fonts.emplace_back();
	fonts.back().loadFromFile(filename);

	return fonts.size() - 1;
}

void ResourcesManager::clear()
{
	textures.clear();
	fonts.clear();
}

const sf::Texture& ResourcesManager::getTexture(ID texture_id) const
{
	return textures[texture_id];
}

const sf::Font& ResourcesManager::getFont(ID font_id) const
{
	return fonts[font_id];
}
