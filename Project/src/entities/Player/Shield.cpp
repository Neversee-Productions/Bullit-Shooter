#include "Entities\Player\Shield.h"

float const Shield::INVULNERABILITY_FRAMES = 0.09f;

/// <summary>
/// @brief default constructor.
/// 
/// 
/// </summary>
/// <param name="position"></param>
/// <param name="radius"></param>
Shield::Shield(sf::Vector2f position, float radius)
	: m_circle(radius)
	, m_position(position)
	, m_health(100)
	, m_invulnerable(false)
	, m_invulnTimer(0.0f)
{
	m_circle.setPosition(m_position);
	m_circle.setOrigin(m_circle.getRadius(), m_circle.getRadius());
	m_circle.setFillColor(sf::Color(0u, 0u, 255u, 50u));
	m_collisionCircle.r = radius;
}

/// <summary>
/// @brief update the position of the shield.
/// 
/// 
/// </summary>
void Shield::update()
{
	if (m_invulnerable)
	{
		m_circle.setFillColor(sf::Color(255u, 255u, 255u, 50u));
		m_invulnTimer += App::getUpdateDeltaTime();
		if (m_invulnTimer >= INVULNERABILITY_FRAMES)
		{
			m_circle.setFillColor(sf::Color(0u, 0u, 255u, 50u));
			m_invulnerable = false;
			m_invulnTimer = 0.0f;
		}
	}
	else
	{
	}


	m_circle.setPosition(m_position);
	m_collisionCircle.p.x = m_position.x;
	m_collisionCircle.p.y = m_position.y;
}

/// <summary>
/// @brief draw the entity.
/// 
/// 
/// </summary>
/// <param name="window">constant reference to the window.</param>
/// <param name="deltaTime"></param>
void Shield::draw(Window & window, const float & deltaTime)
{
	window.draw(m_circle);
}

/// <summary>
/// @brief setter for the position.
/// 
/// 
/// </summary>
/// <param name="pos">new position of the object</param>
void Shield::setPosition(sf::Vector2f pos)
{
	m_position = pos;
}

/// <summary>
/// @brief decrements shield health and sets invulnerability to true.
/// 
/// 
/// </summary>
/// <param name="dmg"></param>
void Shield::decrementShield(float dmg)
{
	if (!m_invulnerable)
	{
		m_health -= dmg;
		m_invulnerable = true;
	}
}

/// <summary>
/// @brief Returns a constant reference to the circle shape.
/// 
/// 
/// </summary>
/// <returns>constant reference to the collision circle</returns>
const sf::CircleShape & Shield::getCircleShape()
{
	return m_circle;
}

/// <summary>
/// @brief getter for the collision circle.
/// 
/// 
/// </summary>
/// <returns>constant reference to the collision circle.</returns>
const tinyh::c2Circle & Shield::getCollisionCircle()
{
	return m_collisionCircle;
}

/// <summary>
/// @brief get the health of the shield.
/// 
/// 
/// </summary>
/// <returns>Constant reference to the shield health.</returns>
const float & Shield::getHealth()
{
	return m_health;
}

/// <summary>
/// @brief this function will reset the shield health to full and reset all variables associated to it.
/// 
/// 
/// </summary>
void Shield::resetShield()
{
	m_health = 100;
	m_invulnerable = false;
	m_invulnTimer = 0.0f;
}
