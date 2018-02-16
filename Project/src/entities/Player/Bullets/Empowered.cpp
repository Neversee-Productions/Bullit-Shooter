#include "Entities\Player\Bullets\Empowered.h"

const float bullets::Empowered::s_FIRE_RATE = 0.5f;

/// <summary>
/// @brief default constructor
/// 
/// 
/// </summary>
bullets::Empowered::Empowered()
	: Bullet()
	, m_damage(1.5f)
{
	m_bulletRect.setSize(sf::Vector2f(25.0f, 25.0f));
	m_bulletRect.setOrigin(m_bulletRect.getSize().x / 2, m_bulletRect.getSize().y / 2);
	
	updateBox();
	m_speed = 11.0f * 60.0f;

	m_type = BulletTypes::Empowered;
}

/// <summary>
/// @Static method to return a fire rate.
/// 
/// 
/// </summary>
/// <returns>value of fire rate</returns>
float bullets::Empowered::getFireRate()
{
	return s_FIRE_RATE;
}

/// <summary>
/// @brief get the damage of this bullet.
/// 
/// 
/// </summary>
/// <returns>defines value of damage as float.</returns>
const float & bullets::Empowered::getDamage()
{
	return m_damage;
}


