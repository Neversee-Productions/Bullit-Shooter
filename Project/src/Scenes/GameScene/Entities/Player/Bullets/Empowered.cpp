#include "Scenes\GameScene\Entities\Player\Bullets\Empowered.h"

const float bullets::Empowered::s_FIRE_RATE = 1.0f;

/// <summary>
/// @brief default constructor
/// 
/// 
/// </summary>
/// <param name="angle">angle at which the bullet will fire</param>
bullets::Empowered::Empowered()
	: Bullet()
	, m_damage(1.4f)
{
	m_speed = 10.0f * 60.0f;
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


