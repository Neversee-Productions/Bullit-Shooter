#include "Scenes\GameScene\Bullet.h"

/// <summary>
/// @brief Default constructor.
/// 
/// 
/// </summary>
Bullet::Bullet()
	: m_position(0.0f,0.0f)
	, m_bulletRect()
	, m_active(false)
	, m_type(BulletTypes::Standard)
	, m_bulletC2Rect()
{
	m_bulletRect.setPosition(0.0f,0.0f);
	m_bulletRect.setFillColor(sf::Color::White);
	m_bulletRect.setSize(sf::Vector2f(10.0f, 10.0f));
	m_bulletRect.setOrigin(m_bulletRect.getSize().x / 2, m_bulletRect.getSize().y / 2);

	//define the bullet collision rectangle
	const auto & bulletRect = m_bulletRect.getGlobalBounds();
	m_bulletC2Rect.min.x = bulletRect.left;
	m_bulletC2Rect.min.y = bulletRect.top;
	m_bulletC2Rect.max.x = bulletRect.left + bulletRect.width;
	m_bulletC2Rect.max.x = bulletRect.top + bulletRect.height;
}

/// <summary>
/// @brief overloaded constructor
/// 
/// 
/// </summary>
/// <param name="position">defines the position vector</param>
/// <param name="type">define type of bullet to create</param>
Bullet::Bullet(sf::Vector2f position, BulletTypes type)
	: m_position(position)
	, m_bulletRect()
	, m_active(false)
	, m_type(type)
	, m_bulletC2Rect()
{
	m_bulletRect.setPosition(position);
	m_bulletRect.setFillColor(sf::Color::White);
	m_bulletRect.setSize(sf::Vector2f(10.0f, 10.0f));
	m_bulletRect.setOrigin(m_bulletRect.getSize().x / 2, m_bulletRect.getSize().y / 2);

	//define the bullet collision rectangle
	const auto & bulletRect = m_bulletRect.getGlobalBounds();
	m_bulletC2Rect.min.x = bulletRect.left;
	m_bulletC2Rect.min.y = bulletRect.top;
	m_bulletC2Rect.max.x = bulletRect.left + bulletRect.width;
	m_bulletC2Rect.max.x = bulletRect.top + bulletRect.height;
}

/// <summary>
/// @brief Render entities.
/// 
/// 
/// </summary>
/// <param name="window">define reference to our target Window.</param>
/// <param name="deltaTime">define reference to draw time step.</param>
void Bullet::draw(Window & window, const float & deltaTime)
{
	if (m_active)
	{
		window.draw(m_bulletRect);
	}
}

/// <summary>
/// @brief get the collision box.
/// 
/// 
/// </summary>
/// <returns>The collision box</returns>
tinyh::c2AABB Bullet::getCollisionRect()
{
	return m_bulletC2Rect;
}

/// <summary>
/// @brief set the active of bullet.
/// 
/// 
/// </summary>
/// <param name="active">the active boolean</param>
void Bullet::setActive(bool active)
{
	m_active = active;
}

/// <summary>
/// @brief update bounding box.
/// 
/// 
/// </summary>
void Bullet::updateBox()
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
void Bullet::setPosition(const sf::Vector2f& pos)
{
	m_position = pos;
	m_bulletRect.setPosition(pos);
	updateBox();
}

/// <summary>
/// @brief return the active boolean.
/// 
/// 
/// </summary>
/// <returns>active bool</returns>
bool Bullet::isActive() const
{
	return m_active;
}





