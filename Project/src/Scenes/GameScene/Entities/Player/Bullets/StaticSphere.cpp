#include "Scenes\GameScene\Entities\Player\Bullets\StaticSphere.h"

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
	, m_pulseCircleCollider()
{
	m_speed = 6.0f * 60.0f;
	m_velocity.y = -m_speed;
	m_angle = -90.0f;

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

	updateCollisionCircle();

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
	m_pulseTimer += UPDATE_DT;
	Bullet::update();
	if (m_pulseTimer > 0.3f)
	{
		m_pulseCircle.setRadius(m_pulseCircle.getRadius() + 1.0f);
		m_pulseCircle.setOrigin(m_pulseCircle.getRadius(), m_pulseCircle.getRadius());
		m_pulseCircle.setPosition(m_position);
		m_pulse = true;

		updateCollisionCircle();
	}
	if (m_pulseCircle.getRadius() > 100)
	{
		m_pulseCircle.setRadius(0.0f);
		m_pulseTimer = 0.0f;

		updateCollisionCircle();
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

/// <summary>
/// @brief this function will update the collision circle.
/// 
/// Change the radius and position of our collision circle.
/// </summary>
void bullets::StaticSphere::updateCollisionCircle()
{
	m_pulseCircleCollider.p.x = m_pulseCircle.getPosition().x;
	m_pulseCircleCollider.p.y = m_pulseCircle.getPosition().y;
	m_pulseCircleCollider.r = m_pulseCircle.getRadius();
}

/// <summary>
/// @brief overriden circle collision.
/// 
/// This version will have to take into account the pulse circle as well
/// as the bullet shape itself,
/// </summary>
/// <param name="other">circle to check collision against</param>
/// <returns>If collision is happening returns true</returns>
bool bullets::StaticSphere::checkCircleCollision(const tinyh::c2Circle & other)
{
	if (tinyh::c2CircletoAABB(other, m_bulletC2Rect) || tinyh::c2CircletoCircle(other, m_pulseCircleCollider))
	{
		return true;
	}
	return false;
}
