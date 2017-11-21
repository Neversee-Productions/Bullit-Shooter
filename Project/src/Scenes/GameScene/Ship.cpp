#include "Scenes\GameScene\Ship.h"


/// <summary>
/// @brief Default constructor.
/// 
/// 
/// </summary>
Ship::Ship()
	: m_shipRect()
	, m_speed(4.0f)
	, m_position(sf::Vector2f(100.0f, 400.0f))
{
	m_shipRect.setFillColor(sf::Color::Red);
	m_shipRect.setPosition(m_position);
	m_shipRect.setSize(sf::Vector2f(50.0f, 25.0f));
	m_shipRect.setOrigin(m_shipRect.getSize().x / 2, m_shipRect.getSize().y / 2);
}

/// <summary>
/// @brief Render entities.
/// 
/// 
/// </summary>
/// <param name="window">define reference to our target Window.</param>
/// <param name="deltaTime">define reference to draw time step.</param>
void Ship::draw(Window & window, const float & deltaTime)
{
	window.draw(m_shipRect);
}

/// <summary>
/// @brief simple method that moves the player up.
/// 
/// 
/// </summary>
void Ship::moveUp()
{
	m_position.y -= m_speed;
}

/// <summary>
/// @brief sumple method that moves the player down.
/// 
/// 
/// </summary>
void Ship::moveDown()
{
	m_position.y += m_speed;
}

/// <summary>
/// @brief update position.
/// 
/// 
/// </summary>
void Ship::update()
{
	m_shipRect.setPosition(m_position);
}

/// <summary>
/// @brief return the position of the ship rectangle.
/// 
/// 
/// </summary>
/// <returns>returns the ship rectangles position</returns>
const sf::Vector2f & Ship::getShipRect()
{
	return m_shipRect.getPosition();
}


