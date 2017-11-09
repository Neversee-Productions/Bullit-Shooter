#include "Scenes\GameScene\Bullets\HolySphere.h"

const float bullets::HolySphere::s_FIRE_RATE = 0.5f;

/// <summary>
/// @brief this is the default constructor.
/// 
/// 
/// </summary>
bullets::HolySphere::HolySphere()
	: Bullet()
{
	m_speed = 16.0f;
	m_velocity.x = m_speed;

	//different size to parent
	m_bulletRect.setSize(sf::Vector2f(5.0f, 5.0f));

	//change collision rectangle
	const auto & bulletRect = m_bulletRect.getGlobalBounds();
	m_bulletC2Rect.min.x = bulletRect.left;
	m_bulletC2Rect.min.y = bulletRect.top;
	m_bulletC2Rect.max.x = bulletRect.left + bulletRect.width;
	m_bulletC2Rect.max.y = bulletRect.top + bulletRect.height;
}

/// <summary>
/// @brief update position and velocity.
/// 
/// Also updates the size, when a max size reached stop scaling
/// after 3 seconds the bullet should disappear
/// </summary>
void bullets::HolySphere::update()
{
	m_position += m_velocity;
	m_bulletRect.setPosition(m_position.x, m_position.y);
	if (m_bulletRect.getSize() != sf::Vector2f(15.0f,15.0f))
	{
		m_bulletRect.setSize(m_bulletRect.getSize() + sf::Vector2f(0.8f, 0.8f));
	}
	updateBox();
}

/// <summary>
/// @brief this is the default constructor.
/// 
/// 
/// </summary>
float bullets::HolySphere::getFireRate()
{
	return s_FIRE_RATE;
}

/// <summary>
/// @brief overloaded set active method.
/// 
/// This method will check if active is being set to false
/// if yes then reset sphere to original size.
/// </summary>
/// <param name="active">determines the active state of bullet</param>
void bullets::HolySphere::setActive(bool active)
{
	if (active == false)
	{
		m_bulletRect.setSize(sf::Vector2f(sf::Vector2f(5.0f, 5.0f)));
	}
	m_active = active;
}
