#include "Scenes\GameScene\Bullets\StaticSphere.h"

const float bullets::StaticSphere::s_FIRE_RATE = 1.0f;


/// <summary>
/// @brief Default constructor.
/// 
/// 
/// </summary>
bullets::StaticSphere::StaticSphere()
	: Bullet()
	, m_pulse(false)
	, m_pulseTimer(0.0f)
{
	m_speed = 6.0f;
	m_velocity.x = m_speed;

	//different size to parent
	m_bulletRect.setSize(sf::Vector2f(30.0f, 30.0f));
	m_bulletRect.setOrigin(m_bulletRect.getSize().x / 2, m_bulletRect.getSize().y / 2);
	m_pulseCircle.setFillColor(sf::Color::Red);
	m_pulseCircle.setRadius(0.0f);
	m_pulseCircle.setOutlineThickness(6.0f);
	m_pulseCircle.setOutlineColor(sf::Color::Red);
	m_pulseCircle.setFillColor(sf::Color(0u, 0u, 0u, 0u));
	m_pulseCircle.setPosition(m_position);
	m_pulseCircle.setOrigin(m_pulseCircle.getRadius(), m_pulseCircle.getRadius());

	//change collision rectangle
	updateBox();
}

/// <summary>
/// @brief update the position and velocity.
/// 
/// 
/// </summary>
void bullets::StaticSphere::update()
{
	m_pulseTimer += App::getUpdateDeltaTime();
	Bullet::update();
	if (m_pulseTimer > 0.3f)
	{
		m_pulseCircle.setRadius(m_pulseCircle.getRadius() + 1.0f);
		m_pulseCircle.setOrigin(m_pulseCircle.getRadius(), m_pulseCircle.getRadius());
		m_pulseCircle.setPosition(m_position);
		m_pulse = true;
	}
	if (m_pulseCircle.getRadius() > 100)
	{
		m_pulseCircle.setRadius(0.0f);
		m_pulseTimer = 0.0f;
	}
	updateBox();
}

/// <summary>
/// @brief overloaded draw.
/// 
/// will draw a circle when needed
/// </summary>
/// <param name="window">reference to window object</param>
/// <param name="deltaTime">constant reference to deltatime</param>
void bullets::StaticSphere::draw(Window & window, const float & deltaTime)
{
	if (m_pulse)
	{
		window.draw(m_pulseCircle);
	}
	Bullet::draw(window, deltaTime);
}

/// <summary>
/// @Static method to return a fire rate.
/// 
/// 
/// </summary>
/// <returns>value of fire rate</returns>
float bullets::StaticSphere::getFireRate()
{
	return s_FIRE_RATE;
}

/// <summary>
/// @brief overloaded set active method.
/// 
/// This method will check if active is being set to false
/// if yes then reset circle to original size.
/// </summary>
/// <param name="active">determines the active state of bullet</param>
void bullets::StaticSphere::setActive(bool active)
{
	if (!active)
	{
		m_pulseCircle.setRadius(0.0f);
		m_pulseTimer = 0.0f;
	}
	m_active = active;
}
