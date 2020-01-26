#include "..\include\game_renderer.hpp"


GameRenderer::GameRenderer(uint32_t win_width, uint32_t win_height)
{
	// Adding default layer
	addLayer();
	// Adding ground layer
	addLayer();
	// Adding bloom layer
	addLayer();
	// Initialize ground texture
	ground.create(win_width, win_height);
	ground.clear(sf::Color::Black);
	// Initialize bloom texture
	bloom.create(win_width, win_height);
	bloom.clear(sf::Color::Black);
}

uint64_t GameRenderer::addLayer()
{
	layers.emplace_back();
	return layers.size() - 1;
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
}

void GameRenderer::clear()
{
	for (RenderLayer& layer : layers) {
		layer.drawables.clear();
	}
}

void GameRenderer::renderGround(sf::RenderTarget& target) const
{
	layers[RenderTarget::Ground].render(ground);
	ground.display();
	target.draw(sf::Sprite(ground.getTexture()));
}

void RenderLayer::render(sf::RenderTarget& target) const
{
	for (RenderLayer::DrawablePtr shape : drawables) {
		target.draw(*shape);
	}
}
