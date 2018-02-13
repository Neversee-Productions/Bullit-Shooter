#include "Entities\Player\Bullets\CometShot.h"

const float bullets::CometShot::s_FIRE_RATE = 0.2f;
const float bullets::CometShot::s_KNOCK_BACK = 40.0f;

/// <summary>
/// @brief Default constructor.
/// 
/// 
/// </summary>
bullets::CometShot::CometShot()
	: Bullet()
	, m_damage(1.0f)
{
	m_speed = 12.0f * 60.0f;
	m_velocity.y = -m_speed;
	m_angle = -90.0f;

	//different size to parent
	m_bulletRect.setSize(sf::Vector2f(60.0f, 25.0f));
	m_bulletRect.setOrigin(m_bulletRect.getSize().x / 2, m_bulletRect.getSize().y / 2);

	m_type = BulletTypes::CometShot;

	//change collision rectangle
	updateBox();
}

/// <summary>
/// @Static method to return a fire rate.
/// 
/// 
/// </summary>
/// <returns>value of fire rate</returns>
float bullets::CometShot::getFireRate()
{
	return s_FIRE_RATE;
}

/// <summary>
/// @brief Update velocity and position.
/// 
/// 
/// </summary>
void bullets::CometShot::update()
{
	Bullet::update();
}

/// <summary>
/// @brief get the damage of this bullet.
/// 
/// 
/// </summary>
/// <returns>defines value of damage as float.</returns>
const float & bullets::CometShot::getDamage()
{
	return m_damage;
}

