#include "Scenes\GameScene\Entities\Player\Bullets\PyroBlast.h"

const float bullets::PyroBlast::s_FIRE_RATE = 4.0f;

/// <summary>
/// @brief Default constructor.
/// 
/// 
/// </summary>
bullets::PyroBlast::PyroBlast()
	: Bullet()
	, m_explode(false)
{
	m_speed = 4.0f * 60.0f;
	m_velocity.y = -m_speed;

	//different size to parent
	m_bulletRect.setSize(sf::Vector2f(15.0f, 20.0f));
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
	tempRect.setPosition(m_bulletC2Rect.min.x, m_bulletC2Rect.min.y);
	tempRect.setSize(sf::Vector2f(m_bulletC2Rect.max.x - m_bulletC2Rect.min.x, m_bulletC2Rect.max.y - m_bulletC2Rect.min.y));
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
		m_bulletRect.setSize(sf::Vector2f(20.0f, 15.0f));
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
void bullets::PyroBlast::explode(bool check)
{
	m_explode = check;
}
