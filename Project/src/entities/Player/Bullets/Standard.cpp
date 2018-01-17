#include "Entities\Player\Bullets\Standard.h"

const float bullets::Standard::s_FIRE_RATE = 0.5f;

/// <summary>
/// @brief this is the default constructor.
/// 
/// 
/// </summary>
bullets::Standard::Standard()
	: Bullet()
	, m_damage(1.5f)
{
	m_speed = 10.0f * 60.0f;
	m_velocity.y = -m_speed;
	m_angle = -90.0f;
}

/// <summary>
/// @brief response to bullet hitting a entity.
/// 
/// Standard bullet will generate a impact animation
/// </summary>
void bullets::Standard::hit()
{
	// TODO: Figure out impact animation playing.
	// Impact animation needs to play a sprite sheet
	//  animation at the impact spot (will use position of bullet)
	//  this impact sprite needs to persist (DIFFICULT PART)
	Bullet::hit();
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

/// <summary>
/// @brief get the damage of this bullet.
/// 
/// 
/// </summary>
/// <returns>defines value of damage as float.</returns>
const float & bullets::Standard::getDamage()
{
	return m_damage;
}
