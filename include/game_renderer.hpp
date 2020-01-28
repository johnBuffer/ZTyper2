#pragma once

#include <SFML/Graphics.hpp>
#include <dynamic_blur.hpp>
#include <vector>
#include <memory>


struct RenderLayer
{
	using DrawablePtr = std::shared_ptr<sf::Drawable>;
	std::vector<DrawablePtr> drawables;

	void render(sf::RenderTarget& target) const;
};


struct GameRenderer
{
	enum RenderTarget
	{
		Ground = 0,
		Bloom = 1,
		Default = 2,
	};

	GameRenderer(uint32_t win_width, uint32_t win_height);
	uint64_t addLayer();
	void setGroundTexture(const sf::Texture& texture);
	void addDrawable(RenderLayer::DrawablePtr drawable, uint64_t layer_id = 2U);
	void render(sf::RenderTarget& target) const;
	void clear();

	std::vector<RenderLayer> layers;

private:
	const sf::Texture* ground_texture;
	mutable sf::RenderTexture ground;
	mutable sf::RenderTexture bloom;
	mutable Blur blur;

	void renderGround(sf::RenderTarget& target) const;
	void renderBloom(sf::RenderTarget& target) const;
};
