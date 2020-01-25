#include "..\include\resources_manager.hpp"


ResourcesManager::ID ResourcesManager::registerTexture(const std::string& filename)
{
	textures.emplace_back();
	textures.back().loadFromFile(filename);

	return textures.size() - 1;
}

const sf::Texture& ResourcesManager::getTexture(ID texture_id) const
{
	return textures[texture_id];
}
