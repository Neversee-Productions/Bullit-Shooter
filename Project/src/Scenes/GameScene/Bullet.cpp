#include "Scenes\GameScene\Bullet.h"

/// <summary>
/// @brief Default constructor.
/// 
/// 
/// </summary>
Bullet::Bullet()
	: m_position(0.0f,0.0f)
	, m_bulletRect()
{
}

/// <summary>
/// @brief overloaded constructor.
/// 
/// 
/// </summary>
/// <param name="position"></param>
Bullet::Bullet(sf::Vector2f position)
	: m_position(position)
	, m_bulletRect()
{
	m_bulletRect.setPosition(position);
	m_bulletRect.setFillColor(sf::Color::White);
	m_bulletRect.setSize(sf::Vector2f(10.0f, 10.0f));
	m_bulletRect.setOrigin(m_bulletRect.getSize().x / 2, m_bulletRect.getSize().y / 2);
}

/// <summary>
/// @brief Render entities.
/// 
/// 
/// </summary>
/// <param name="window">define reference to our target Window.</param>
/// <param name="deltaTime">define reference to draw time step.</param>
void Bullet::draw(Window & window, const float & deltaTime)
{
	window.draw(m_bulletRect);
}

