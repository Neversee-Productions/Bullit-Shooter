#include "Scenes\GameScene\Asteroid.h"


/// <summary>
/// @brief Default constructor.
/// 
/// 
/// </summary>
Asteroid::Asteroid()
	: m_rectangle(sf::Vector2f(200.0f, 200.0f))
	, m_circle(10.0f)
	, m_velocity(0.0f, 0.0f)
	, m_position(300.0f,300.0f)
	, m_active(false)
{
	m_rectangle.setOrigin(m_rectangle.getGlobalBounds().width / 2, m_rectangle.getGlobalBounds().height / 2);
	m_rectangle.setPosition(m_position);
	m_circle.setFillColor(sf::Color::Red);
	m_circle.setPosition(m_position);
	m_circle.setRadius(m_rectangle.getGlobalBounds().width / 2);
	m_circle.setOrigin(m_rectangle.getOrigin());
}

/// <summary>
/// @brief update position based on velocity.
/// 
/// 
/// </summary>
void Asteroid::update()
{
	if (m_active)
	{
		m_position += m_velocity;
		m_rectangle.setPosition(m_position);
		m_circle.setPosition(m_position);
	}
}

/// <summary>
/// @brief Draw if active.
/// 
/// 
/// </summary>
/// <param name="window">reference to the window</param>
/// <param name="deltaTime">constant reference to delta time</param>
void Asteroid::draw(Window & window, const float & deltaTime)
{
	if (m_active)
	{
		window.draw(m_rectangle);
		window.draw(m_circle);
	}
}

/// <summary>
/// @brief sets the velocity of the asteroid.
/// 
/// 
/// </summary>
void Asteroid::setVelocity(sf::Vector2f vel)
{
	m_velocity = vel;
}

/// <summary>
/// @brief Sets active of asteroid to passed parameter.
/// 
/// 
/// </summary>
/// <param name="active">new value of m_active</param>
void Asteroid::setActive(bool active)
{
	m_active = active;
}

