#include "Scenes\GameScene\Bullets\NapalmSphere.h"

const float bullets::NapalmSphere::s_FIRE_RATE = 0.5f;
const sf::Vector2f bullets::NapalmSphere::s_DEFAULT_SIZE = sf::Vector2f(10.0f, 10.0f);

/// <summary>
/// @brief Default constructor.
/// 
/// 
/// </summary>
bullets::NapalmSphere::NapalmSphere()
	: Bullet()
	, m_explode(false)
	, m_timeAlive(0.0f)
{
	m_speed = 8.0f * 60.0f;
	//updateVelocityVector();
	m_velocity.y = -m_speed;

	//different size to parent
	m_bulletRect.setSize(s_DEFAULT_SIZE);
	m_bulletRect.setOrigin(m_bulletRect.getSize().x / 2, m_bulletRect.getSize().y / 2);

	updateBox();
}

/// <summary>
/// @Static method to return a fire rate.
/// 
/// 
/// </summary>
/// <returns>value of fire rate</returns>
float bullets::NapalmSphere::getFireRate()
{
	return s_FIRE_RATE;
}

/// <summary>
/// @brief Update position and velocity.
/// 
/// On impact sphere of fire remains in place
/// causing damage over time.
/// </summary>
void bullets::NapalmSphere::update()
{
	if (!m_explode)
	{
		Bullet::update();
	}
	else
	{
		m_bulletRect.setSize(sf::Vector2f(20.0f, 20.0f));
		m_bulletRect.setOrigin(m_bulletRect.getSize().x / 2, m_bulletRect.getSize().y / 2);
		updateBox();
		m_timeAlive += App::getUpdateDeltaTime();
		if (m_timeAlive >= 3.0f)
		{
			setActive(false);
		}
	}
	tempRect.setPosition(m_bulletC2Rect.min.x, m_bulletC2Rect.min.y);
	tempRect.setSize(sf::Vector2f(m_bulletC2Rect.max.x - m_bulletC2Rect.min.x, m_bulletC2Rect.max.y - m_bulletC2Rect.min.y));
}

/// <summary>
/// @brief overloaded set active method.
/// 
/// this will reset the m_moving to true as well
/// as resetting the time alive to 0
/// </summary>
/// <param name="active"></param>
void bullets::NapalmSphere::setActive(bool active)
{
	if (active == false)
	{
		m_timeAlive = 0.0f;
		m_bulletRect.setSize(s_DEFAULT_SIZE);
		m_bulletRect.setOrigin(m_bulletRect.getSize().x / 2, m_bulletRect.getSize().y / 2);
		m_explode = false;
	}
	m_active = active;
}

/// <summary>
/// @brief this method simply sets explode bool to true.
/// 
/// 
/// </summary>
/// <param name="check">Defines the new explode bool value</param>
void bullets::NapalmSphere::explode(bool check)
{
	m_explode = check;
}

