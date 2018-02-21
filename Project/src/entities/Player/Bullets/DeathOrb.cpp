#include "Entities\Player\Bullets\DeathOrb.h"

const float bullets::DeathOrb::s_FIRE_RATE = 0.15f;

/// <summary>
/// @brief this is the default constructor.
/// 
/// 
/// </summary>
bullets::DeathOrb::DeathOrb()
	: Bullet()
	, m_damage(0.1f)
	, m_IMPACT(false)
{
	m_speed = 14.0f * 60.0f;
	m_velocity.y = -m_speed;
	m_angle = -90.0f;

	//different size to parent
	m_bulletRect.setSize(sf::Vector2f(50.0f, 50.0f));
	m_bulletRect.setOrigin(m_bulletRect.getSize().x / 2, m_bulletRect.getSize().y / 2);

	m_type = BulletTypes::DeathOrb;
	
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
	m_position += m_velocity * UPDATE_DT;
	m_bulletRect.setPosition(m_position.x, m_position.y);
	updateBox();
	tempRect.setPosition(m_bulletC2Rect.min.x, m_bulletC2Rect.min.y);
	tempRect.setSize(sf::Vector2f(m_bulletC2Rect.max.x - m_bulletC2Rect.min.x, m_bulletC2Rect.max.y - m_bulletC2Rect.min.y));
}

/// <summary>
/// @brief get the damage of this bullet.
/// 
/// 
/// </summary>
/// <returns>defines value of damage as float.</returns>
const float & bullets::DeathOrb::getDamage()
{
	return m_damage;
}

/// <summary>
/// @brief Death Orb never enters impact state.
/// 
/// 
/// </summary>
/// <returns>always false.</returns>
bool const & bullets::DeathOrb::isImpact() const
{
	return m_IMPACT;
}
