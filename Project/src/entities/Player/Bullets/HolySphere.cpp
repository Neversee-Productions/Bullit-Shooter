#include "Entities\Player\Bullets\HolySphere.h"

const float bullets::HolySphere::s_FIRE_RATE = 1.0f;
const float bullets::HolySphere::s_MAX_SIZE = 120.0f;
const sf::Vector2f bullets::HolySphere::s_SIZE_CHANGE = sf::Vector2f(3.0f, 3.0f);
const sf::Vector2f bullets::HolySphere::s_DEFAULT_SIZE = sf::Vector2f(10.0f, 10.0f);
const float bullets::HolySphere::s_DEF_TTL = 1.0f;
const float bullets::HolySphere::s_ALPHA_DECREASE = 10.0f;
const float bullets::HolySphere::s_MIN_ALPHA = 5.0f;



/// <summary>
/// @brief this is the default constructor.
/// 
/// 
/// </summary>
bullets::HolySphere::HolySphere()
	: Bullet()
	, m_timeToLive(s_DEF_TTL)
	, m_alpha(255.0f)
	, m_damage(0.2f)
{
	m_speed = 4.5f * 60.0f;
	m_velocity.y = -m_speed;
	m_angle = -90.0f;

	//different size to parent
	m_bulletRect.setSize(s_DEFAULT_SIZE);
	m_bulletRect.setOrigin(m_bulletRect.getSize().x / 2, m_bulletRect.getSize().y / 2);

	m_type = BulletTypes::HolySphere;

	updateBox();
}

/// <summary>
/// @brief update position and velocity.
/// 
/// Also updates the size, when a max size reached stop scaling
/// after 3 seconds the bullet should disappear
/// </summary>
void bullets::HolySphere::update()
{
	//decrease time to live
	m_timeToLive -= UPDATE_DT;
	m_position += m_velocity * UPDATE_DT;
	m_bulletRect.setPosition(m_position.x, m_position.y);
	//if not max size increase the size
	if (m_bulletRect.getSize().x <= s_MAX_SIZE)
	{
		m_bulletRect.setSize(m_bulletRect.getSize() + s_SIZE_CHANGE);
		m_bulletRect.setOrigin(m_bulletRect.getSize().x / 2, m_bulletRect.getSize().y / 2);
	}
	if (m_timeToLive <= 0.0f)
	{
		m_alpha -= s_ALPHA_DECREASE;
		m_bulletRect.setFillColor(sf::Color(255u, 255u, 255u, static_cast<sf::Uint8>(m_alpha)));
		if (m_alpha < s_MIN_ALPHA)
		{
			setActive(false);
		}
	}
	tempRect.setPosition(m_bulletC2Rect.min.x, m_bulletC2Rect.min.y);
	tempRect.setSize(sf::Vector2f(m_bulletC2Rect.max.x - m_bulletC2Rect.min.x, m_bulletC2Rect.max.y - m_bulletC2Rect.min.y));
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
		m_bulletRect.setSize(s_DEFAULT_SIZE);
		m_bulletRect.setOrigin(m_bulletRect.getSize().x / 2, m_bulletRect.getSize().y / 2);
		m_timeToLive = s_DEF_TTL;
		m_alpha = 255.0f;
	}
	m_active = active;
}

/// <summary>
/// @brief get the damage of this bullet.
/// 
/// 
/// </summary>
/// <returns>defines value of damage as float.</returns>
const float & bullets::HolySphere::getDamage()
{
	return m_damage;
}
