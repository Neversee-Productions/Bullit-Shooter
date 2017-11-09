#include "Scenes\GameScene\Bullets\Bullet.h"
#include "Thor\Math.hpp"

double const bullets::Bullet::DEG_TO_RAD = thor::Pi / 180.0f;

/// <summary>
/// @brief Default constructor.
/// 
/// 
/// </summary>
bullets::Bullet::Bullet()
	: m_position(0.0f,0.0f)
	, m_bulletRect()
	, m_active(false)
	, m_type(BulletTypes::Standard)
	, m_bulletC2Rect()
	, m_velocity(0.0f,0.0f)
	, m_speed(0)
	, m_angle(0)
{
	m_bulletRect.setPosition(0.0f,0.0f);
	m_bulletRect.setFillColor(sf::Color::White);
	m_bulletRect.setSize(sf::Vector2f(5.0f, 5.0f));
	m_bulletRect.setOrigin(m_bulletRect.getSize().x / 2, m_bulletRect.getSize().y / 2);

	//define the bullet collision rectangle
	const auto & bulletRect = m_bulletRect.getGlobalBounds();
	m_bulletC2Rect.min.x = bulletRect.left;
	m_bulletC2Rect.min.y = bulletRect.top;
	m_bulletC2Rect.max.x = bulletRect.left + bulletRect.width;
	m_bulletC2Rect.max.x = bulletRect.top + bulletRect.height;
}

/// <summary>
/// @brief default update.
/// 
/// updates bullet position based on velocity
/// </summary>
void bullets::Bullet::update()
{
	m_position += m_velocity;
	m_bulletRect.setPosition(m_position.x, m_position.y);
	updateBox();
}

/// <summary>
/// @brief Render entities.
/// 
/// 
/// </summary>
/// <param name="window">define reference to our target Window.</param>
/// <param name="deltaTime">define reference to draw time step.</param>
void bullets::Bullet::draw(Window & window, const float & deltaTime)
{
	window.draw(m_bulletRect);
}

/// <summary>
/// @brief get the collision box.
/// 
/// 
/// </summary>
/// <returns>The collision box</returns>
tinyh::c2AABB bullets::Bullet::getCollisionRect()
{
	return m_bulletC2Rect;
}

/// <summary>
/// @brief set the active of bullet.
/// 
/// 
/// </summary>
/// <param name="active">the active boolean</param>
void bullets::Bullet::setActive(bool active)
{
	m_active = active;
}

/// <summary>
/// @brief update bounding box.
/// 
/// 
/// </summary>
void bullets::Bullet::updateBox()
{
	const auto & bulletRect = m_bulletRect.getGlobalBounds();
	m_bulletC2Rect.min.x = bulletRect.left;
	m_bulletC2Rect.min.y = bulletRect.top;
	m_bulletC2Rect.max.x = bulletRect.left + bulletRect.width;
	m_bulletC2Rect.max.x = bulletRect.top + bulletRect.height;
}

/// <summary>
/// @brief Set the position vector
/// 
/// 
/// </summary>
/// <param name="pos">defines the new position vector</param>
void bullets::Bullet::setPosition(const sf::Vector2f& pos)
{
	m_position = pos;
	m_bulletRect.setPosition(pos);
	updateBox();
}

/// <summary>
/// @brief set angle of fire.
/// 
/// 
/// </summary>
/// <param name="angle">reference to angle of fire</param>
void bullets::Bullet::setAngle(const float & angle)
{
	m_angle = angle;
}

/// <summary>
/// @brief update the velocity based on angle.
/// 
/// 
/// </summary>
void bullets::Bullet::updateVelocityVector()
{
	const auto & angleRad = thor::toRadian(m_angle);
	m_velocity.x = cos(angleRad) * m_speed;
	m_velocity.y = sin(angleRad) * m_speed;
}

/// <summary>
/// @brief return the active boolean.
/// 
/// 
/// </summary>
/// <returns>active bool</returns>
bool bullets::Bullet::isActive() const
{
	return m_active;
}





