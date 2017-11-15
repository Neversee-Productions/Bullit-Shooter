#include "Scenes\GameScene\Bullets\PyroBlast.h"

const float bullets::PyroBlast::s_FIRE_RATE = 4.0f;

/// <summary>
/// @brief Default constructor.
/// 
/// 
/// </summary>
bullets::PyroBlast::PyroBlast()
	: Bullet()
	, TIMETOLIVE(3.0f)
	, m_explode(false)
{
	m_speed = 4.0f;
	m_velocity.x = m_speed;

	//different size to parent
	m_bulletRect.setSize(sf::Vector2f(20.0f, 15.0f));
	m_bulletRect.setOrigin(m_bulletRect.getSize().x / 2, m_bulletRect.getSize().y / 2);

	//change collision rectangle
	updateBox();
}

/// <summary>
/// @brief update position and velocity.
/// 
/// 
/// </summary>
void bullets::PyroBlast::update()
{
	TIMETOLIVE -= App::getUpdateDeltaTime();
	if (TIMETOLIVE <= 0)
	{
		m_explode = true;
	}
	if (!m_explode)
	{
		Bullet::update();
	}
	else
	{
		if (m_bulletRect.getSize().x < 200.0f)
		{
			m_bulletRect.setSize(m_bulletRect.getSize() + sf::Vector2f(2.0f, 2.0f));
			m_bulletRect.setOrigin(m_bulletRect.getSize().x / 2, m_bulletRect.getSize().y / 2);
		}
		else
		{
			setActive(false);
		}
	}
	updateBox();
}

/// <summary>
/// @Static method to return a fire rate.
/// 
/// 
/// </summary>
/// <returns>value of fire rate</returns>
float bullets::PyroBlast::getFireRate()
{
	return s_FIRE_RATE;
}

/// <summary>
/// @brief overloaded set active method.
/// 
/// This method will check if active is being set to false
/// if yes then reset to original form
/// </summary>
/// <param name="active">determines the active state of bullet</param>
void bullets::PyroBlast::setActive(bool active)
{
	if (!active)
	{
		m_bulletRect.setSize(sf::Vector2f(20.0f, 10.0f));
		m_bulletRect.setOrigin(m_bulletRect.getSize().x / 2, m_bulletRect.getSize().y / 2);
		m_explode = false;
		TIMETOLIVE = 3.0f;
	}
	m_active = active;
}
