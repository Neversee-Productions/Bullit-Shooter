#include "Entities\Player\Connector.h"

/// <summary>
/// @brief Default constructor.
/// 
/// 
/// </summary>
Connector::Connector(bool flipped)
	: m_CLEAR_COLOR(sf::Color::Transparent)
	, m_THICKNESS(20.0f)
	, m_sprite({20.0f, 100.0f})
	, m_shader(nullptr)
	, m_timer()
	, m_renderState()
	, m_shaderTexture()
	, m_shaderQuad()
	, m_FLIPPED(flipped)
{
	////////////////////////////////
	// Initializing shader texture
	////////////////////////////////
	auto const & shaderSize = static_cast<sf::Vector2u>(m_sprite.getSize() * 10.0f);
	m_shaderTexture.create(shaderSize.x, shaderSize.y);
	m_shaderTexture.setRepeated(true);
	m_shaderTexture.setSmooth(true);
	m_shaderTexture.clear(m_CLEAR_COLOR);

	////////////////////////////////
	// Initializing sprite
	////////////////////////////////
	m_sprite.setOrigin(m_THICKNESS / 2.0f, 0.0f);
	m_sprite.setTexture(&m_shaderTexture.getTexture(), true);
	

	////////////////////////////////
	// Initialize shader quad
	////////////////////////////////
	m_shaderQuad.setSize(m_sprite.getSize() * 10.0f);
	m_shaderQuad.setPosition(0.0f, 0.0f);
	m_shaderQuad.setFillColor(sf::Color(255u, 255u, 255u, 255u));
	m_shaderQuad.setOutlineColor(sf::Color(0u, 0u, 0u, 0u));
}

/// <summary>
/// @brief Initialize connector.
/// 
/// Resources have been loaded, perform post-asset loading
/// operations.
/// </summary>
/// <param name="resources">Defines shared pointer to our loaded resources.</param>
void Connector::init(std::shared_ptr<Resources> resources)
{
	if (!m_shader)
	{
		m_shader = resources->m_sptrCnShader;
	}
	m_renderState.shader = m_shader.get();
}

/// <summary>
/// @brief Update Connector.
/// 
/// 
/// </summary>
void Connector::update(sf::Vector2f const & startPos, sf::Vector2f const & endPos)
{
	auto const & direction = endPos - startPos;
	m_sprite.setPosition(startPos);
	auto const & length = thor::length(direction);
	auto const & size = sf::Vector2f(m_THICKNESS, length);
	m_sprite.setSize(size);
	m_sprite.setRotation(thor::polarAngle(direction) - 90.0f);
}

/// <summary>
/// @brief Draw connector.
/// 
/// 
/// </summary>
/// <param name="window">target window.</param>
/// <param name="deltaTime">draw delta time.</param>
void Connector::draw(Window & window, float const & deltaTime)
{
	if (m_FLIPPED)
	{
		m_timer -= sf::seconds(deltaTime);
		m_shader->setUniform("time", m_timer.asSeconds());
	}
	else
	{
		m_timer += sf::seconds(deltaTime);
		m_shader->setUniform("time", m_timer.asSeconds());
	}
	m_shader->setUniform("resolution", m_shaderQuad.getSize());
	m_shaderTexture.clear(m_CLEAR_COLOR);
	m_shaderTexture.draw(m_shaderQuad, m_renderState);
	m_shaderTexture.display();
	window.draw(m_sprite);
}
