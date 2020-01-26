#include "..\include\game_renderer.hpp"


GameRenderer::GameRenderer()
{
	// Adding default layer
	addLayer();
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
	for (const RenderLayer& layer : layers) {
		for (RenderLayer::DrawablePtr shape : layer.drawables) {
			target.draw(*shape);
		}
	}
}

void GameRenderer::clear()
{
	for (RenderLayer& layer : layers) {
		layer.drawables.clear();
	}
}
