#include "Scenes\GameScene\Entities\Background.h"

/// <summary>
/// @brief Default constructor.
/// 
/// 
/// </summary>
Background::Background()
	: m_image(static_cast<sf::Vector2f>(App::getViewSize()))
	, m_shader(nullptr)
	, m_timer(nullptr)
	, m_renderState()
{
}

/// <summary>
/// @brief Initialize background.
/// 
/// Resources have been loaded, perform post-asset loading
/// operations.
/// </summary>
/// <param name="resources">Defines shared pointer to our loaded resources.</param>
void Background::init(std::shared_ptr<Resources> resources)
{
	if (!m_shader)
	{
		m_shader = resources->m_sptrBgShader;
	}
	m_renderState.shader = m_shader.get();

	if (!m_timer)
	{
		m_timer = std::make_unique<sf::Clock>();
	}
}

/// <summary>
/// @brief Update background.
/// 
/// 
/// </summary>
void Background::update()
{
}

/// <summary>
/// @brief Draw background.
/// 
/// 
/// </summary>
/// <param name="window">target window.</param>
/// <param name="deltaTime">draw delta time.</param>
void Background::draw(Window & window, const float & deltaTime)
{
	m_shader->setUniform("time", m_timer->getElapsedTime().asSeconds());
	window.draw(m_image, m_renderState);
}
