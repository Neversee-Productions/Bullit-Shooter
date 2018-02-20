#include "Entities\Player\Bullets\PyroBlast.h"

const float bullets::PyroBlast::s_FIRE_RATE = 0.7f;

/// <summary>
/// @brief Default constructor.
/// 
/// 
/// </summary>
bullets::PyroBlast::PyroBlast()
	: Bullet()
	, m_explode(false)
	, m_damage(6.0f)
{
	m_speed = 6.0f * 60.0f;
	m_velocity.y = -m_speed;

	//different size to parent
	m_bulletRect.setSize(sf::Vector2f(100.0f, 120.0f));
	m_bulletRect.setOrigin(m_bulletRect.getSize().x / 2, m_bulletRect.getSize().y / 2);

	m_type = BulletTypes::PyroBlast;

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
		if (m_bulletRect.getSize().x < 400.0f)
		{
			m_bulletRect.setSize(m_bulletRect.getSize() + sf::Vector2f(3.0f, 3.0f));
			m_bulletRect.setOrigin(m_bulletRect.getSize().x / 2, m_bulletRect.getSize().y / 2);
			updateExplosionCircle();
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
		m_bulletRect.setSize(sf::Vector2f(100.0f, 120.0f));
		m_bulletRect.setOrigin(m_bulletRect.getSize().x / 2, m_bulletRect.getSize().y / 2);
		m_explode = false;
		this->setAnimation(s_LOOP_ID);
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
	if (check)
	{
		this->setAnimation(s_IMPACT_ID);
	}
}

/// <summary>
/// @brief returns yes/no on whether this bullet is in the explosion state.
/// 
/// 
/// </summary>
/// <returns>True for yes, false for no.</returns>
bool bullets::PyroBlast::isExplosion()
{
	return m_explode;
}

/// <summary>
/// @brief get the damage of this bullet.
/// 
/// 
/// </summary>
/// <returns>defines value of damage as float.</returns>
const float & bullets::PyroBlast::getDamage()
{
	return m_damage;
}

/// <summary>
/// @brief Check collision between bullet and another object OR agains bullets explosion and other object.
/// 
/// 
/// </summary>
/// <param name="other">other object</param>
/// <returns>true if collision happened otherwise false</returns>
bool bullets::PyroBlast::checkCircleCollision(const tinyh::c2Circle & other)
{
	if (m_explode)
	{
		if (tinyh::c2CircletoCircle(other, m_explosionCircleCollider))
		{
			return true;
		}
	}
	else if(tinyh::c2CircletoAABB(other, m_bulletC2Rect))
	{
		return true;
	}
	return false;
}

/// <summary>
/// @brief Check collision between bullet and another object OR against bullets explosion and other object.
/// 
/// 
/// </summary>
/// <param name="other">other object.</param>
/// <returns>true if collision happened otherwise false.</returns>
bool bullets::PyroBlast::checkAABBCollision(const tinyh::c2AABB & other)
{
	if (m_explode)
	{
		if (tinyh::c2CircletoAABB(m_explosionCircleCollider, other))
		{
			return true;
		}
	}
	else if (tinyh::c2AABBtoAABB(other, m_bulletC2Rect))
	{
		return true;
	}
	return false;
}

/// <summary>
/// @brief this method will update the explosiion circle.
/// 
/// 
/// </summary>
void bullets::PyroBlast::updateExplosionCircle()
{
	m_explosionCircleCollider.p.x = m_bulletRect.getPosition().x;
	m_explosionCircleCollider.p.y = m_bulletRect.getPosition().y;
	m_explosionCircleCollider.r = (m_bulletRect.getGlobalBounds().width / 2.0f) * 0.8f;
}
