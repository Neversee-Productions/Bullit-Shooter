#include "Scenes\GameScene\Bullets\Standard.h"

const float bullets::Standard::s_FIRE_RATE = 0.5f;

/// <summary>
/// @brief this is the default constructor.
/// 
/// 
/// </summary>
bullets::Standard::Standard()
	: Bullet()
{
	m_speed = 8.0f;
	m_velocity.x = m_speed;
}

/// <summary>
/// @Static method to return a fire rate.
/// 
/// 
/// </summary>
/// <returns>value of fire rate</returns>
float bullets::Standard::getFireRate()
{
	return s_FIRE_RATE;
}
