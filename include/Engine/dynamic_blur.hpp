#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>


constexpr char VERTEX_SHADER_SRC[] =
"void main()                                                  \
{                                                             \
	gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0; \
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;   \
}";

constexpr char FRAG_X_SHADER_SRC[] =
"uniform sampler2D texture;                                   \
uniform float WIDTH;                                          \
float WIDTH_STEP = 1.0 / WIDTH;                               \
void main()                                                   \
{                                                             \
	vec2 pos = gl_TexCoord[0].xy;                             \
	vec2 offset = vec2(WIDTH_STEP, 0.0);                      \
	vec4 color = texture2D(texture, pos) * 0.25;              \
	color += texture2D(texture, pos + offset * 1.0) * 0.188;  \
	color += texture2D(texture, pos + offset * 2.0) * 0.141;  \
	color += texture2D(texture, pos + offset * 3.0) * 0.105;  \
	color += texture2D(texture, pos - offset * 1.0) * 0.188;  \
	color += texture2D(texture, pos - offset * 2.0) * 0.141;  \
	color += texture2D(texture, pos - offset * 3.0) * 0.105;  \
	gl_FragColor = vec4(color.xyz, 1.0);                      \
}";

constexpr char FRAG_Y_SHADER_SRC[] =
"uniform sampler2D texture;                                   \
uniform float HEIGHT;                                         \
float HEIGHT_STEP = 1.0 / HEIGHT;                             \
void main()                                                   \
{                                                             \
	vec2 pos = gl_TexCoord[0].xy;                             \
	vec2 offset = vec2(0.0, HEIGHT_STEP);                     \
	vec4 color = texture2D(texture, pos) * 0.27;              \
	color += texture2D(texture, pos + offset * 1.0) * 0.188;  \
	color += texture2D(texture, pos + offset * 2.0) * 0.141;  \
	color += texture2D(texture, pos + offset * 3.0) * 0.105;  \
	color += texture2D(texture, pos - offset * 1.0) * 0.188;  \
	color += texture2D(texture, pos - offset * 2.0) * 0.141;  \
	color += texture2D(texture, pos - offset * 3.0) * 0.105;  \
	gl_FragColor = vec4(color.xyz, 1.0);                      \
}";

class Blur
{
public:
    Blur(sf::Vector2u render_size, int32_t iterations, float quality = 1.0f)
        : m_render_size({static_cast<int32_t>(render_size.x * quality), static_cast<int32_t>(render_size.y * quality)})
        , m_iterations(iterations)
        , m_quality(quality)
    {
        createTextures();
        createShaders();
        m_result.setScale(1.0f / m_quality, 1.0f / m_quality);
    }

    sf::Sprite& apply(const sf::Texture& texture)
    {
        // Retrieve texture content and downscale it
        sf::Sprite sprite(texture);
        sprite.setScale(m_quality, m_quality);
        uint32_t current_buffer = 0;
        m_textures[current_buffer].draw(sprite);
        //current_buffer = blurIteration(current_buffer, 1);
        for (int32_t i(0); i<m_iterations; i += 1) {
            current_buffer = blurPass(current_buffer, i);
        }
        for (int32_t i(m_iterations); i >= 0; i -= 1) {
            current_buffer = blurPass(current_buffer, i);
        }
        m_textures[current_buffer].display();
        m_result.setTexture(m_textures[current_buffer].getTexture());
        return m_result;
    }

private:
    sf::Vector2i      m_render_size;
    int32_t           m_iterations;
    sf::RenderTexture m_textures[2];
    float             m_quality;

    // Shaders
    sf::Shader m_horizontal;
    sf::Shader m_vertical;
    sf::Sprite m_result;

    // Methods
    void createTextures()
    {
        // Initialize textures
        m_textures[0].create(m_render_size.x, m_render_size.y);
        m_textures[1].create(m_render_size.x, m_render_size.y);
        m_textures[0].setSmooth(true);
        m_textures[1].setSmooth(true);
        // Update clear
        m_textures[0].display();
        m_textures[1].display();
    }

    void createShaders()
    {
        m_horizontal.loadFromMemory(VERTEX_SHADER_SRC, FRAG_X_SHADER_SRC);
        m_vertical.loadFromMemory(VERTEX_SHADER_SRC, FRAG_Y_SHADER_SRC);
        // Set pixel steps in shader
        m_horizontal.setUniform("WIDTH", static_cast<float>(m_render_size.x));
        m_vertical.setUniform("HEIGHT", static_cast<float>(m_render_size.y));
    }

    void clear(uint32_t texture_id)
    {
        m_textures[texture_id].clear(sf::Color::Black);
    }

    void draw(const sf::Sprite& sprite, uint32_t dest_buffer, const sf::Shader& shader)
    {
        clear(dest_buffer);
        m_textures[dest_buffer].draw(sprite, &shader);
    }

    void draw(const sf::Sprite& sprite, uint32_t dest_buffer)
    {
        clear(dest_buffer);
        m_textures[dest_buffer].draw(sprite);
    }

    const sf::Texture& getTexture(uint32_t source_buffer)
    {
        return m_textures[source_buffer].getTexture();
    }

    uint32_t blurPass(uint32_t source_buffer, int32_t downscale)
    {
        // Initialize scales and rectangle
        const auto scale = static_cast<float>(std::pow(0.66f, downscale));
        const auto inv_scale = 1.0f / scale;
        const auto current_pass_size_x = static_cast<int32_t>(m_render_size.x * scale);
        const auto current_pass_size_y = static_cast<int32_t>(m_render_size.y * scale);
        // Draw from source to target with separate blur passes
        sf::Sprite sprite;
        sprite.setScale(scale, scale);
        sprite.setTexture(getTexture(source_buffer));
        draw(sprite, !source_buffer);

        sprite.setScale(1.0f, 1.0f);
        sprite.setTexture(getTexture(!source_buffer));
        sprite.setTextureRect({0, 0, current_pass_size_x, current_pass_size_y});
        draw(sprite, source_buffer, m_horizontal);

        sprite.setTexture(getTexture(source_buffer));
        draw(sprite, !source_buffer, m_vertical);

        const float safe_scale = 1.0f;
        sprite.setScale(inv_scale * safe_scale, inv_scale * safe_scale);
        sprite.setTexture(getTexture(!source_buffer));
        draw(sprite, source_buffer);

        return source_buffer;
    }
};
