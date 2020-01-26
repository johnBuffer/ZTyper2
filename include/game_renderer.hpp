#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>


struct RenderLayer
{
	using DrawablePtr = std::shared_ptr<sf::Drawable>;
	std::vector<DrawablePtr> drawables;
};


struct GameRenderer
{
	GameRenderer();
	uint64_t addLayer();
	void addDrawable(RenderLayer::DrawablePtr drawable, uint64_t layer_id = 0U);
	void render(sf::RenderTarget& target) const;
	void clear();

	std::vector<RenderLayer> layers;
};
