#include "Entities\Player\Bullets\FireBlast.h"

const float bullets::FireBlast::s_FIRE_RATE = 0.1f;

/// <summary>
/// @brief this is the default constructor.
/// 
/// 
/// </summary>
bullets::FireBlast::FireBlast()
	: Bullet()
	, m_damage(0.8f)
{
	m_speed = 20.0f * 60.0f;
	m_velocity.y = -m_speed;
	m_angle = -90.0f;

	//different size to parent
	m_bulletRect.setSize(sf::Vector2f(40.0f, 30.0f));
	m_bulletRect.setOrigin(m_bulletRect.getSize().x / 2, m_bulletRect.getSize().y / 2);

	//change collision rectangle
	updateBox();
}

/// <summary>
/// @brief this is the default constructor.
/// 
/// 
/// </summary>
float bullets::FireBlast::getFireRate()
{
	return s_FIRE_RATE;
}

/// <summary>
/// @brief get the damage of this bullet.
/// 
/// 
/// </summary>
/// <returns>defines value of damage as float.</returns>
const float & bullets::FireBlast::getDamage()
{
	return m_damage;
}

