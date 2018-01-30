#include "Entities\Background.h"

/// <summary>
/// @brief Default constructor.
/// 
/// 
/// </summary>
Background::Background()
	: m_DELTA_TIME(App::getUpdateDeltaTime())
	, m_bgColor(sf::Color::Black)
	, m_bgTargetColor(sf::Color::Black)
	, m_COLOR_CHANGE(0.5f)
	, m_image(static_cast<sf::Vector2f>(App::getViewSize()))
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
	this->interpolate(m_bgColor.x, m_bgTargetColor.x);
	this->interpolate(m_bgColor.y, m_bgTargetColor.y);
	this->interpolate(m_bgColor.z, m_bgTargetColor.z);
	this->interpolate(m_bgColor.w, m_bgTargetColor.w);
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
	m_shader->setUniform("color", m_bgColor);
	window.draw(m_image, m_renderState);
}

/// <summary>
/// @brief Set new target color for background to fade into.
/// 
/// 
/// </summary>
/// <param name="newColor">new target color.</param>
void Background::setTargetColor(sf::Color const & newColor)
{
	// Converts sf::Color to sf::GlSl::Vec4
	m_bgTargetColor = static_cast<sf::Glsl::Vec4>(newColor);
}

/// <summary>
/// @brief Interpolates value towards target value.
/// 
/// 
/// </summary>
/// <param name="value">reference to the value that will be changed.</param>
/// <param name="targetValue">read-only reference to the target value.</param>
void Background::interpolate(float & value, float const & targetValue)
{
	auto const DELTA_VALUE = (targetValue - value) * m_COLOR_CHANGE * m_DELTA_TIME;
	if (value < targetValue - DELTA_VALUE || value > targetValue + DELTA_VALUE)
	{
		value += DELTA_VALUE;
	}
	else
	{
		value = targetValue;
	}
}
