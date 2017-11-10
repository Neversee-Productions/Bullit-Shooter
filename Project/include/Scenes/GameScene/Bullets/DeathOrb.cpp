#include "DeathOrb.h"

const float bullets::DeathOrb::s_FIRE_RATE = 0.5f;

/// <summary>
/// @brief this is the default constructor.
/// 
/// 
/// </summary>
bullets::DeathOrb::DeathOrb()
	: Bullet()
{
	m_speed = 4.0f;
	m_velocity.x = m_speed;

	//different size to parent
	m_bulletRect.setSize(sf::Vector2f(10.0f, 10.0f));
	
	//change collision rectangle
	updateBox();
}

/// <summary>
/// @Static method to return a fire rate.
/// 
/// 
/// </summary>
/// <returns>value of fire rate</returns>
float bullets::DeathOrb::getFireRate()
{
	return s_FIRE_RATE;
}

/// <summary>
/// @brief update collisions and movement
/// 
/// 
/// </summary>
void bullets::DeathOrb::update()
{
	m_position += m_velocity;
	m_bulletRect.setPosition(m_position.x, m_position.y);
	updateBox();
}
