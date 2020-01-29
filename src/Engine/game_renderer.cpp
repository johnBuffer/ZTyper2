#include "game_renderer.hpp"


GameRenderer::GameRenderer(uint32_t win_width, uint32_t win_height)
	: blur(win_width, win_height, 0.5f)
	, ground_texture(nullptr)
{
	// Adding default layer
	addLayer();
	// Adding ground layer
	addLayer();
	// Adding bloom layer
	addLayer();
	// Initialize ground texture
	ground.create(win_width, win_height);
	ground.clear(sf::Color(0, 0, 0, 0));
	// Initialize bloom texture
	bloom.create(win_width, win_height);
}

uint64_t GameRenderer::addLayer()
{
	layers.emplace_back();
	return layers.size() - 1;
}

void GameRenderer::setGroundTexture(const sf::Texture& texture)
{
	ground_texture = &texture;
}

void GameRenderer::addDrawable(RenderLayer::DrawablePtr drawable, uint64_t layer_id)
{
	layers[layer_id].drawables.push_back(drawable);
}

void GameRenderer::render(sf::RenderTarget& target) const
{
	// Render ground
	renderGround(target);
	// Render drawables
	for (uint32_t i(RenderTarget::Default); i < layers.size(); ++i) {
		const RenderLayer& layer = layers[i];
		layer.render(target);
	}
	// Render bloom
	renderBloom(target);
}

void GameRenderer::clear()
{
	for (RenderLayer& layer : layers) {
		layer.drawables.clear();
	}
}

void GameRenderer::renderGround(sf::RenderTarget& target) const
{
	if (ground_texture) {
		target.draw(sf::Sprite(*ground_texture));
	}
	const sf::Vector2u screen_size = ground.getSize();
	sf::RectangleShape cache(sf::Vector2f(float(screen_size.x), float(screen_size.y)));
	const uint8_t intensity = 250U;
	cache.setFillColor(sf::Color(intensity, intensity, intensity));
	ground.draw(cache, sf::BlendMultiply);
	layers[RenderTarget::Ground].render(ground);
	ground.display();
	target.draw(sf::Sprite(ground.getTexture()));
}

void GameRenderer::renderBloom(sf::RenderTarget& target) const
{
	bloom.clear();
	layers[RenderTarget::Bloom].render(bloom);
	bloom.display();
	target.draw(blur.apply(bloom.getTexture(), 1U), sf::BlendAdd);
}

void RenderLayer::render(sf::RenderTarget& target) const
{
	for (RenderLayer::DrawablePtr shape : drawables) {
		target.draw(*shape);
	}
}
