#include "Scenes\GameScene\Ship.h"


/// <summary>
/// @brief Default constructor.
/// 
/// 
/// </summary>
Ship::Ship()
	: m_shipRect()
{
	m_shipRect.setFillColor(sf::Color::Red);
	m_shipRect.setPosition(sf::Vector2f(100.0f, 400.0f));
	m_shipRect.setSize(sf::Vector2f(100.0f, 50.0f));
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
