#include "Scenes\GameScene\Bullets\Empowered.h"

const float bullets::Empowered::s_FIRE_RATE = 1.0f;

/// <summary>
/// @brief default constructor
/// 
/// 
/// </summary>
/// <param name="angle">angle at which the bullet will fire</param>
bullets::Empowered::Empowered()
	: Bullet()
{
	m_speed = 6.0f * 60.0f;
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


